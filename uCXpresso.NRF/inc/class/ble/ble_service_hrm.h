/*
 ===============================================================================
 Name        : ble_service_hrm.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/12
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Heart Rate service class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/12	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_HRM_H_
#define BLE_SERVICE_HRM_H_

#include <class/ble/ble_device.h>
#include <class/semaphore.h>

typedef enum  {
	HRS_BODY_SENSOR_LOCATION_OTHER = 0,
	HRS_BODY_SENSOR_LOCATION_CHEST,
	HRS_BODY_SENSOR_LOCATION_WRIST,
	HRS_BODY_SENSOR_LOCATION_FINGER,
	HRS_BODY_SENSOR_LOCATION_HAND,
	HRS_BODY_SENSOR_LOCATION_EAR_LOBE,
	HRS_BODY_SENSOR_LOCATION_FOOT
}hrm_sensor_loc_t;

/**@brief 	BLE Heart Rate service
 * @class 	bleServiceHRM ble_service_hrm.h "class/ble/ble_service_hrm.h"
 *
 * @details This service exposes heart rate and other data from a
 * Heart Rate Sensor intended for fitness applications.
 *
 * @ingroup Bluetooth
 */
class bleServiceHRM: public bleService {
public:
	bleServiceHRM(bleDevice &ble,
				  hrm_sensor_loc_t sensor_location = HRS_BODY_SENSOR_LOCATION_FINGER,
				  bool contact_supported=false);

	virtual bool isAvailable();

	/**@brief Send the heart rate measurement value.
	 *
	 * @param[in] heart_rate Send the heart rate value to client.
	 *
	 * @return NRF_SUCCESS if send measurement value successful.
	 */
	virtual uint32_t send(uint16_t heart_rate);

	/**@brief Function for adding a RR Interval measurement to the RR Interval buffer.
	 *
	 * @details All buffered RR Interval measurements will be included in the next heart rate
	 *          measurement message, up to the maximum number of measurements that will fit into the
	 *          message. If the buffer is full, the oldest measurement in the buffer will be deleted.
	 *
	 * @param[in]   rr_interval  New RR Interval measurement (will be buffered until the next
	 *                           transmission of Heart Rate Measurement).
	 */
	virtual void rr_interval_add(uint16_t interval);

	/**@brief Function for checking if RR Interval buffer is full.
	 *
	 * @return      true if RR Interval buffer is full, false otherwise.
	 */
	virtual bool rr_interval_buffer_is_full();

	/**@brief Function for setting the state of the Sensor Contact Detected bit.
	 *
	 * @param[in]   is_sensor_contact_detected   TRUE if sensor contact is detected, FALSE otherwise.
	 */
	virtual void sensor_contact_detected_update(bool is_sensor_contact_detected);

	virtual inline uint16_t uuid() {
		return BLE_UUID_HEART_RATE_SERVICE;
	}

	//
	///@cond PRIVATE
	//
	uint16_t cccd_handle();
	virtual ~bleServiceHRM();
	bool	m_bNotify;
protected:
	xHandle	m_handle;
	virtual void on_ble_event(xHandle evt);
	//@endcond
};

extern bleServiceHRM *gpHRM;	///< the global point to the Heart Rate Service object

/**\example /ble/ble_app_hrm_htm_bat/src/main.cpp
 * This is an example of how to use the bleServiceHRM class.
 * More details about this example.
 */

#endif /* BLE_SERVICE_HRM_H_ */
