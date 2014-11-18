/*
 ===============================================================================
 Name        : Storage data to flash memory
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/18
 Copyright   : Copyright (C) www.embeda.com.tw
 Description :
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

class CStorage: public CPeripheral {
public:
	CStorage(uint16_t size, uint32_t addr=0);

	uint32_t write(const void *buf, uint16_t size, uint16_t offset=0);
	uint32_t read(void *buf, uint16_t size, uint16_t offset=0);
	uint32_t clear();

	uint16_t size();
	uint32_t addr();

	static uint32_t total_size();
	static uint32_t start_addr();

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
