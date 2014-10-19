/*
 ===============================================================================
 Name        : ble_service.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/12
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Services base class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/12	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_H_
#define BLE_SERVICE_H_

#include <class/ble/ble_base.h>

/**
 * @brief BLE Service base class.
 *
 * @class bleService ble_service.h "class/ble/ble_service.h"
 *
 * @ingroup Bluetooth
 */
class bleService: virtual public bleBase {
public:
	/**@brief bleService constructor.
	 * @param ble is a bleDevice to point the bleDevice object.
	 */
	bleService(bleBase &ble);

	/** @brief Check the service available.
	 * @return true if service is available, false otherwise.
	 */
	virtual inline bool isAvailable() { return true; }

	/**@brief Get the UUID of service
	 * @return an uint16_t value.
	 */
	virtual uint16_t uuid() = PURE_VIRTUAL_FUNC;

	/**@brief Get the UUID type of service.
	 * @return an uint8_t value.
	 */
	virtual inline uint8_t uuid_type() {
		return BLE_UUID_TYPE_BLE;
	}

	//
	/// @cond PRIVATE
	//
	virtual void on_ble_event(xHandle evt) = PURE_VIRTUAL_FUNC;
	~bleService();
protected:
	bleBase	*m_p_ble;
	/// @endcond
};

#endif /* BLE_SERVICE_H_ */
