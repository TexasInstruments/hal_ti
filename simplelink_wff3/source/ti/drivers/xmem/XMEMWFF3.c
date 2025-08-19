/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ========== XSPIWFF3.c ==========
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/dpl/SemaphoreP.h>
#include <ti/drivers/dpl/ClockP.h>

#include <ti/drivers/xmem/XMEMWFF3.h>
#include <ti/drivers/xmem/flash/FlashWFF3.h>

#include <ti/devices/DeviceFamily.h>

#define PHY_OFFSET             12
#define PHYSICAL_ADDR          0
#define LOGIC_ADDR             1
#define VERIFBUF_SIZE_IN_BYTES 256

static int_fast16_t checkEraseRange(XMEM_Handle handle, size_t offset, size_t size);
static int_fast16_t doErase(XMEM_Handle handle, size_t offset, size_t size);
static uint32_t ConvertOffsetToAddr(XMEM_Handle handle, size_t offset, size_t AddrType);

static XMEMWFF3_Object object[XMEM_NUM_DEVICE] = {{.opened = false}};

static const XMEMWFF3_HWAttrs hwAttrs[XMEM_NUM_DEVICE] = {

    {

        .sectorSize         = 0x1000,
        .regionBase         = 0x21A000,
        .regionStartAddr    = 0xA0050000,
        .regionOffset       = 0x1CA,
        .regionSize         = 0x1E5000,
        .sectorEraseOpcode  = 0x20,
        .sectorEraseTimeOut = 200,
        .verifyBufSize      = VERIFBUF_SIZE_IN_BYTES

    }

};

XMEM_Config XMEM_config[XMEM_NUM_DEVICE] = {

    {

        .object  = &(object[XMEM_FLASH]),
        .hwAttrs = &(hwAttrs[XMEM_FLASH])

    }

};

const uint8_t XMEM_count = XMEM_NUM_DEVICE;

/*
 *  Semaphore to synchronize access to flash region.
 */
static SemaphoreP_Handle writeSem = NULL;

static size_t sectorBaseMask; /* for efficient argument checking */
static void *verifyBuf;       /*!< Write Pre/Post verify buffer */
static uint8_t verifyBuffer[VERIFBUF_SIZE_IN_BYTES];

/*
 *  ======== XMEMWFF3_close ========
 */
void XMEMWFF3_close(XMEM_Handle handle)
{
    XMEMWFF3_Object *object;

    object         = handle->object;
    object->opened = false;
}

/*
 *  ======== XMEMWFF3_erase ========
 */
int_fast16_t XMEMWFF3_erase(XMEM_Handle handle, size_t offset, size_t size)
{
    int_fast16_t status;

    SemaphoreP_pend(writeSem, SemaphoreP_WAIT_FOREVER);

    status = doErase(handle, offset, size);

    SemaphoreP_post(writeSem);

    return (status);
}

/*
 *  ======== XMEMWFF3_getAttrs ========
 */
void XMEMWFF3_getAttrs(XMEM_Handle handle, XMEM_Attrs *attrs)
{
    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    attrs->regionBase = (void *)&hwAttrs->regionBase;
    attrs->regionSize = hwAttrs->regionSize;
    attrs->sectorSize = hwAttrs->sectorSize;
}

/*
 *  ======== XMEMWFF3_init ========
 */
void XMEMWFF3_init(void)
{

    unsigned int key;

    /* Initialize variables */
    verifyBuf = (void *)&verifyBuffer;

    key = HwiP_disable();

    if (writeSem == NULL)
    {
        /* Create a binary semaphore for thread safety */
        writeSem = SemaphoreP_createBinary(1);
        HwiP_restore(key);
    }
    else
    {
        /* Init already called */
        HwiP_restore(key);
    }
}

/*
 *  ======== XMEMWFF3_lock =======
 */
int_fast16_t XMEMWFF3_lock(XMEM_Handle handle, uint32_t timeout)
{
    if (SemaphoreP_pend(writeSem, timeout) != SemaphoreP_OK)
    {
        return (XMEM_STATUS_TIMEOUT);
    }
    return (XMEM_STATUS_SUCCESS);
}

/*
 *  ======== XMEMWFF3_open =======
 */
XMEM_Handle XMEMWFF3_open(uint_least8_t index)
{
    XMEMWFF3_Object *object;
    XMEMWFF3_HWAttrs const *hwAttrs;
    XMEM_Handle handle;

    /* Confirm that 'init' has successfully completed */
    if (writeSem == NULL)
    {
        XMEMWFF3_init();
        if (writeSem == NULL)
        {
            return (NULL);
        }
    }

    /* Verify XMEM region index */
    if (index >= XMEM_count)
    {
        return (NULL);
    }

    handle  = &XMEM_config[index];
    object  = XMEM_config[index].object;
    hwAttrs = XMEM_config[index].hwAttrs;

    sectorBaseMask = ~(hwAttrs->sectorSize - 1);

    SemaphoreP_pend(writeSem, SemaphoreP_WAIT_FOREVER);

    if (object->opened == true)
    {
        SemaphoreP_post(writeSem);
        return (NULL);
    }

    /* The region cannot be smaller than a sector size */
    if (hwAttrs->regionSize < hwAttrs->sectorSize)
    {
        SemaphoreP_post(writeSem);
        return (NULL);
    }

    /* The region size must be a multiple of sector size */
    if (hwAttrs->regionSize != (hwAttrs->regionSize & sectorBaseMask))
    {
        SemaphoreP_post(writeSem);
        return (NULL);
    }

    object->opened = true;

    SemaphoreP_post(writeSem);

    return (handle);
}

/*
 *  ======== XMEMWFF3_read =======
 */
int_fast16_t XMEMWFF3_read(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize)
{
    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    unsigned int key;
    uint32_t flashlogicAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR);

    if (offset + bufferSize > hwAttrs->regionSize)
    {
        return (XMEM_STATUS_INV_OFFSET);
    }

    /*
     *  Get exclusive access to the region.  We don't want someone
     *  else to erase the region while we are reading it.
     */
    SemaphoreP_pend(writeSem, SemaphoreP_WAIT_FOREVER);

    FlashRead((uint32_t *)flashlogicAddr, (uint32_t *)buffer, bufferSize);

    SemaphoreP_post(writeSem);

    return (XMEM_STATUS_SUCCESS);
}

/*
 *  ======== XMEMWFF3_unlock =======
 */
void XMEMWFF3_unlock(XMEM_Handle handle)
{
    SemaphoreP_post(writeSem);
}

/*
 *  ======== XMEMWFF3_write =======
 */
int_fast16_t XMEMWFF3_write(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize, uint_fast16_t flags)
{
    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    unsigned int key;
    unsigned int size;
    uint32_t status              = 0;
    uint32_t flashlogicStartAddr = ConvertOffsetToAddr(handle, offset, LOGIC_ADDR);
    uint32_t flashlogicAddr      = flashlogicStartAddr;
    uint32_t *srcBuf, *dstBuf;
    uint32_t totalSize;
    int i, j;
    int retval = XMEM_STATUS_SUCCESS;

    /* Validate offset and bufferSize */
    if (offset + bufferSize > hwAttrs->regionSize)
    {
        return (XMEM_STATUS_INV_OFFSET);
    }

    /* Get exclusive access to the Flash region */
    SemaphoreP_pend(writeSem, SemaphoreP_WAIT_FOREVER);

    /* If erase is set, erase destination sector(s) first */
    if (flags & XMEM_WRITE_ERASE)
    {
        size = bufferSize & sectorBaseMask;
        if (bufferSize & (~sectorBaseMask))
        {
            size += hwAttrs->sectorSize;
        }

        /* Validate offset is not aligned on a sector boundary */
        if (offset != (offset & sectorBaseMask))
        {
            SemaphoreP_post(writeSem);
            return (XMEM_STATUS_INV_ALIGNMENT);
        }

        retval = doErase(handle, offset, size);
        if (retval != XMEM_STATUS_SUCCESS)
        {
            SemaphoreP_post(writeSem);
            return (retval);
        }
    }
    else if (flags & XMEM_WRITE_PRE_VERIFY)
    {
        /*
         *  If pre-verify, each destination byte must be able to be changed to the
         *  source byte (1s to 0s, not 0s to 1s).
         *  this is satisfied by the following test:
         *     src == (src & dst)
         */

        /* Validate that the verification buffer has been configured */
        if ((verifyBuf == NULL) || (hwAttrs->verifyBufSize == 0))
        {
            SemaphoreP_post(writeSem);
            return (XMEM_STATUS_VERIFYBUFFER);
        }

        /* Start reading from the requested start address */
        flashlogicAddr = flashlogicStartAddr;

        /* Set the number of bytes to read */
        totalSize = bufferSize;

        j = 0;

        while (totalSize > 0)
        {
            if (totalSize > hwAttrs->verifyBufSize)
            {
                size = hwAttrs->verifyBufSize;
            }
            else
            {
                size = totalSize;
            }

            /* Read destination before the change for pre-verify expected change */
            dstBuf = (uint32_t *)verifyBuf;

            key = HwiP_disable();
            FlashRead((uint32_t *)flashlogicAddr, (uint32_t *)dstBuf, (uint32_t)size);
            HwiP_restore(key);

            srcBuf = (uint32_t *)buffer;

            for (i = 0; i < size / 4; i++, j++)
            {
                if (srcBuf[j] != (srcBuf[j] & dstBuf[i]))
                {
                    SemaphoreP_post(writeSem);
                    return (XMEM_STATUS_INV_WRITE);
                }
            }

            flashlogicAddr = flashlogicAddr + size;
            totalSize      = totalSize - size;
        }
    }

    srcBuf = (uint32_t *)buffer;
    size   = bufferSize;
    dstBuf = (uint32_t *)flashlogicStartAddr;

    key = HwiP_disable();
    FlashWrite((uint32_t *)srcBuf, (uint32_t *)dstBuf, size);
    HwiP_restore(key);

    if (status != 0)
    {
        retval = XMEM_STATUS_ERROR;
    }
    else if (flags & XMEM_WRITE_POST_VERIFY)
    {
        /*
         *  Note: This validates the entire bufferSize even on erase mode.
         */

        /* Validate that the verification buffer has been configured */
        if ((verifyBuf == NULL) || (hwAttrs->verifyBufSize == 0))
        {
            SemaphoreP_post(writeSem);
            return (XMEM_STATUS_VERIFYBUFFER);
        }

        /* Start reading from the requested start address */
        flashlogicAddr = flashlogicStartAddr;

        /* Set the number of bytes to read */
        totalSize = bufferSize;

        j = 0;

        while (totalSize > 0)
        {
            if (totalSize > hwAttrs->verifyBufSize)
            {
                size = hwAttrs->verifyBufSize;
            }
            else
            {
                size = totalSize;
            }

            srcBuf = buffer;
            dstBuf = (uint32_t *)verifyBuf;

            key = HwiP_disable();
            FlashRead((uint32_t *)flashlogicAddr, (uint32_t *)dstBuf, (uint32_t)size);
            HwiP_restore(key);

            for (i = 0; i < size / 4; i++, j++) /* compare 32bits */
            {
                if (srcBuf[j] != dstBuf[i])
                {
                    SemaphoreP_post(writeSem);
                    return (XMEM_STATUS_ERROR);
                }
            }

            flashlogicAddr = flashlogicAddr + size;
            totalSize      = totalSize - size;
        }
    }

    SemaphoreP_post(writeSem);

    return (retval);
}

/*
 *  ======== checkEraseRange ========
 */
static int_fast16_t checkEraseRange(XMEM_Handle handle, size_t offset, size_t size)
{
    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    if (offset != (offset & sectorBaseMask))
    {
        return (XMEM_STATUS_INV_ALIGNMENT); /* Start address is not aligned */
    }

    if (size != (size & sectorBaseMask))
    {
        return (XMEM_STATUS_INV_SIZE); /* Size is not a multiple of sector size */
    }

    if (offset >= hwAttrs->regionSize)
    {
        return (XMEM_STATUS_INV_OFFSET); /* Offset is past end of region */
    }

    if (offset + size > hwAttrs->regionSize)
    {
        return (XMEM_STATUS_INV_SIZE); /* Size is too big */
    }

    return (XMEM_STATUS_SUCCESS);
}

uint32_t ConvertOffsetToAddr(XMEM_Handle handle, size_t offset, size_t AddrType)
{
    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    uint32_t calcAddr;
    uint32_t controlbits = 0xFFFFFFFF;
    uint32_t blockbits;

    if (AddrType == LOGIC_ADDR)
    {
        /* Calculate logic address */
        uint32_t regionoffsetAlign = (uint32_t)hwAttrs->regionOffset << PHY_OFFSET;
        controlbits                = (hwAttrs->regionStartAddr & BITMASK_x_y(31, 26));
        blockbits = ((uint32_t)abs((int)hwAttrs->regionBase - (int)regionoffsetAlign) & BITMASK_x_y(25, 12));
        calcAddr  = controlbits + blockbits + offset;
        return (calcAddr);
    }
    else
    {
        /* Calculate physical address */
        calcAddr = hwAttrs->regionBase + offset;
        return (calcAddr);
    }
}

/*
 *  ======== doErase ========
 */
static int_fast16_t doErase(XMEM_Handle handle, size_t offset, size_t size)
{
    XMEMWFF3_HWAttrs const *hwAttrs;

    hwAttrs = handle->hwAttrs;

    unsigned int key;
    uint32_t status = 0;
    uint32_t sectorBase;
    uint32_t sectorEraseSize       = hwAttrs->sectorSize;
    uint32_t eraseOpcode           = hwAttrs->sectorEraseOpcode;
    uint32_t sectorEraseTimeoutVal = hwAttrs->sectorEraseTimeOut; /*!< Flash_max_operation_time_limit */
    uint32_t clockPTick;
    uint32_t clockPTickPeriod;
    int_fast16_t rangeStatus;

    /* Sanity test the erase args */
    rangeStatus = checkEraseRange(handle, offset, size);

    if (rangeStatus != XMEM_STATUS_SUCCESS)
    {
        return (rangeStatus);
    }

    uint32_t startAddrPhy = ConvertOffsetToAddr(handle, offset, PHYSICAL_ADDR);

    while (size)
    {
        key = HwiP_disable();

        /*
         * Ensure SysTimer is enabled, to be able to read the SysTimer counter
         * value.
         */
        clockPTick       = ClockP_getSystemTicks();
        clockPTickPeriod = ClockP_getSystemTickPeriod();
        FlashSetTickPeriod(clockPTickPeriod);
        status = (uint32_t)FlashSectorErase(startAddrPhy, eraseOpcode, sectorEraseTimeoutVal);

        HwiP_restore(key);

        if (status != FLASH_STATUS_SUCCESS)
        {
            break;
        }

        startAddrPhy += hwAttrs->sectorSize;
        size -= hwAttrs->sectorSize;
    }

    if (status != FLASH_STATUS_SUCCESS)
    {
        return (XMEM_STATUS_ERROR);
    }

    return (XMEM_STATUS_SUCCESS);
}
