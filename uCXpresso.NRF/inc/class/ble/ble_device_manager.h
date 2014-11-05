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
	bleDeviceManager();

	uint32_t settings(bool clearAllBoundedCentrals = true,
					  uint8_t timeout = 30,
					  uint8_t bond = 1,
					  uint8_t mitm = 0,
					  uint8_t ioCapabilities=BLE_GAP_IO_CAPS_NONE,
					  uint8_t oob = 0,
					  uint8_t minKeySize = 7,
					  uint8_t maxKeySize = 16);

	//
	// Private
	//
	virtual uint32_t onEvent(xHandle handle, xHandle event, uint32_t result);

	~bleDeviceManager();
	/// @cond
protected:
	uint8_t    	 m_app_handle;
	virtual void on_ble_event(ble_evt_t * p_ble_evt);

friend class bleDevice;
	/// @endcond
};

#endif /* BLE_DEVICE_MANAGER_H_ */
