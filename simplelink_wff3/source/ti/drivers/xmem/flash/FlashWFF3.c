/*
 *  Copyright (c) 2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * ========== FlashWFF3.c ==========
 */

#include "assert.h"
#include "FlashWFF3.h"
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/dpl/DebugP.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_systim.h)

/*
 * Globals
 */
static uint32_t flashClockPTickPeriod = 1U;

static uint32_t __attribute__((section(".TI.ramfunc"))) getClockPTickUs(void);
static bool __attribute__((section(".TI.ramfunc")))
FlashClockPCheckTimeout(uint32_t StartTick, uint32_t TimerInMicroSec);
static uint32_t FlashGetBound(uint8_t directionMode);
static FlashUdmaJobStatus FlashUDMAOperationStatus(uint32_t channelSelect);
static void FlashPartitioningUDMATransaction(uint32_t *srcAddr,
                                             uint32_t *dstAddr,
                                             uint32_t lengthBytes,
                                             uint8_t directionMode,
                                             uint32_t channelSelect);

void FlashRead(uint32_t *readFromAddr, uint32_t *writeToAddr, uint32_t length)
{

    FlashPartitioningUDMATransaction(readFromAddr,
                                     writeToAddr,
                                     length,
                                     XIP_UDMA_DIRECTION_EXT_TO_INT,
                                     XIP_UDMA_SECURE_CHANNEL);
}

void FlashWrite(uint32_t *readFromAddr, uint32_t *writeToAddr, uint32_t length)
{
    FlashPartitioningUDMATransaction(readFromAddr,
                                     writeToAddr,
                                     length,
                                     XIP_UDMA_DIRECTION_INT_TO_EXT,
                                     XIP_UDMA_SECURE_CHANNEL);
}

void __attribute__((section(".TI.ramfunc"))) FlashSetOTFDE(uint8_t setState)
{
    DebugP_assert(!((setState == FLASH_OTFDE_DISABLE) || (setState == FLASH_OTFDE_ENABLE)));

    if (setState == FLASH_OTFDE_DISABLE)
    {
        XIPDisableOTFDE();
    }
    else if (setState == FLASH_OTFDE_ENABLE)
    {
        XIPEnableOTFDE();
    }
}

/*
 * ======== FlashExecutePolling ========
 */
uint32_t __attribute__((section(".TI.ramfunc"))) FlashExecutePolling(uint32_t timerVal)
{

    OSPISTIGConfig_t XspiStigConifgReg = {0};
    XspiStigConifgReg.stigOpcode       = OSPI_COMMAND_RDSR;
    XspiStigConifgReg.stigRdEn         = OSPI_STIG_READ_DATA_ENABLE >> OSPI_FLASH_CMD_CTRL_ENB_READ_DATA_S;
    XspiStigConifgReg.stigRDNumBytes   = 1;
    uint32_t startTime                 = (uint32_t)getClockPTickUs();
    uint32_t timerValMicroSec          = timerVal * 1000;

    /* Wait for command completion by polling WIP bit from flash status register */
    do
    {
        if (timerVal != 0)
        {
            if (FlashClockPCheckTimeout(startTime, timerValMicroSec) != 1)
            {
                return FLASH_TIMEOUT_REACHED_ERROR;
            }
        }
        /* Read Status Register */
        OSPIExecuteSTIGWriteCommand(XspiStigConifgReg);
    } while (OSPIGetSTIGDataRegister(OSPI_STIG_READ_DATA_LOWER) & OSPI_FLASH_STA_REG_WIP);

    return FLASH_STATUS_SUCCESS;
}

/*
 * ======== FlashExecuteEraseSTIGCommand ========
 */
void __attribute__((section(".TI.ramfunc")))
FlashExecuteEraseSTIGCommand(uint8_t EraseOpcode, uint32_t EraseAddr_en, uint32_t srcEraseAddr)
{

    OSPISTIGConfig_t XspiStigRegConfig = {0};

    if (EraseAddr_en == 1)
    {
        OSPISetCommandAddress(srcEraseAddr);
    }

    /* Set wren command before erase command */
    XspiStigRegConfig.stigOpcode = OSPI_COMMAND_WREN;
    OSPIExecuteSTIGWriteCommand(XspiStigRegConfig);

    memset(&XspiStigRegConfig, 0, sizeof(XspiStigRegConfig));
    XspiStigRegConfig.stigOpcode       = EraseOpcode;
    XspiStigRegConfig.stigAddrEn       = EraseAddr_en;
    XspiStigRegConfig.stigAddrNumBytes = 0x2;
    OSPIExecuteSTIGWriteCommand(XspiStigRegConfig);
}

/*
 * ======== FlashSectorErase ========
 */
FlashEraseStatus __attribute__((section(".TI.ramfunc")))
FlashSectorErase(uint32_t eraseStartAddr, uint32_t sectorEraseOpcode, uint32_t sectorEraseTimeOut)
{
    uint32_t status = FLASH_ERASE_ERROR;

    /* OTFDE Disable */
    FlashSetOTFDE(FLASH_OTFDE_DISABLE);
    status = FlashExecutePolling(sectorEraseTimeOut);

    FlashExecuteEraseSTIGCommand(sectorEraseOpcode, 1, eraseStartAddr);

    status = FlashExecutePolling(sectorEraseTimeOut);

    if (status != FLASH_STATUS_SUCCESS)
    {
        status = FLASH_ERASE_TIMEOUT;
    }
    /* OTFDE Enable */
    FlashSetOTFDE(FLASH_OTFDE_ENABLE);
    return status;
}

/*
 * ======== FlashSetTickPeriod ========
 */
void FlashSetTickPeriod(uint32_t TickPeriod)
{
    flashClockPTickPeriod = TickPeriod;
}

/*
 *  ======== FlashClockPCheckTimeout ========
 *
 * @brief Return indication if configurable timeout excedded.
 *
 * @param[in] StartTick The start Time from which we count #TimerInMicroSec Ticks in micro seconds,
 * if exceeds stop counting #getClockPTickUs.
 *
 * @param[in] TimerInMicroSec Configured time in micro seconds,
 * if exceeds stop counting #getClockPTickUs.
 *
 * @return bool
 * false - Timeout occur
 * true  - Timeout not occur
 *
 */
static bool __attribute__((section(".TI.ramfunc")))
FlashClockPCheckTimeout(uint32_t StartTick, uint32_t TimerInMicroSec)
{
    uint32_t currTick = getClockPTickUs();

    if ((currTick - StartTick) > TimerInMicroSec)
    {
        return false;
    }

    return true;
}

/*
 *  ======== getClockPTickUs ========
 *
 * @brief Return the current ClockP tick value.
 *
 * @return The current ClockP tick value.
 *
 * @note the global variable #flashClockPTickPeriod will be set by
 * #ClockP_getSystemTickPeriod() before entering RAM routiens.
 *
 */
static uint32_t __attribute__((section(".TI.ramfunc"))) getClockPTickUs(void)
{
    return (HWREG(SYSTIM_BASE + SYSTIM_O_TIME1U) / flashClockPTickPeriod);
}

/*
 *  ======== FlashGetBound ========
 *
 * @brief Return a bound to obtain an efficient read/write commands through UDMA.
 *
 * @param[in] directionMode XIP_UDMA_DIRECTION_INT_TO_EXT or XIP_UDMA_DIRECTION_EXT_TO_INT
 *                          INT: internal RAM
 *                          EXT: external memory
 *
 * @return Bound value in bytes.
 *
 */
static uint32_t FlashGetBound(uint8_t directionMode)
{
    /* Set resolution, in bytes */
    if (directionMode == XIP_UDMA_DIRECTION_INT_TO_EXT)
    {
        return FLASH_WR_BOUND_SIZE_IN_BYTES;
    }
    else
    {
        return FLASH_RD_BOUND_SIZE_IN_BYTES;
    }
}

/*
 *  ======== FlashUDMAOperationStatus ========
 *
 * @brief return UDMA job status.
 *
 * @param[in] channelSelect check the status of one of the two DMA channels
 * - \ref XIP_UDMA_SECURE_CHANNEL
 * - \ref XIP_UDMA_NON_SECURE_CHANNEL
 *
 * @return status FLASH_UDMA_JOB_DONE or FLASH_UDMA_JOB_ERROR
 *         after checking if UDMA job was completed.
 */
static FlashUdmaJobStatus FlashUDMAOperationStatus(uint32_t channelSelect)
{
    uint32_t jobStatus;

    while (XIPGetUDMAChannelProgressingStatus(channelSelect) == XIP_UDMA_CHANNEL_STATUS_PROGRESS) {};

    while (XIPGetUDMAChannelWordsLeft(channelSelect) != 0) {};

    jobStatus = XIPGetUDMAIrqStatus(channelSelect);
    if (jobStatus == XIP_UDMA_JOB_IRQ_STATUS_DONE)
    {
        return FLASH_UDMA_JOB_DONE;
    }
    else
    {
        return FLASH_UDMA_JOB_ERROR;
    }
}

/*
 *  ======== FlashPartitioningUDMATransaction ========
 *
 * @brief drive UDMA transaction according to write/read jobs restrictions.
 *
 * @param[in] srcAddr the start address from where to read the data
 *
 * @param[in] dstAddr the start address where to place the data
 *
 * @param[in] length number of bytes to transfer
 *
 * @param[in] directionMode XIP_UDMA_DIRECTION_INT_TO_EXT or XIP_UDMA_DIRECTION_EXT_TO_INT
 *                          INT: internal RAM
 *                          EXT: external memory
 *
 * @param[in] channelSelect one of the two DMA channels (SECURED & NON-SECURED)
 * - \ref XIP_UDMA_SECURE_CHANNEL
 * - \ref XIP_UDMA_NON_SECURE_CHANNEL
 *
 * @note use only SECURED channel see Jira: LPRFXXWARE-979
 */
static void FlashPartitioningUDMATransaction(uint32_t *srcAddr,
                                             uint32_t *dstAddr,
                                             uint32_t lengthBytes,
                                             uint8_t directionMode,
                                             uint32_t channelSelect)
{
    uint32_t JobStatus;
    uint32_t bound;
    uint32_t startAddr;

    if ((uint8_t)directionMode == XIP_UDMA_DIRECTION_EXT_TO_INT)
    {
        startAddr = (uint32_t)srcAddr;
    }
    else /* XIP_UDMA_DIRECTION_INT_TO_EXT */
    {
        startAddr = (uint32_t)dstAddr;
    };

    bound = FlashGetBound(directionMode); /* Bound should not equal '0'*/

    /* Calculate srcAddr offset from bound [Bytes]
     * assume bound is power of two
     */

    uint32_t sourceOffsetToGrid = startAddr & (bound - 1);

    /* AlignedJobLength in Bytes */
    uint32_t alignedJobLength = bound - sourceOffsetToGrid;

    /* Check if source address is not aligned to bound
     * and check the size to be copy is actually cross the bound
     */
    if (sourceOffsetToGrid != 0 && lengthBytes > alignedJobLength)
    {
        /* Align transaction - transact the first bytes between the source address and the followed bound
         * in order to align the original srcAddr to the bound.
         */
        JobStatus = XIPStartUDMATransaction(srcAddr, dstAddr, alignedJobLength / 4, directionMode, channelSelect);

        /* Return an error if UDMA is busy and is unable to start a new job */
        if (JobStatus != FLASH_STATUS_SUCCESS)
        {
            /* Return in case of an error.
             * The error check will be in the callback function.
             */
            return;
        }

        if (FlashUDMAOperationStatus(channelSelect) == FLASH_UDMA_JOB_DONE)
        {
            /* Update parameters */
            srcAddr = (uint32_t *)((uint32_t)srcAddr + alignedJobLength);
            dstAddr = (uint32_t *)((uint32_t)dstAddr + alignedJobLength);
            lengthBytes -= alignedJobLength;
        }
        else
        {
            /* Return in case of an error.
             * The error check will be in the callback function.
             */
            return;
        }
    }

    /* Transact the rest of lengthBytes (when previous align procedure has been executed)
     * or directly when original srcAddr aligned to bound.
     */
    while (lengthBytes > 0)
    {
        /* Condition for the optional last remaining bytes (when lengthBytes is not aligned to bound) */
        uint32_t transSizeBytes;
        if (lengthBytes > bound)
        {
            transSizeBytes = bound;
        }
        else
        {
            transSizeBytes = lengthBytes;
        }

        JobStatus = XIPStartUDMATransaction(srcAddr, dstAddr, transSizeBytes / 4, directionMode, channelSelect);

        /* Return an error if UDMA is busy and is unable to start a new job */
        if (JobStatus != FLASH_STATUS_SUCCESS)
        {
            /* Return in case of an error.
             * The error check will be in the callback function.
             */
            return;
        }

        if (FlashUDMAOperationStatus(channelSelect) == FLASH_UDMA_JOB_DONE)
        {
            /* Update parameters */
            srcAddr = (uint32_t *)((uint32_t)srcAddr + transSizeBytes);
            dstAddr = (uint32_t *)((uint32_t)dstAddr + transSizeBytes);
            lengthBytes -= transSizeBytes;
        }
        else
        {
            /* Return in case of an error.
             * The error check will be in the callback function
             */
            return;
        }
    }
}
