/*
 ===============================================================================
 Name        : ble_service_csc.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/4
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Cycling Speed and Cadence service
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/4	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_CSC_H_
#define BLE_SERVICE_CSC_H_

#include <class/ble/ble_device.h>
#include <class/ble/nrf51/ble_sensor_location.h>

/** @defgroup BLE_CSCS_FEATURES Cycling Speed and Cadence Service feature bits
 * @{ */
#define BLE_CSCS_FEATURE_WHEEL_REV_BIT                  (0x01 << 0)     /**< Wheel Revolution Data Supported bit. */
#define BLE_CSCS_FEATURE_CRANK_REV_BIT                  (0x01 << 1)     /**< Crank Revolution Data Supported bit. */
#define BLE_CSCS_FEATURE_MULTIPLE_SENSORS_BIT           (0x01 << 2)     /**< Multiple Sensor Locations Supported bit. */
/** @} */

#define DEF_CSC_FEATURES (BLE_CSCS_FEATURE_WHEEL_REV_BIT | BLE_CSCS_FEATURE_CRANK_REV_BIT | BLE_CSCS_FEATURE_MULTIPLE_SENSORS_BIT) ///< Default CSC features

/**
 * @brief Cycling Speed and Cadence service
 * @class bleServiceCSC ble_service_csc.h "class/ble/ble_service_csc.h"
 *
  * @details This module implements the Cycling Speed and Cadence Service. If enabled, notification
 *          of the Cycling Speead and Candence Measurement is performed when the application
 *          calls the send() member function.
 *
 * @ingroup Bluetooth
 */
class bleServiceCSC: public bleService {
public:
	/**
	 * @brief Construct of the bleServiceCSC class.
	 * @param[in] ble bleDevice Object.
	 */
	bleServiceCSC(bleDevice &ble,
				  uint16_t features = DEF_CSC_FEATURES,
				  ble_sensor_location_t sensor_location=BLE_SENSOR_LOCATION_FRONT_WHEEL);

	virtual bool isAvailable();

	/**
	 * @brief Overload Function, send the CSC Measurement data for wheel.
	 *
	 * @param cumulative_wheel_revolutions
	 * @param last_wheel_event_time	Unit has a resolution of 1/1024s.
	 *
	 * @return
	 * @retval NRF_SUCCESS	Send the data successful.
	 */
	inline uint32_t send(uint32_t cumulative_wheel_revolutions, uint16_t last_wheel_event_time) {
		return send(BLE_CSCS_FEATURE_WHEEL_REV_BIT, cumulative_wheel_revolutions, last_wheel_event_time, 0, 0);
	}

	/**
	 * @brief Overload function, send the CSC Measurement data for crank.
	 * @param cumulative_crank_revolutions
	 * @param last_crank_event_time	Unit has a resolution of 1/1024s.
	 *
	 * @return
	 * @retval NRF_SUCCESS	Send the data successful.
	 */
	inline uint32_t send(uint16_t cumulative_crank_revolutions, uint16_t last_crank_event_time) {
		return send(BLE_CSCS_FEATURE_CRANK_REV_BIT, 0, 0, cumulative_crank_revolutions, last_crank_event_time);
	}

	/**
	 * @brief Overload function, send the CSC Measurement data for wheel and crank.
	 *
	 * @param cumulative_wheel_revolutions
	 * @param last_wheel_event_time	Unit has a resolution of 1/1024s.
	 * @param cumulative_crank_revolutions
	 * @param last_crank_event_time	Unit has a resolution of 1/1024s.
	 *
	 * @return
	 * @retval NRF_SUCCESS	Send the data successful.
	 */
	inline uint32_t send(uint32_t cumulative_wheel_revolutions,
					 uint16_t last_wheel_event_time,
					 uint16_t cumulative_crank_revolutions,
					 uint16_t last_crank_event_time) {

		return send(BLE_CSCS_FEATURE_WHEEL_REV_BIT | BLE_CSCS_FEATURE_CRANK_REV_BIT,
					cumulative_wheel_revolutions, last_wheel_event_time,
					cumulative_crank_revolutions, last_crank_event_time);
	}

	/**
	 * @brief Retrieve the cumulative wheel revolutions.
	 */
	inline uint32_t cumulative_wheel_revs() {
		return m_cumulative_wheel_revs;
	}

	/**
	 * @brief check an autocalibration is in progress.
	 */
	inline bool is_auto_calibration_in_progress() {
		return m_auto_calibration_in_progress;
	}

	/**
	 * @brief Get the CSC UUID of service
	 * @return an uint16_t value.
	 */
	virtual inline uint16_t uuid() {
		return BLE_UUID_CYCLING_SPEED_AND_CADENCE;
	}

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceCSC();
	uint32_t m_cumulative_wheel_revs;                   /**< Cumulative wheel revolutions. */
	bool     m_auto_calibration_in_progress;            /**< Set when an autocalibration is in progress. */

protected:
	xHandle m_handle;
	virtual void on_ble_event(xHandle evt);
	virtual uint32_t send(uint8_t  flag,
					  uint32_t cumulative_wheel_revolutions,
					  uint16_t last_wheel_event_time,
					  uint16_t cumulative_crank_revolutions,
					  uint16_t last_crank_event_time);
	///@endcond
};

#endif /* BLE_SERVICE_CSC_H_ */
