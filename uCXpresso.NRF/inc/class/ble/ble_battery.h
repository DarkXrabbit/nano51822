/*
 * ble_battery.h
 *
 *  Created on: 2014/9/21
 *      Author: Jason
 */

#ifndef BLE_BATTERY_H_
#define BLE_BATTERY_H_

#include <class/ble/ble_device.h>

class bleServiceBattery: public bleService {
public:
	bleServiceBattery(bleDevice &ble, uint8_t initial_level=100);

	virtual bool isAvailable();

	virtual uint32_t send(uint8_t battery_level);

	//
	///@cond
	//
	virtual ~bleServiceBattery();
	bool m_bNotify;
protected:
	xHandle	m_handle;
	virtual void on_ble_event(xHandle evt);
	///@endcond
};

#endif /* BLE_BATTERY_H_ */
