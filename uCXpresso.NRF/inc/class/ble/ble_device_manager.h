/*
 * ble_device_manager.h
 *
 *  Created on: Jul 24, 2014
 *      Author: Jason
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
	 * @param bond				Perform bonding, default 0, meaning bond can not be estabished.
	 * @param mitm				MITM protection needed.
	 * @param ioCapabilities	IO Capabilities
	 * @param oob				Out Of Band data available.
	 * @param minKeySize		Minimum encryption key size in octets between 7 and 16.
	 * @param maxKeySize		Maximum encryption key size in octets between min_key_size and 16.
	 *
	 * @return NRF_SUCCESS if register a new device manager successful.
	 */
	uint32_t settings( uint8_t timeout = 30,
					  uint8_t bond = 0,
					  uint8_t mitm = 0,
					  uint8_t ioCapabilities=BLE_GAP_IO_CAPS_NONE,
					  uint8_t oob = 0,
					  uint8_t minKeySize = 7,
					  uint8_t maxKeySize = 16);

	//
	///@cond Private
	//
	~bleDeviceManager();
	/// @cond
protected:
	uint8_t    	 m_app_handle;
	/// @endcond
};

#endif /* BLE_DEVICE_MANAGER_H_ */
