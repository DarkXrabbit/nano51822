/*
 ===============================================================================
 Name        : ble_device_manager
 Author      : uCXpresso
 Version     : v1.0.1
 Date		 : 2014/11/13
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Device Manager Module
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/11	v1.0.0	First Edition.									Jason
 2014/11/13 v1.0.1	Modify DM to Stand-alone (optional)				Jason
 ===============================================================================
 */

#ifndef BLE_DEVICE_MANAGER_H_
#define BLE_DEVICE_MANAGER_H_

#include <class/ble/ble_device.h>
#include <class/ble/nrf51/device_manager.h>
#include <class/timeout.h>

/**
 * @brief BLE Device Management
 * @class bleDeviceManager ble_device_manager.h "class/ble/ble_device_manager.h"
 * @ingroup Bluetooth
 */
class bleDeviceManager: public bleService {
public:
	/**
	 * @brief Device Manager settings.
	 *
	 * @param clearAllBoundedCentrals 	Set to true in case the module should clear all persistent data.
	 * @param timoeut					Timeout for SMP transactions or Security Request in seconds.
	 * @param bond						Perform bonding, default 1, meaning bond should be estabished.
	 * @param mitm						MITM protection needed.
	 * @param ioCapabilities			IO Capabilities
	 * @param oob						Out Of Band data available.
	 * @param minKeySize				Minimum encryption key size in octets between 7 and 16.
	 * @param maxKeySize				Maximum encryption key size in octets between min_key_size and 16.
	 *
	 */
	bleDeviceManager( bleDevice &ble,
					  bool clearAllBoundedCentrals = false,
					  uint8_t timeout = 30,
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

	/**
	 * @brief Member for creating the whitelist.
	 *
	 * @details This API allows application to create whitelist based on bonded peer devices in module
	 *          data base.
	 *
	 * @param[in,out] p_whitelist Pointer where created whitelist is provided to the application.
	 *
	 * @note 'addr_count' and 'irk_count' fields of the structure should be populated with the maximum
	 *       number of devices that the application wishes to request in the whitelist.
	 *       If the number of bonded devices is less than requested, the fields are updated with that number of devices.
	 *       If the number of devices are more than requested, the module will populate the list
	 *       with devices in the order the bond was established with the peer devices. Also, if this routine is
	 *       called when a connection exists with one or more peer devices,
	 *       those connected devices are not added to the whitelist.
	 *
	 * @retval NRF_SUCCESS             On success, else an error code indicating reason for failure.
	 * @retval NRF_ERROR_INVALID_STATE If the API is called without module initialization and/or
	 *                                 application registration.
	 * @retval NRF_ERROR_NULL          If p_handle or p_whitelist is NULL.
	 */
	uint32_t whitelist_create(ble_gap_whitelist_t *whitelist);

	/**
	 * @brief Member for getting a peer's device address.
	 *
	 * @param[out] p_addr   Pointer where address is to be copied. Can not be NULL.
	 *
	 * @retval NRF_SUCCESS             On success, else an error code indicating reason for failure.
	 * @retval NRF_ERROR_INVALID_STATE If the API is called without module initialization and/or
	 *                                 application registration.
	 * @retval NRF_ERROR_NULL          If p_handle and/or p_addr is NULL.
	 * @retval NRF_ERROR_NOT_FOUND     If the peer could not be identified.
	 */
	uint32_t peer_addr_get( ble_gap_addr_t  *p_peer_address);

	/**
	 * @brief Set to connect directed mode
	 */
	void connect_directed_mode();

	/**
	 * @brief Check the DM object is valid or not.
	 */
	virtual bool isValid();

	//
	///@cond Private
	//
	~bleDeviceManager();
	uint32_t	m_flag;
	dm_handle_t	m_bonded_peer_handle;
protected:
	uint8_t    	m_app_handle;
	void on_ble_event(ble_evt_t * p_ble_evt);
	/// @endcond
};

/**\example /ble/ble_app_proximity/src/main.cpp
 * This is an example of how to use the bleDeviceManager class.
 * More details about this example.
 */

extern bleDeviceManager *gpDM;

#endif /* BLE_DEVICE_MANAGER_H_ */
