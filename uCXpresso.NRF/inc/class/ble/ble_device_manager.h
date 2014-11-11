/*
 ===============================================================================
 Name        : ble_device_manager
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/11
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Device Manager Module
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/1	v1.0.0	First Edition.									Jason
 ===============================================================================
 */

#ifndef BLE_DEVICE_MANAGER_H_
#define BLE_DEVICE_MANAGER_H_

#include <class/ble/ble_base.h>
#include <class/timeout.h>

/**
 * @brief BLE Device Management
 * @class bleDeviceManager ble_device_manager.h "class/ble/ble_device_manager.h"
 * @ingroup Bluetooth
 */
class bleDeviceManager: public bleBase {
public:
	/**
	 * @brief Device Manager settings.
	 *
	 * @param timoeut			Timeout for SMP transactions or Security Request in seconds.
	 * @param bond				Perform bonding, default 1, meaning bond should be estabished.
	 * @param mitm				MITM protection needed.
	 * @param ioCapabilities	IO Capabilities
	 * @param oob				Out Of Band data available.
	 * @param minKeySize		Minimum encryption key size in octets between 7 and 16.
	 * @param maxKeySize		Maximum encryption key size in octets between min_key_size and 16.
	 *
	 * @return NRF_SUCCESS if register a new device manager successful.
	 */
	uint32_t settings( uint8_t timeout = 30,
					  uint8_t bond = 1,
					  uint8_t mitm = 0,
					  uint8_t ioCapabilities=BLE_GAP_IO_CAPS_NONE,
					  uint8_t oob = 0,
					  uint8_t minKeySize = 7,
					  uint8_t maxKeySize = 16);
	/**
	 * @brief Indicates that link with the peer is secured.
	 *
	 * @detail For bonded devices, subsequent reconnections with bonded peer
	 * will result only in this event when the link is secured and
	 * setup procedures will not occur unless the bonding information is either lost or deleted on either or both sides.
	 *
	 * @return true if link is secured.
	 */
	bool isLinkSecured();

	//
	///@cond Private
	//
	~bleDeviceManager();
	uint32_t	m_flag;
protected:
	uint8_t    	m_app_handle;
	/// @endcond
};

extern bleDeviceManager *gpDM;

#endif /* BLE_DEVICE_MANAGER_H_ */
