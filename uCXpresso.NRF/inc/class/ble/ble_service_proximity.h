/*
 ===============================================================================
 Name        : ble_service_proximity.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/10
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Proximity Service
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/10	v1.0.0	First Edition								Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_PROXIMITY_H_
#define BLE_SERVICE_PROXIMITY_H_

#include <class/ble/ble_device.h>

/**
 * @brief Proximity service alert level.
 * @ingroup Enumerations
 */
enum ALERT_LEVEL_T {
	ALERT_LEVEL_NO_ALERT	= 0x00,		/**< No Alert. */
	ALERT_LEVEL_MILD_ALERT	= 0x01,		/**< Mild Alert. */
	ALERT_LEVEL_HIGH_ALERT  = 0x02		/**< High Alert. */
};

/**
 * @brief BLE Service base class.
 * @class bleServiceProximity ble_service_proximity.h "class/ble/ble_service_proximity.h"
 *
 * @dital
 *
 * @ingroup Bluetooth
 */
class bleServiceProximity: public bleService {
public:
	/**
	 * @brief bleServiceProxiity constructor
	 * @param ble 		Pointer to the bleDevice object.
	 * @param defLevel	Default alert level @ref ALERT_LEVEL_T
	 */
	bleServiceProximity(bleDevice &ble, ALERT_LEVEL_T defLevel = ALERT_LEVEL_NO_ALERT);

	/**
	 * @brief Check the service available.
	 * @return true if service is available, false otherwise.
	 */
	virtual bool isAvailable();

	/**
	 * @brief Send immediate alert.
	 * @param level The alert level @ref ALERT_LEVEL_T.
	 * @return NRF_SUCCESS if send successful.
	 */
	virtual uint32_t send(ALERT_LEVEL_T level);

	/**@brief Get the uuid list of service for advertisement.
	 * @return uuid of service
	 */
	virtual inline uint16_t uuid() {
		return BLE_UUID_IMMEDIATE_ALERT_SERVICE;
	}

	/**
	 * @brief On Alert Signal Event
	 */
	virtual void on_alert_signal(ALERT_LEVEL_T level, bool is_link_loss) { NOTHING }

	/**
	 * @brief Event indicating that the Immediate Alert Service is found at the peer.
	 */
	virtual void on_server_discovered() { NOTHING }

	/**
	 * @brief Event indicating that the Immediate Alert Service client module has completed disconnected.
	 */
	virtual void on_server_disconnected() { NOTHING }

	/**
	 * @brief Event indicating that the Immediate Alert Service is not found at the peer.
	 */
	virtual void on_server_not_found() { NOTHING }

	//
	///@cond
	///
	virtual ~bleServiceProximity();
protected:
	xHandle m_ias_handle;
	xHandle m_lls_handle;
	xHandle m_ias_c_handle;
	virtual void on_ble_event(ble_evt_t * p_ble_evt);
	///@endcond
};

#endif /* BLE_SERVICE_PROXIMITY_H_ */
