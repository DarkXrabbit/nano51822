/*
 ===============================================================================
 Name        : ble_service_bat.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/8/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Battery Level Service
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/1	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_BATTERY_H_
#define BLE_BATTERY_H_

#include <class/ble/ble_device.h>

/**@brief 	Battery Service Class.
 * @class 	bleServiceBattery ble_service_bat.h "class/ble/ble_service_bat.h"
 *
 * @details This class implements the Battery Service with the Battery Level characteristic.
 *          During initialization it adds the Battery Service and Battery Level characteristic
 *          to the BLE stack database. Optionally it can also add a Report Reference descriptor
 *          to the Battery Level characteristic (used when including the Battery Service in
 *          the HID service).
 *
 * @ingroup BLE Class
 */
class bleServiceBattery: public bleService {
public:
	/**@brief bleServiceBattery constructor
	 * @param ble indicates to the bleDevice object.
	 * @param initial_level indicate the battery voltage level in percentage. (default 100%)
	 */
	bleServiceBattery(bleDevice &ble, uint8_t initial_level=100);

	/**@brief To check the service available.
	 * @return true if service is available, false otherwise.
	 * @note must send the battery level when the service available.
	 */
	virtual bool isAvailable();

	/**@brief Send the battery voltage level in percentage
	 * @param battery_level is a percentage to indicate the battery capacity.
	 */
	virtual uint32_t send(uint8_t battery_level);

	virtual inline uint16_t uuid() {
		return BLE_UUID_BATTERY_SERVICE;
	}
	//
	///@cond PRIVATE
	//
	virtual ~bleServiceBattery();
	bool m_bNotify;
protected:
	xHandle	m_handle;
	virtual void on_ble_event(xHandle evt);
	///@endcond
};

#endif /* BLE_BATTERY_H_ */
