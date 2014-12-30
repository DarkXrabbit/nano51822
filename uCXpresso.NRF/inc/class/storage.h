/*
 ===============================================================================
 Name        : Storage data to flash memory
 Author      : uCXpresso
 Version     : v1.0.1
 Date		 : 2014/11/22
 Copyright   : Copyright (C) www.embeda.com.tw
 Description :
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18	v1.0.0	First Edition for nano51822						Jason
 2014/11/22 v1.0.1	Add access_wait static member.					Jason
 ===============================================================================
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <class/peripheral.h>
#include <class/semaphore.h>
#include <class/ble/nrf51/nrf_error.h>

/**
 * @brief CStorage class provides the flash memory access service.
 * @class CStorage storage.h "class/storage.h"
 * @ingroup Peripherals
 */
class CStorage: public CPeripheral {
public:
	/**
	 * @brief Constructs the storage object.
	 * @param size Number of bytes handle by the storage object.
	 * @param addr Indicate the memory address. If addr is zero, assign the address automatically.
	 */
	CStorage(uint16_t size, uint32_t addr=0);

	/**
	 * @brief Write data to storage.
	 * @param buf 		Pointer to the data buffer for write.
	 * @param size		Number of byte to write.
	 * @param offset	Offset to the address from the storage began.
	 * @return
	 * @retval NRF_SUCCESS             on success, else an error code indicating reason for failure.
	 * @retval NRF_ERROR_INVALID_STATE is returned is API is called without module initialization.
	 * @retval NRF_ERROR_NULL          if NULL parameter has been passed.
	 * @retval NRF_ERROR_INVALID_PARAM if invalid parameters are passed to the API.
	 * @retval NRF_ERROR_INVALID_ADDR  in case data address 'p_src' is not aligned.
	 * @retval NRF_ERROR_NO_MEM        in case request cannot be processed.
	 *
	 * @warning	No copy of the data is made, and hence memory provided for data source to be written
	 * 			to flash cannot be freed or reused by the application until this procedure
	 *			is complete. End of this procedure is notified to the application using the
	 *			notification callback registered by the application.
	 */
	uint32_t write(const void *buf, uint16_t size, uint16_t offset=0);

	/**
	 * @brief Read data from storage.
	 * @param buf 		Pointer to the data buffer for read
	 * @param size		Number of byte to read.
	 * @param offset	Offset to the address from the storage began.
	 * @return
	 * @retval NRF_SUCCESS             on success, else an error code indicating reason for failure.
	 * @retval NRF_ERROR_INVALID_STATE is returned is API is called without module initialization.
	 * @retval NRF_ERROR_NULL          if NULL parameter has been passed.
	 * @retval NRF_ERROR_INVALID_PARAM if invalid parameters are passed to the API.
	 * @retval NRF_ERROR_INVALID_ADDR  in case data address 'p_src' is not aligned.
	 * @retval NRF_ERROR_NO_MEM        in case request cannot be processed.
	 */
	uint32_t read(void *buf, uint16_t size, uint16_t offset=0);

	/**
	 * @brief To clear the all data in storage memory.
	 *
	 * @retval     NRF_SUCCESS             on success, else an error code indicating reason for failure.
	 * @retval     NRF_ERROR_INVALID_STATE is returned is API is called without module initialization.
	 * @retval     NRF_ERROR_NULL          if NULL parameter has been passed.
	 * @retval     NRF_ERROR_INVALID_PARAM if invalid parameters are passed to the API.
	 * @retval     NRF_ERROR_INVALID_ADDR  in case data address 'p_dst' is not aligned.
	 * @retval     NRF_ERROR_NO_MEM        in case request cannot be processed.
	 *
	 * @note       Clear operations may take time. This API however, does not block until the clear
	 *             procedure is complete. Application is notified of procedure completion using
	 *             notification callback registered by the application. 'result' parameter of the
	 *             callback suggests if the procedure was successful or not.
	 */
	uint32_t clear();

	/**
	 * @brief Retrieve the size of the storage object.
	 */
	uint16_t size();

	/**
	 * @brief Retrieve the start address of the storage object.
	 */
	uint32_t addr();

	/**
	 * @brief Retrieve the total size of the flash memory for user's data.
	 */
	static uint32_t total_size();

	/**
	 * @brief Retrieve the start address ot the flash memory for user's data.
	 */
	static uint32_t start_addr();

	/**
	 * @brief Waiting for storage access operators finish.
	 */
	static uint32_t access_wait();

	//
	/// @cond PRIVATE
	//
	virtual ~CStorage();
	virtual void onEvent(uint8_t op_code, uint32_t result, uint8_t * p_data, uint32_t data_len) { NOTHING }
protected:
	uint16_t   	m_size;
	xHandle 	m_handle;
	/// @endcond
};

#endif /* FLASH_H_ */
