/*
 ===============================================================================
 Name        : ble_device.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/8/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE SoftDevice driver (S110) class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/1	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_DEVICE_H_
#define BLE_DEVICE_H_

#include <class/thread.h>
#include <class/semaphore.h>
#include <class/peripheral.h>
#include <class/list.h>

#include <class/ble/ble_service.h>
#include <class/ble/ble_advertising.h>
#include <class/ble/ble_device_manager.h>
#include <class/ble/ble_gap.h>

/**@brief 	BLE Device Class (SoftDevice).
 * @class 	bleDevice ble_device.h "class/ble/ble_device.h"
 *
 * @details This class manages the all BLE event from the SoftDevice driver,
 * 			and provides the device-manager, advertising and gap objects.
 *
 * @ingroup BLE Class
 */
class bleDevice : public bleBase, public CThread{
public:
	/**@brief Enable the BLE stack (device).
	 *
	 * @param stack Set the stack size for the BLE device task.
	 *
	 * @return @ref NRF_SUCCESS BLE stack has been enabled successfully
	 */
	uint32_t enable(uint32_t stack=86);

	/**@brief Check BLE connection.
	 *
	 * @return true if ble is in connected, false otherwise.
	 */
	virtual bool isConnected();

	/**@brief A Connected Event.
	 *
	 * @details The onConnected will be called when a BLE connection created.
	 */
	virtual void onConnected();

	/**@brief A Disconnected Event.
	 *
	 * @details The onDisconnected will be called when a BLE connection destroy.
	 */
	virtual void onDisconnected();

	/**@brief A BLE stack error occurred.
	 */
	virtual void onError(uint32_t err_code);

	/**@brief A GAP timeout occurred.
	 */
	virtual void onTimeout();

	/**@brief A RSSI changed event
	 * @param rssi A received signal strength indication.
	 */
	virtual void onRssiChanged(int8_t rssi);

	/**@brief A device manager member object.
	 * @ref bleDeviceManager class.
	 */
	bleDeviceManager	m_device_manager;

	/**@brief An advertising member object.
	 * @ref bleAdvertising class.
	 */
	bleAdvertising		m_advertising;

	/**@brief GAP member object.
	 * @ref bleGAP class.
	 */
	bleGAP				m_gap;

	//
	/// @cond PRIVATE
	//
	bleDevice();
	virtual ~bleDevice();
	void on_ble_event(xHandle event);
	void on_sys_event(uint32_t event);

	xHandle 	m_hBleEvent;
	uint16_t    m_conn_handle;
	int8_t		m_rssi;			// current rssi;
	ble_gap_evt_auth_status_t m_auth_status;
	ble_gap_sec_params_t	  m_sec_params;
	CSemaphore	m_semBleEvent;
protected:
	uint32_t	m_flag;
	bool		m_memory_access_in_progress;

	void system_off_mode_enter();

	//
	// parameters initiation
	//
	virtual void security_params_init();

	//
	// for services
	//
	CList m_lstService;
	void add_service(bleService *service);
	void del_service(bleService *service);
	void services_evt(xHandle evt);

	//
	// Implement CThread::run()
	//
	virtual void run();
//
// friend class for BLE services
//
friend class bleAdvertising;
friend class bleDeviceManager;
friend class bleService;
	/// @endcond
};

extern bleDevice *gpBLE;	///< Point to the global bleDevice object.

#endif /* BLE_DEVICE_H_ */
