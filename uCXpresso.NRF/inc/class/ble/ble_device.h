/*
 ===============================================================================
 Name        : bleDevice.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/7/21
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : nRF51822 BLE device
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/7/21	v1.0.0	First Edition for nano11Uxx						Jason
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


#define APP_TIMER_PRESCALER			0	/**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_MAX_TIMERS		4	/**< Maximum number of simultaneously created timers. */
#define APP_TIMER_OP_QUEUE_SIZE		5	/**< Size of timer operation queues. */

class bleDevice : public bleBase{
public:
	bleDevice();
	uint32_t enable();					// enable BLE stack
	static bool waitForEvent(uint32_t timeout=0);

	//
	// Status
	//
	virtual bool isConnected();

	//
	// Events
	//
	virtual void onConnected();
	virtual void onDisconnected();
	virtual void onError(uint32_t err_code);

	//
	// GAP Events
	//
	virtual void onTimeout();
	virtual void onRssiChanged(int8_t rssi);

	//
	// BLE common member
	//
	bleDeviceManager	m_device_manager;
	bleAdvertising		m_advertising;
	bleGAP				m_gap;

	//
	/// @cond PRIVATE
	//
	virtual ~bleDevice();
	void on_ble_event(xHandle event);
	void on_sys_event(uint32_t event);

	xHandle 	m_hBleEvent;
//	uint32_t	m_nSysEvent;
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
// friend class for BLE services
//
friend class bleAdvertising;
friend class bleDeviceManager;
friend class bleService;
	/// @endcond
};

extern bleDevice *gpBLE;

#endif /* BLE_DEVICE_H_ */
