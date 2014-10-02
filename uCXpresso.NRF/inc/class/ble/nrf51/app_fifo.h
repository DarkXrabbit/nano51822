/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/**@file
 *
 * @defgroup app_fifo FIFO implementation
 * @{
 * @ingroup app_common
 *
 * @brief FIFO implementation.
 */

#ifndef __APP_FIFO_H__
#define __APP_FIFO_H__

#include <stdint.h>
#include <stdlib.h>
#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief A FIFO instance structure. Keeps track of which bytes to read and write next.
 *        Also it keeps the information about which memory is allocated for the buffer
 *        and its size. This needs to be initialized by app_fifo_init() before use.
 */
typedef struct
{
    uint8_t *          p_buf;           /**< Pointer to FIFO buffer memory.                      */
    uint16_t           buf_size_mask;   /**< Read/write index mask. Also used for size checking. */
    volatile uint32_t  read_pos;        /**< Next read position in the FIFO buffer.              */
    volatile uint32_t  write_pos;       /**< Next write position in the FIFO buffer.             */
} app_fifo_t;

/**@brief Function for initializing the FIFO.
 *
 * @param[out] p_fifo   FIFO object.
 * @param[in]  p_buf    FIFO buffer for storing data. The buffer size has to be a power of two.
 * @param[in]  buf_size Size of the FIFO buffer provided, has to be a power of 2.
 *
 * @retval     NRF_SUCCESS              If initialization was successful.
 * @retval     NRF_ERROR_NULL           If a NULL pointer is provided as buffer.
 * @retval     NRF_ERROR_INVALID_LENGTH If size of buffer provided is not a power of two.
 */
uint32_t app_fifo_init(app_fifo_t * p_fifo, uint8_t * p_buf, uint16_t buf_size);

/**@brief Function for adding an element to the FIFO.
 *
 * @param[in]  p_fifo   Pointer to the FIFO.
 * @param[in]  byte     Data byte to add to the FIFO.
 *
 * @retval     NRF_SUCCESS              If an element has been successfully added to the FIFO.
 * @retval     NRF_ERROR_NO_MEM         If the FIFO is full.
 */
uint32_t app_fifo_put(app_fifo_t * p_fifo, uint8_t byte);

/**@brief Function for getting the next element from the FIFO.
 *
 * @param[in]  p_fifo   Pointer to the FIFO.
 * @param[out] p_byte   Byte fetched from the FIFO.
 *
 * @retval     NRF_SUCCESS              If an element was returned.
 * @retval     NRF_ERROR_NOT_FOUND      If there is no more elements in the queue.
 */
uint32_t app_fifo_get(app_fifo_t * p_fifo, uint8_t * p_byte);

/**@brief Function for flushing the FIFO.
 *
 * @param[in]  p_fifo   Pointer to the FIFO.
 *
 * @retval     NRF_SUCCESS              If the FIFO flushed successfully.
 */
uint32_t app_fifo_flush(app_fifo_t * p_fifo);

/**@brief Function to return the FIFO available size.
 *
 *  @param[in]  p_fifo   Pointer to the FIFO.
 *
 *  @retval available size
 */
uint32_t app_fifo_avail(app_fifo_t * p_fifo);

/**@brief Function to return the FIFO free size.
 *
 *  @param[in]  p_fifo   Pointer to the FIFO.
 *
 *  @retval free size
 */
uint32_t app_fifo_free(app_fifo_t * p_fifo);

/**@brief Function to get a block data from FIFO.
 *
 *  @param[in]  p_fifo	Pointer to the FIFO.
 *
 *  @param[out] buf		Pointer to receive buffer
 *
 *  @size[in]	size	Indicate the size of buffer
 *
 *  @retval received size
 */
int app_fifo_get_block(app_fifo_t *p_fifo, uint8_t *buf, int size);

/**@brief Function to put a block data to FIFO.
 *
 *  @param[in]  p_fifo	Pointer to the FIFO.
 *
 *  @param[in] buf		Pointer to transmit buffer
 *
 *  @size[in]	size	Indicate the size of buffer
 *
 *  @retval transmitted size
 */
int app_fifo_put_block(app_fifo_t *p_fifo, uint8_t *buf, int size);

#ifdef __cplusplus
}
#endif
#endif // APP_FIFO_H__

/** @} */
