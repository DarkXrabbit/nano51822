/*
 ===============================================================================
 Name        : ble_base.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/8/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE base class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/1	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_BASE_H_
#define BLE_BASE_H_

#include <uCXpresso.h>
#include <class/object.h>
#include <class/ble/nrf51/ble.h>
#include <class/ble/nrf51/ble_gap.h>
#include <class/ble/nrf51/ble_data.h>
#include <class/ble/nrf51/ble_gatt.h>
#include <class/ble/nrf51/ble_srv_common.h>
#include <class/ble/nrf51/app_util.h>
#include <class/ble/nrf51/nrf_error.h>
#include <class/ble/nrf51/nordic_common.h>

/**
 * @defgroup Bluetooth
 * @ditails The Bluetooth LE modules
 */

/**
 * @brief 	The bleBase class is an empty base class.
 * @class 	bleBase ble_base.h "class/ble/ble_base.h"
 * @ingroup Bluetooth
 */
class bleBase : virtual public CObject {
};

#endif /* BLE_BASE_H_ */
