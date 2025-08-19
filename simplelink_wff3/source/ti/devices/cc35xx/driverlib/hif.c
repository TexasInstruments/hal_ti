/******************************************************************************
 *  Filename:       hif.c
 *
 *  Description:    Driver for the HIF peripheral
 *
 *  Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 ******************************************************************************/
#include "hif.h"
#include "../inc/hw_hif.h"

#define HIF_BLOCK_SIZE_BYTES          (16) // this is the maximum that can be set
#define HIF_DMA_WORD_SIZE_4B_IN_BYTES (4)
#define HIF_DMA_BLOCK_SIZE_IN_WORDS   ((HIF_BLOCK_SIZE_BYTES / HIF_DMA_WORD_SIZE_4B_IN_BYTES) - 1)

#define STATUS_PROCESSING (0x0)   // Processing.
#define STATUS_TRANS_DONE (0x1)   // Transaction Done.
#define STATUS_ABORT      (0x10)  // Channel Aborted by SW.
#define STATUS_EXCEPTION  (0x100) // Exception.

#define RX_DATA_SIZE_OF_RECV_RX_HEADER (16)

typedef enum
{
    HIF_MODE_DIRECT_ACCESS_WR = 0x0, // write without using DMA
    HIF_MODE_DMA_WR           = 0x1, // write using DMA
    HIF_MODE_DIRECT_ACCESS_RD = 0x2, // read without using DMA
    HIF_MODE_DMA_RD           = 0x3, // read using DMA
} HIF_MODE;

#define RD_DMA_IF_EN_WRCL (0x1)
#define HOST_CNYS_PATTERN (0xC5C5C5C5UL)
#define HOST_SYNC_PATTERN (0x5C5C5C5CUL)

#define NAB_READ_DATA_OPCODE (0x940BU)

#define ALIGN_TO_4(x) (((x) + 3) & (~3)) // Rounds up x to the nearest multiple of 4

typedef struct
{
    uint32_t syn;    // init word = HOST_SYNC_PATTERN
    uint16_t opcode; // NAB opcode, should always be NAB_READ_DATA_OPCODE
    uint16_t len;    // should be always set to 4
    uint16_t length; // number of bytes to read
    uint8_t sd;      // unused, should be always set to 0
    uint8_t flags;   // unused, should be always set to 0
} recvRxData_t;

int32_t HIFReadDirect(uint8_t *destStartAddr, uint16_t length);
int32_t HIFWriteDirect(uint8_t *srcStartAddr, uint16_t length);

//*****************************************************************************
//
// HIF transport
// 1.  INIT DMA Channel
// 2.  INIT HIF
//
//*****************************************************************************
int32_t HIFInit(uint32_t dmaChannel)
{
    DMAInitChannel((uint32_t)dmaChannel, DMA_PERIPH_HIF);
    DMAConfigureChannel(dmaChannel, HIF_DMA_BLOCK_SIZE_IN_WORDS, DMA_WORD_SIZE_4B, 0);
    // Configure HIF Threshold --> has to align with DMA_BLK_SIZE
    HWREG(HIF_BASE + HIF_O_FIFOTH) = (HIF_DMA_BLOCK_SIZE_IN_WORDS - 1) & HIF_FIFOTH_THR_M;
    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// Read from NAB , direct read
//
//*****************************************************************************

int32_t HIFReadDirect(uint8_t *destStartAddr, uint16_t length)
{
    if ((length & 0x3) != 0)
    {
        return HIF_ERR_NOT_ALIGN; // length not aligned 4
    }

    // Changing mode only after write FIFO is empty
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_RD;

    while (length > 0)
    {
        // Wait for FIFO to have some data from the NAB
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};

        // Read word (4 bytes)
        *((uint32_t *)(destStartAddr)) = HWREG(HIF_BASE + HIF_O_ICRDFIFO);

        destStartAddr += 4;
        length -= 4;
    }
    return HIF_STATUS_SUCCESS;
}

//*****************************************************************************
//
// Read from NAB using DMA
//
//*****************************************************************************

int32_t HIFRead(uint32_t dmaChannel,
                uint32_t srcAddr,
                uint8_t *destStartAddr,
                uint16_t length,
                uint32_t *actualLengthRead)
{
    bool useBurstReq = 1;
    uint32_t temp;
    uint32_t offset = 0;
    volatile uint16_t lengthAfterAlignment;
    uint32_t chStatus;
    recvRxData_t recvRxData;

    // Change mode to write
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_WR;

    if (srcAddr == HIF_NAB_DATA_ADDR)
    {
        if (length < 16)
        {
            // Minimum length to read is 16 bytes (NAB_header_t is not included in the length)
            return HIF_ERR_BUFFER_OVERFLOW;
        }
        recvRxData.syn    = HOST_SYNC_PATTERN;
        recvRxData.opcode = NAB_READ_DATA_OPCODE;
        recvRxData.len    = 4;
        recvRxData.length = length - RX_DATA_SIZE_OF_RECV_RX_HEADER; // It includes all bytes that comes after the
                                                                     // descriptor word
        recvRxData.sd     = 0;
        recvRxData.flags  = 0;

        // Request for Rx data
        if (HIFWriteDirect((uint8_t *)&recvRxData, sizeof(recvRxData)) != HIF_STATUS_SUCCESS)
        {
            return HIF_ERR_WRITE_FAIL; // dma write failure
        }

        lengthAfterAlignment = length;
        *actualLengthRead    = length;

        // Changing mode only after write FIFO is empty
        HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_RD;

        // Wait until read FIFO is not empty, i.e the NAB set data on the read FIFO
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
    }
    else if (srcAddr == HIF_NAB_CONTROL_ADDR)
    {
        // Wait until write FIFO is not full
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};

        // Write 32-bit word to the event mailbox
        HWREG(HIF_BASE + HIF_O_ICWRFIFO) = HOST_CNYS_PATTERN;

        // The NAB copy from its MAILBOX the answer for the HOST_CNYS_PATTERN
        // wait until write FIFO is empty
        while (!((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};

        // Changing mode only after write FIFO is empty
        HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_RD;
        // Wait until read FIFO is not empty
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
        // Read first word (4 bytes)
        temp                                    = HWREG(HIF_BASE + HIF_O_ICRDFIFO);
        *((uint32_t *)(destStartAddr + offset)) = temp;
        offset += 4;

        // Wait until read FIFO is not empty
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_EMP_M) >> HIF_FIFOSTA_EMP_S)) {};
        // read second word (4 bytes)
        temp                                    = HWREG(HIF_BASE + HIF_O_ICRDFIFO);
        *((uint32_t *)(destStartAddr + offset)) = temp;
        // Read what is the actual number of bytes that the NAB has to send
        *actualLengthRead                       = (temp >> 16) & 0xFFFF;
        offset += 4;

        if ((ALIGN_TO_4(*actualLengthRead) + 4 /*header*/) > length) // verify that there is no overflow
        {
            return HIF_ERR_BUFFER_OVERFLOW;
        }
        lengthAfterAlignment = (uint16_t)ALIGN_TO_4((*actualLengthRead));
    }
    else
    {
        return HIF_ERR_INVALID_SRC_ADDR; // src address not supported
    }

    // Read the data using the DMA from the relevant FIFO buffer
    // Change mode to read
    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DMA_RD;

    DMAConfigureChannelFlags(dmaChannel, DMA_CONFIG_SRC_PTR_FIFO);
    DMAStartTransaction(dmaChannel,
                        (uint32_t *)(HIF_BASE + HIF_O_ICRDFIFO),
                        (uint32_t *)((uint8_t *)destStartAddr + offset),
                        lengthAfterAlignment,
                        useBurstReq);

    // Wait for the DMA transaction to finish
    while ((chStatus = DMAGetChannelStatus(dmaChannel)) == STATUS_PROCESSING) {};
    if (chStatus & (STATUS_ABORT | STATUS_EXCEPTION)) // this is fatal error and should not happen
    {
        return HIF_ERR_DMA_READ_FAIL; // DMA write failure
    }

    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// Write to the NAB
//
//*****************************************************************************

int32_t HIFWriteDirect(uint8_t *srcStartAddr, uint16_t length)
{
    if ((length & 0x3) != 0)
    {
        return HIF_ERR_NOT_ALIGN; // length not aligned 4
    }

    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DIRECT_ACCESS_WR;
    while (length > 0)
    {
        // Wait until FIFO is not full
        while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};
        // event mailbox
        HWREG(HIF_BASE) = (uint32_t)(*((uint32_t *)srcStartAddr));

        srcStartAddr += 4;
        length -= 4;
    }
    // Wait until FIFO is not full
    while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};

    return HIF_STATUS_SUCCESS; // success
}

//*****************************************************************************
//
// Write to the NAB using DMA
//
//*****************************************************************************

int32_t HIFWrite(uint32_t dmaChannel, uint8_t *srcStartAddr, uint16_t length)
{
    bool useBurstReq = 1;
    uint32_t chStatus;

    if ((length & 0x3) != 0)
    {
        return HIF_ERR_NOT_ALIGN; // length not aligned 4
    }

    HWREG(HIF_BASE + HIF_O_MOD) = HIF_MODE_DMA_WR;

    // Wait until FIFO is not full
    while (((HWREG(HIF_BASE + HIF_O_FIFOSTA) & HIF_FIFOSTA_FULL_M) >> HIF_FIFOSTA_FULL_S)) {};

    DMAConfigureChannelFlags(dmaChannel, DMA_CONFIG_DST_PTR_FIFO);

    DMAStartTransaction(dmaChannel,
                        (uint32_t *)((uint8_t *)srcStartAddr),
                        (uint32_t *)(HIF_BASE + HIF_O_ICWRFIFO),
                        length,
                        useBurstReq);

    // Wait for the DMA transaction to finish
    while ((chStatus = DMAGetChannelStatus(dmaChannel)) == STATUS_PROCESSING) {};
    if (chStatus & (STATUS_ABORT | STATUS_EXCEPTION)) // this is fatal error and should not happen
    {
        return HIF_ERR_DMA_WRITE_FAIL;
    }
    return HIF_STATUS_SUCCESS; // success
}
