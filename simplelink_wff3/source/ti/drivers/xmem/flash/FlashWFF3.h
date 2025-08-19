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
 *  ========== FlashWFF3.h ==========
 */

#ifndef ti_drivers_nvs_flash_FlashWFF3__include
#define ti_drivers_nvs_flash_FlashWFF3__include

#include <stdint.h>
#include <string.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/xip.h)
#include DeviceFamily_constructPath(driverlib/ospi.h)
#include DeviceFamily_constructPath(driverlib/debug.h)

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Values that can be returned from the API functions
 */
#define FLASH_STATUS_SUCCESS         0x00000000 /*!< Function completed successfully */
#define FLASH_TIMEOUT_REACHED_ERROR  (-1300)    /*!< timeout status error */
/*
 * Configuration values that should be passed to #XIPStartUDMATransaction()
 * as the directionMode parameter.
 */
/*!< UDMA Data movement boundary for write command (page program) Internal memory to External memory */
#define FLASH_WR_BOUND_SIZE_IN_BYTES 64U
/*!< UDMA Data movement boundary for read command External memory to Internal memory */
#define FLASH_RD_BOUND_SIZE_IN_BYTES 256U

/* Defines supports bit manipulation macros #BITMASK_x_0() & #BITMASK_x_y() */
#define __IF__(x)   (x)
#define __THEN__(x) ? (x)
#define __ELSE__(x)     : (x)
#define __ELSE_IF__(x)  : (x)

/*!
 * BITMASK_x_0() returns a bit mask of "1" from Bits[x:0]
 *
 * E.g., for x=5
 *
 * BITMASK_x_0(5) = ........111111     Bits[5:0] = "111111"
 * BITMASK_x_0(0) = .............1     Bits[0:0] = "000001"
 *
 */
#define BITMASK_x_0(x)                                                                 \
    (__IF__((x) == 31)               /* For x==31, we immediately return 0xFFFFFFFF */ \
     __THEN__(0xFFFFFFFF)            /* For other x, we return 2^(x+1) - 1.         */ \
     __ELSE__((1 << ((x) + 1)) - 1)) // MACRO BITMASK_x_0() //

/*!
 * BITMASK_x_y() returns a bit mask of "1" from Bits[x:y]
 * (naturally, x >= y should be enforces by the caller!!)
 *
 * E.g., for x=5, y=2
 *
 * BITMASK_x_y(5,5) = ......1.....     Bits[5:5] = "100000"
 * BITMASK_x_y(5,2) = ......1111..     Bits[5:0] = "111100"
 * BITMASK_x_0(5,1) = ......11111.     Bits[5:1] = "111110"
 * BITMASK_x_0(5,0) = ......111111     Bits[5:0] = "111111"
 *
 */
#define BITMASK_x_y(x, y)                                                                             \
    (__IF__((y) == 0)                               /* For y==0, we return Bits[x:0]               */ \
     __THEN__(BITMASK_x_0(x))                       /* For y> 0, we return Bits[x:0] - Bits[y-1:0] */ \
     __ELSE__(BITMASK_x_0(x) - BITMASK_x_0((y)-1))) // MACRO BITMASK_x_y(). //

typedef enum
{
    FLASH_OTFDE_DISABLE = 0, /*!< Bit configuration to disable OTFDE control over XSPI */
    FLASH_OTFDE_ENABLE  = 1  /*!< Bit configuration to enable OTFDE control over XSPI */
} FlashOtfdeStateSet;

typedef enum
{
    FLASH_UDMA_JOB_DONE  = 0, /*!< UDMA job completed successfully */
    FLASH_UDMA_JOB_ERROR = 1  /*!< UDMA job did not completed successfully */
} FlashUdmaJobStatus;

/* Erase status */
typedef enum
{
    FLASH_ERASE_DONE    = 0, /*!< Erase command completed successfully */
    FLASH_ERASE_TIMEOUT = 1, /*!< Erase command completed with timeout */
    FLASH_ERASE_ERROR   = 2  /*!< Erase command did not completed successfully */
} FlashEraseStatus;

/*
 *Functions
 */

/*!
 * @brief Read from external memory.
 *
 * This function call to #XIPStartUDMATransaction() in order to execute
 * copy transaction from external memory to internal memory.
 *
 * @param[in] readFromAddr is a pointer to the external memory source data.
 * @param[in] writeToAddr is a pointer to the internal memory destination data.
 * @param[in] length is the number of bytes to transfer.
 *
 * @note Tested with flash only (did not test with PSRAM)
 */
void FlashRead(uint32_t *readFromAddr, uint32_t *writeToAddr, uint32_t length);

/*!
 * @brief Write to external memory.
 *
 * This function call to #XIPStartUDMATransaction() in order to execute
 * copy transaction from internal memory to external memory.
 *
 * @param[in] readFromAddr is a pointer to the internal memory source data.
 * @param[in] writeToAddr is a pointer to the external memory destination data.
 * @param[in] length is the number of bytes to transfer.
 *        Maximum configurable job size - 1 Mega byte (256K Words).
 *
 * @note Tested with flash only (did not test with PSRAM)
 */
void FlashWrite(uint32_t *readFromAddr, uint32_t *writeToAddr, uint32_t length);

/*!
 * @brief Enable/Disable the OTFDE.
 *
 * @param[in] setState is the required state to configure #FlashOtfdeStateSet.
 */
void FlashSetOTFDE(uint8_t setState);

/*!
 * @brief read flash status register until WIP (write in process) indication is free.
 *
 * This function can be called by nay function that execute on going process
 * such as #FlashSectorErase().
 *
 * @param[in] timeout The maximum time in system ticks (microsecond) for the transaction
 *  to complete.
 *  If transaction will not complete before timeout reatched
 *  @return status transaction complete:
 *  #FLASH_STATUS_SUCCESS        - Trasaction successfuly completed.
 *  #FLASH_TIMEOUT_REACHED_ERROR - Timeout, transaction failed.
 */
uint32_t FlashExecutePolling(uint32_t timeout);

/*!
 * @brief Execute erase Flash based on STIG command.
 *
 * @param[in] EraseOpcode is the erase command to drive on flash interface.
 *
 * @param[in] EraseAddr_en set in case the STIG command needs to use #srcEraseAddr.
 *
 * @param[in] srcEraseAddr from where to start the flash erase.
 */
void FlashExecuteEraseSTIGCommand(uint8_t EraseOpcode, uint32_t EraseAddr_en, uint32_t srcEraseAddr);

/*!
 * @brief Execute erase Flash based on STIG command.
 *
 * @param sectorEraseOpcode is the erase command to drive on flash interface.
 *
 * @param[in] sectorEraseTimeOut The maximum time (microsecond) that sector erase command
 *                               should take.
 *                               When exceeds the time, will send FLASH_ERASE_TIMEOUT status.
 *
 * @param[in] eraseStartAddr from where to start the sector erase.
 *
 * @return #FlashEraseStatus of erase execution command:
 * #FLASH_ERASE_DONE    - sector erase command done.
 * #FLASH_ERASE_TIMEOUT - sector erase command not completed, fifnish with timeout.
 * #FLASH_ERASE_ERROR   - sector erase command failed.
 *
 */
FlashEraseStatus FlashSectorErase(uint32_t eraseStartAddr, uint32_t sectorEraseOpcode, uint32_t sectorEraseTimeOut);

/*!
 * @brief Store the ClockP period internally.
 *
 * @param TickPeriod Periodic interval in ClockP ticks
 *
 */
void FlashSetTickPeriod(uint32_t TickPeriod);

/*!
 * Mark the end of the C bindings section for C++ compilers.
 */
#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_nvs_flash_FlashWFF3__include */
