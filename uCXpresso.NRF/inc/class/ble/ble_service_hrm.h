/*
 * ble_service_hrm.h
 *
 *  Created on: Jul 24, 2014
 *      Author: Jason
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


class bleServiceHRM: public bleService {
public:
	bleServiceHRM(bleDevice &ble,
				  hrm_sensor_loc_t sensor_location = HRS_BODY_SENSOR_LOCATION_FINGER,
				  bool contact_supported=false);

	virtual bool isAvailable();

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

	uint16_t cccd_handle();
	virtual ~bleServiceHRM();
	bool	m_bNotify;
protected:
	xHandle	m_handle;
	virtual void on_ble_event(xHandle evt);
friend class bleDevice;
};

#endif /* BLE_SERVICE_HRM_H_ */
