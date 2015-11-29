/*
 ===============================================================================
 Name        : ble_rssi
 Author      : Jason
 Version     : v1.0.1
 Date		 : 2014/12/5
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : To measure current connection RSSI value.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/12	v1.0.0	First Edition									Jason
 2014/12/5	v1.0.1	Add attach/detach event handle member 			Jason
 	 	 	 	 	functions.
 ===============================================================================
 */

#ifndef BLE_RSSI_H_
#define BLE_RSSI_H_

#include <class/ble/ble_device.h>

#define RSSI_INVALID_VALUE	127

/**
 * @brief BLE RSSI service class.
 *
 * @class bleRSSI ble_rssi.h "class/ble/ble_rssi.h"
 *
 * @ingroup Bluetooth
 */
class bleRSSI: public bleService {
	/**@brief thread task handler type. */
	typedef void (*rssi_handle_t) (bleRSSI * p_rssi, int8_t rssi);
public:
	/**
	 * @brief bleRSSI constructor
	 * @param ble Pointer to @ref bleDevice object.
	 */
	bleRSSI(bleDevice &ble);

	/**
	 * @brief Check bleRSSI available.
	 * @return true if the service is available. false otherwise.
	 */
	virtual bool isAvailable();

	/**
	 * @brief Retrieve current connection RSSI value.
	 */
	inline int8_t read() {
		return m_rssi;
	}

	/**
	 * @brief Shorthand read rssi.
	 */
	inline operator int8_t () {
		return read();
	}

	/**
	 * @brief Attach the rssi event handle
	 */
	inline void attach(rssi_handle_t handle) {
		m_rssi_handle = handle;
	}

	/**
	 * @brief Detach the rssi event handle
	 */
	inline void detach() {
		m_rssi_handle = NULL;
	}

protected:
	/**
	 * @brief On rssi changed event.
	 * @param[in] rssi Current connection rssi.
	 */
	virtual void onEvent(int8_t rssi);

	//
	///@cond
	//
public:
	virtual ~bleRSSI();
protected:
	int8_t			m_rssi;
	uint16_t    	m_conn_handle;
	rssi_handle_t	m_rssi_handle;
	virtual void on_ble_event(ble_evt_t * p_ble_evt);
	///@endcond
};

/**\example /ble/ble_rssi_measure/src/main.cpp
 * This is an example of how to use the bleRSSI class.
 * More details about this example.
 */

#endif /* BLE_RSSI_H_ */
