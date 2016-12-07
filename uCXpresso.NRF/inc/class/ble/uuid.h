/*
 ===============================================================================
 Name        : uuid.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月7日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Create UUID from a string
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月7日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef UUID_H_
#define UUID_H_

#include <class/object.h>
#include <class/ble/nrf51/ble_types.h>

class CUUID: public CObject {
public:
	ble_uuid128_t uuid;
	CUUID(const char *str);
};

#endif /* UUID_H_ */
