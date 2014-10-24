/*
 ===============================================================================
 Name        : ble_service_dfu.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/24
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE DFU Service class (for OTA)
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/24	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_DFU_H_
#define BLE_SERVICE_DFU_H_

#include <class/ble/ble_device.h>

/**
 * @brief BLE DFU service class.
 *
 * @class bleServiceDFU ble_service_dfu.h "class/ble/ble_service_dfu.h"
 *
 * @warning the DFU service support for nanoDFU v141024 and later.
 *
 * @ingroup Bluetooth
 */
class bleServiceDFU: public bleService {
public:
	bleServiceDFU(bleDevice &ble);

	/**
	 * @brief check service available.
	 */
	virtual bool isAvailable();

	/**
	 * @brief enable DFU service can be entry to DFU mode
	 *
	 * @note May you enable the DFU entry when security check valid.
	 */
	virtual void enable();

	/**
	 * @brief disable DFU service can not be entry to DFU mode.
	 */
	virtual void disable();

	/**
	 * @brief UUID type assigned for DFU Service by the S110 SoftDevice.
	 */
	virtual uint8_t uuid_type();

	//
	///@cond
	//
	virtual ~bleServiceDFU();
	virtual void onResetPrepare();
protected:
	virtual inline uint16_t uuid() { return 0;}
	xHandle m_handle;
	virtual void on_ble_event(xHandle evt);
	///@endcond
};

extern bleServiceDFU *gpDFU;

/**\example /ble/ble_beacon/src/main.cpp
 * This is an example of how to use the bleServiceDFU class.
 * More details about this example.
 */

#endif /* BLE_SERVICE_DFU_H_ */
