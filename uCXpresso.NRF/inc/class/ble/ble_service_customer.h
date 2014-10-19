/*
 ===============================================================================
 Name        : ble_service_customer.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/12
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Customer Service base class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/12	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_CUSTOMER_H_
#define BLE_SERVICE_CUSTOMER_H_

#include <class/ble/ble_device.h>
#include <class/ble/nrf51/ble_gatt.h>
#include <class/ble/nrf51/ble_gattc.h>
#include <class/ble/nrf51/ble_gatts.h>

/**@brief 	BLE customer services base class.
 * @class 	bleServiceCustomer ble_service_customer.h "class/ble/ble_service_customer.h"
 *
 * @details This class provides the service event handles for customer's service class.
 *
 * @ingroup Bluetooth
 */
class bleServiceCustomer: public bleService {
public:
	bleServiceCustomer(bleDevice &ble);

	virtual bool isAvailable();

	virtual inline uint16_t uuid() {
		return m_service_uuid;
	}

	virtual inline uint8_t uuid_type() {
		return m_uuid_type;
	}

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceCustomer();

protected:
	uint16_t		m_conn_handle;
	ble_uuid128_t	m_p_base_uuid;
	uint16_t		m_service_uuid;
	uint8_t			m_uuid_type;
	uint16_t		m_service_handle;

	virtual uint32_t service_add(ble_uuid128_t const *base_uuid, uint16_t service_uuid);

	//
	// on ble event and event dispatch
	//
	virtual void on_ble_event(xHandle evt);
	virtual void on_connected(xHandle evt);
	virtual void on_disconnected(xHandle evt);
	virtual void on_write(xHandle evt);
	virtual void on_hvc(xHandle evt);
	virtual void on_send(xHandle evt);
	///@endcond
};

#endif /* BLE_SERVICE_CUSTOMER_H_ */
