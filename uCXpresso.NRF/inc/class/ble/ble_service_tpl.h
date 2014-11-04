/*
 ===============================================================================
 Name        : Tx Power Level
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/3
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Tx Power Level Service
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/3	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_TPL_H_
#define BLE_SERVICE_TPL_H_

#include <class/ble/ble_device.h>

/**@brief Tx Power Level Service class
 * @class 	bleServiceTPL ble_service_tpl.h "class/ble/ble_service_tpl.h"
 *
 * @details This module implements the TX Power Service with the TX Power Level characteristic.
 *          During initialization it adds the TX Power Service and TX Power Level characteristic
 *          with the specified initial value to the BLE stack database.
 *
 *          It provides a function for letting the application update the TX Power Level
 *          characteristic.
 *
 * @ingroup Bluetooth
 */
class bleServiceTPL: public bleService {
public:
	/**
	 * @brief Construct the Tx Power Level class.
	 *
	 * @param[in] ble @ref bleDevice object.
	 * @param[in] initial_tx_power_level Initial value of the TX Power Level characteristic (in dBm).
	 */
	bleServiceTPL(bleDevice &ble, int8_t initial_tx_power_level=0);

	/**
	 * @brief Send the device Tx Power Level.
	 *
	 * @param[in]   tx_power_level   New TX Power Level (unit dBm, range -100 to 20).
	 *
	 * @return      NRF_SUCCESS on success, otherwise an error code.
	 */
	uint32_t send(int8_t tx_power_level);

	/**
	 * @brief the Tx Power Level Service UUID
	 */
	virtual inline uint16_t uuid() {
		return BLE_UUID_TX_POWER_SERVICE;
	}

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceTPL();
protected:
	xHandle	m_handle;
	virtual void on_ble_event(xHandle evt) {}
	///@endcond
};

#endif /* BLE_SERVICE_TPL_H_ */
