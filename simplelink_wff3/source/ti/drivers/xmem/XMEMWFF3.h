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
 * ========== XMEMWFF3.h ==========
 */
#ifndef ti_drivers_xmem_XMEMWFF3__include
#define ti_drivers_xmem_XMEMWFF3__include

#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define XMEM_NUM_DEVICE 1 /* In the future add support for PSRAM and increase the value by 1 */
#define XMEM_FLASH      0
#define XMEM_PSRAM      1 /* Placeholder - will be relevant when adding support for PSRAM */

/*!
 *  @brief   Successful status code returned by:
 *  #XMEMWFF3_read(), #XMEMWFF3_write(), #XMEMWFF3_erase(), or
 *  #XMEMWFF3_lock().
 *
 *  APIs returns #XMEM_STATUS_SUCCESS if the API was executed
 *  successfully.
 */
#define XMEM_STATUS_SUCCESS (0)

/*!
 *  @brief   Generic error status code returned by:
 *  #XMEMWFF3_erase(), or #XMEMWFF3_write(),
 *
 *  APIs return #XMEM_STATUS_ERROR if the API was not executed
 *  successfully.
 */
#define XMEM_STATUS_ERROR (-1)

/*!
 *  @brief An error status code returned by #XMEMWFF3_lock()
 *
 *  #XMEMWFF3_lock() will return this value if the @p timeout has expired
 */
#define XMEM_STATUS_TIMEOUT (-3)

/*!
 *  @brief An error status code returned by #XMEMWFF3_read(), #XMEMWFF3_write(), or
 *  #XMEMWFF3_erase()
 *
 *  Error status code returned if the @p offset argument is invalid
 *  (e.g., when offset + bufferSize exceeds the size of the region).
 */
#define XMEM_STATUS_INV_OFFSET (-4)

/*!
 *  @brief An error status code
 *
 *  Error status code returned by #XMEMWFF3_erase() if the @p offset argument is
 *  not aligned on a flash sector address.
 */
#define XMEM_STATUS_INV_ALIGNMENT (-5)

/*!
 *  @brief An error status code returned by #XMEMWFF3_erase() and #XMEMWFF3_write()
 *
 *  Error status code returned by #XMEMWFF3_erase() if the @p size argument is
 *  not a multiple of the flash sector size, or if @p offset + @p size
 *  extends past the end of the region.
 */
#define XMEM_STATUS_INV_SIZE (-6)

/*!
 *  @brief An error status code returned by #XMEMWFF3_write()
 *
 *  #XMEMWFF3_write() will return this value if #XMEMWFF3_WRITE_PRE_VERIFY is
 *  requested and a flash location can not be changed to the value
 *  desired.
 */
#define XMEM_STATUS_INV_WRITE (-7)

/*!
 *  @brief   An error status code returned by #XMEMWFF3_write()
 *
 *  XMEMWFF3_write() will return this value if #XMEM_WRITE_PRE_VERIFY
 *  or #XMEM_WRITE_POST_VERIFY is requested but the verification buffer has not been configured.
 */
#define XMEM_STATUS_VERIFYBUFFER (-8)

/** @}*/

/*!
 *  @brief XMEM write flags
 *
 *  The following flags can be or'd together and passed as a bit mask
 *  to #XMEMWFF3_write().
 *  @{
 */

/*!
 *  @brief Erase write flag.
 *
 *  If #XMEM_WRITE_ERASE is set in the flags passed to #XMEMWFF3_write(), the
 *  affected destination flash sectors will be erased prior to the
 *  start of the write operation.
 */
#define XMEM_WRITE_ERASE (0x1)

/*!
 *  @brief Validate write flag.
 *
 *  If #XMEM_WRITE_PRE_VERIFY is set in the flags passed to #XMEMWFF3_write(), the
 *  destination address range will be pre-tested to guarantee that the source
 *  data can be successfully written. If #XMEM_WRITE_ERASE is also requested in
 *  the write flags, then the #XMEM_WRITE_PRE_VERIFY modifier is ignored.
 */
#define XMEM_WRITE_PRE_VERIFY (0x2)

/*!
 *  @brief Validate write flag.
 *
 *  If #XMEM_WRITE_POST_VERIFY is set in the flags passed to #XMEMWFF3_write(), the
 *  destination address range will be tested after the write is finished to
 *  verify that the write operation was completed successfully.
 */
#define XMEM_WRITE_POST_VERIFY (0x4)

/** @} */

/*!
 *  @brief Special #XMEMWFF3_lock() timeout values
 *  @{
 */

/*!
 *  @brief    #XMEMWFF3_lock() Wait forever define
 */
#define XMEM_LOCK_WAIT_FOREVER (SemaphoreP_WAIT_FOREVER)

/*!
 *  @brief    #XMEMWFF3_lock() No wait define
 */
#define XMEM_LOCK_NO_WAIT (SemaphoreP_NO_WAIT)

/** @} */

/*!
 *  @brief      XMEMWFF3 hardware attributes
 *
 *  @note       Currently XMEMWFF3 does not require any attributes
 */

typedef struct
{
    size_t sectorSize;         /*!< Erase sector size - fetched during init() */
    size_t regionBase;         /*!< Offset from base of Ext flash - fetched during init() */
    size_t regionStartAddr;    /*!< The regionBase translated to logical address - fetched during init() */
    size_t regionOffset;       /*!< Offset from regionbase to regionStartAddr - fetched during init() */
    size_t regionSize;         /*!< The size of the region in bytes - fetched during init() */
    size_t sectorEraseOpcode;  /*!< Erase sector command opcode - fetched during init() */
    size_t sectorEraseTimeOut; /*!< Erase Maximum Process Time  - fetched during init() */
    size_t verifyBufSize;      /*!< Write Pre/Post verify buffer size */
} XMEMWFF3_HWAttrs;

/*!
 *  @brief      XMEMWFF3 Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct
{
    bool opened; /* Has this region been opened */
} XMEMWFF3_Object;

/*!
 *  @brief      XMEM attributes
 *
 *  The address of an XMEM_Attrs structure is passed to #XMEMWFF3_getAttrs().
 *
 *  @sa     #XMEMWFF3_getAttrs()
 */
typedef struct
{
    void *regionBase;  /*!< Base address of the XMEM region. */
    size_t regionSize; /*!< XMEM region size in bytes. */
    size_t sectorSize; /*!< Erase sector size in bytes. This attribute is
                            device specific. */
} XMEM_Attrs;

/*!
 *  @brief      A handle that is returned from the #XMEMWFF3_open() call.
 */
typedef struct XMEM_Config_ *XMEM_Handle;

/*!
 *  @brief  XMEM Global configuration
 *
 *  The XMEM_Config structure contains a set of pointers used to characterize
 *  the XMEM driver implementation.
 *
 *  This structure needs to be defined before calling #XMEMWFF3_init() and it must
 *  not be changed thereafter.
 *
 *  @sa     #XMEMWFF3_init()
 */
typedef struct XMEM_Config_
{
    /*! Pointer to a driver specific data object */
    void *object;

    /*! Pointer to a driver specific hardware attributes structure */
    void const *hwAttrs;
} XMEM_Config;

/*!
 *  @brief  Function to close an #XMEM_Handle.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 *
 *  @sa     #XMEMWFF3_open()
 */
void XMEMWFF3_close(XMEM_Handle handle);

/*!
 *  @brief  Erase @p size bytes of the region beginning at @p offset bytes
 *  from the base of the region referenced by the #XMEM_Handle.
 *
 *  @warning Erasing internal flash on most devices can introduce
 *  significant interrupt latencies while the erase operation is in
 *  in progress. The user may want to surround certain real-time
 *  critical code sections with #XMEMWFF3_lock() and #XMEMWFF3_unlock() calls in order
 *  to prevent uncoordinated flash erase operations from negatively
 *  impacting performance.
 *
 *  @param   handle     A handle returned from #XMEMWFF3_open()
 *
 *  @param   offset     The byte offset into the XMEM region to start
 *                      erasing from (must be erase sector aligned)
 *
 *  @param   size       The number of bytes to erase (must be integer
 *                      multiple of sector size)
 *
 *  @retval  #XMEM_STATUS_SUCCESS         Success.
 *  @retval  #XMEM_STATUS_INV_ALIGNMENT   If @p offset is not aligned on
 *                                       a sector boundary
 *  @retval  #XMEM_STATUS_INV_OFFSET      If @p offset exceeds region size
 *  @retval  #XMEM_STATUS_INV_SIZE        If @p size or @p offset + @p size
 *                                       exceeds region size, or if @p size
 *                                       is not an integer multiple of
 *                                       the flash sector size.
 *  @retval  #XMEM_STATUS_ERROR           If an internal error occurred
 *                                       erasing the flash.
 */
int_fast16_t XMEMWFF3_erase(XMEM_Handle handle, size_t offset, size_t size);

/*!
 *  @brief  Function to get the XMEM attributes
 *
 *  This function will populate a #XMEM_Attrs structure with attributes
 *  specific to the memory region associated with the #XMEM_Handle.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 *
 *  @param  attrs       Location to store attributes.
 */
void XMEMWFF3_getAttrs(XMEM_Handle handle, XMEM_Attrs *attrs);

/*!
 *  @brief  Function to initialize the XMEM module
 *
 *  @pre    The XMEM_config structure must exist and be persistent before this
 *          function can be called. This function must also be called before
 *          any other XMEM APIs.
 */
void XMEMWFF3_init(void);

/*!
 *  @brief  Function to lock the XMEM driver
 *
 *  This function is provided in the event that the user needs to
 *  perform some flash related operation not provided by the XMEM
 *  driver API set or if the user simply needs to block flash operations
 *  for a period of time.
 *
 *  For example, the interrupt latency introduced
 *  by an uncoordinated flash write operation could interfere with some
 *  critical operation being performed by the application.
 *
 *  #XMEMWFF3_lock() prevents any other thread from initiating
 *  read, write, or erase operations while the user is performing an
 *  operation which is incompatible with those functions.
 *
 *  When the application no longer needs to block flash operations by
 *  other threads, #XMEMWFF3_unlock() must be called to allow XMEM write or erase
 *  APIs to complete.
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 *
 *  @param  timeout     Timeout (in milliseconds) to wait,
 *                      or #XMEM_LOCK_WAIT_FOREVER, #XMEM_LOCK_NO_WAIT
 *
 *  @retval  #XMEM_STATUS_SUCCESS         Success.
 *  @retval  #XMEM_STATUS_TIMEOUT         If @p timeout has expired.
 */
int_fast16_t XMEMWFF3_lock(XMEM_Handle handle, uint32_t timeout);

/*!
 *  @brief  Open an XMEM region for reading and writing.
 *
 *  @pre    #XMEMWFF3_init() was called.
 *
 *  @param  index         Index in the #XMEM_Config table of the region
 *                        to manage.
 *
 *  @return  A non-zero handle on success, else NULL.
 */
XMEM_Handle XMEMWFF3_open(uint_least8_t index);

/*!
 *  @brief   Read data from the XMEM region associated with the #XMEM_Handle.
 *
 *  @param   handle     A handle returned from #XMEMWFF3_open()
 *
 *  @param   offset     The byte offset into the XMEM region to start
 *                      reading from.
 *
 *  @param   buffer     A buffer to copy the data to.
 *
 *  @param   bufferSize The size of the buffer (number of bytes to read).
 *
 *  @retval  #XMEM_STATUS_SUCCESS     Success.
 *  @retval  #XMEM_STATUS_INV_OFFSET  If @p offset + @p size exceed the size
 *                                    of the region.
 */
int_fast16_t XMEMWFF3_read(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize);

/*!
 *  @brief  Function to unlock the XMEM driver
 *
 *  This function allows XMEM write and erase operations to proceed after being
 *  temporarily inhibited by a call to #XMEMWFF3_lock().
 *
 *  @param  handle      A handle returned from #XMEMWFF3_open()
 */
void XMEMWFF3_unlock(XMEM_Handle handle);

/*!
 *  @brief   Write data to the XMEM region associated with the #XMEM_Handle.
 *
 *  @warning Writing to internal flash on most devices can introduce
 *  significant interrupt latencies while the write operation is in
 *  in progress. The user may want to surround certain real-time
 *  critical code sections with #XMEMWFF3_lock() and #XMEMWFF3_unlock() calls in order
 *  to prevent uncoordinated flash write operations from negatively
 *  impacting performance.
 *
 *  @param   handle     A handle returned from #XMEMWFF3_open()
 *
 *  @param   offset     The byte offset into the XMEM region to start
 *                      writing.
 *
 *  @param   buffer     A buffer containing data to write to
 *                      the XMEM region.
 *
 *  @param   bufferSize The size of the buffer (number of bytes to write).
 *
 *  @param   flags      Write flags (#XMEM_WRITE_ERASE, #XMEM_WRITE_PRE_VERIFY,
 *                      #XMEM_WRITE_POST_VERIFY).
 *
 *  @retval  #XMEM_STATUS_SUCCESS       Success.
 *  @retval  #XMEM_STATUS_ERROR         If the internal flash write operation
 *                                      failed, or if #XMEM_WRITE_POST_VERIFY
 *                                      was requested and the destination flash
 *                                      range does not match the source
 *                                      @p buffer data.
 *  @retval  #XMEM_STATUS_INV_OFFSET     If @p offset + @p size exceed the size
 *                                      of the region.
 *  @retval  #XMEM_STATUS_INV_WRITE      If #XMEM_WRITE_PRE_VERIFY is requested
 *                                      and the destination flash address range
 *                                      cannot be change to the values desired.
 *  @retval  #XMEM_STATUS_INV_ALIGNMENT  If #XMEM_WRITE_ERASE is requested
 *                                      and @p offset is not aligned on
 *                                      a sector boundary
 *  @retval  #XMEM_STATUS_VERIFYBUFFER   If #XMEM_WRITE_PRE_VERIFY or #XMEM_WRITE_POST_VERIFY
 *                                      is requested but the verification buffer has not
 *                                      been configured.
 *
 *  @remark  This call may lock a region to ensure atomic access to the region.
 */
int_fast16_t XMEMWFF3_write(XMEM_Handle handle, size_t offset, void *buffer, size_t bufferSize, uint_fast16_t flags);

/*! @endcond */

#if defined(__cplusplus)
}
#endif /* defined (__cplusplus) */

/*@}*/
#endif /* ti_drivers_xmem_XMEMWFF3__include */
