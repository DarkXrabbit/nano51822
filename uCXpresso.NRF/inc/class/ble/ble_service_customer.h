/*
 * ble_service_customer.h
 *
 *  Created on: 2014/9/24
 *      Author: Jason
 */

#ifndef BLE_SERVICE_CUSTOMER_H_
#define BLE_SERVICE_CUSTOMER_H_

#include <class/ble/ble_device.h>

class bleServiceCustomer: public bleService {
public:
	bleServiceCustomer(bleDevice &ble);

	virtual bool isAvailable();

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceCustomer();
protected:
	uint16_t m_conn_handle;
	uint16_t m_service_handle;

	virtual uint32_t add_characteristic(ble_uuid128_t uuid);

	virtual void on_ble_event(xHandle evt);
	virtual void on_connected(xHandle evt);
	virtual void on_disconnected(xHandle evt);
	virtual void on_write(xHandle evt);
	virtual void on_hvc(xHandle evt);
	///@endcond
};

#endif /* BLE_SERVICE_CUSTOMER_H_ */
