/*
 ===============================================================================
 Name        : Running Speed and Cadence Service
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/4
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Running Speed and Cadence Service measurement
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/4	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_RSC_H_
#define BLE_SERVICE_RSC_H_

#include <class/ble/ble_device.h>

/**@brief Running Speed and Cadence Service feature bits. */
#define BLE_RSCS_FEATURE_INSTANT_STRIDE_LEN_BIT             (0x01 << 0)     /**< Instantaneous Stride Length Measurement Supported bit. */
#define BLE_RSCS_FEATURE_TOTAL_DISTANCE_BIT                 (0x01 << 1)     /**< Total Distance Measurement Supported bit. */
#define BLE_RSCS_FEATURE_WALKING_OR_RUNNING_STATUS_BIT      (0x01 << 2)     /**< Walking or Running Status Supported bit. */
#define BLE_RSCS_FEATURE_CALIBRATION_PROCEDURE_BIT          (0x01 << 3)     /**< Calibration Procedure Supported bit. */
#define BLE_RSCS_FEATURE_MULTIPLE_SENSORS_BIT               (0x01 << 4)     /**< Multiple Sensor Locations Supported bit. */

#define DEF_RSC_FEATURES	(BLE_RSCS_FEATURE_INSTANT_STRIDE_LEN_BIT | BLE_RSCS_FEATURE_WALKING_OR_RUNNING_STATUS_BIT)

/**
 * @brief Running Speed and Cadence status
 * @ingroup Enumerations
 */
enum RSC_STATUS_T {
	RSC_WALKING,
	RSC_RUNNING
};

/**
 * @brief BLE Running Speed and Cadence Service
 * @class bleServiceRSC ble_service_rsc.h "class/ble/ble_service_rsc.h"
 *
 * @details This module implements the Running Speed and Cadence Service. If enabled, notification
 *          of the Running Speead and Candence Measurement is performed when the application
 *          calls send() member function.
 *
 * @ingroup Bluetooth
 */
class bleServiceRSC: public bleService {
public:
	bleServiceRSC(bleDevice &ble, uint16_t features=DEF_RSC_FEATURES);

	/** @brief Check the service available.
	 * @return true if service is available, false otherwise.
	 */
	virtual bool isAvailable();

	/**
	 * @brief Send Running Speed and Cadence Service measurement.
	 *
	 * @param speed				Instantaneous Speed.
	 * @param cadence			Instantaneous Cadence.
	 * @param status			Walking or Running, @ref RSC_STATUS_T
	 * @param total_distance	Optional, Total Distance.
	 * @param stride_length_cm	Optional, Instantaneous Stride Length. (in center meter)
	 *
	 * @return NRF_SUCCESS on success, otherwise an error code.
	 */
	uint32_t send(uint16_t speed,
				  uint8_t cadence,
				  RSC_STATUS_T status = RSC_WALKING,
				  uint32_t total_distance=0,
				  uint16_t stride_length_cm=0) ;

	/**@brief Get the UUID of service
	 * @return an uint16_t value.
	 */
	virtual uint16_t uuid() {
		return BLE_UUID_RUNNING_SPEED_AND_CADENCE;
	}

	//
	///@cond
	//
	virtual ~bleServiceRSC();
protected:
	xHandle m_handle;
	virtual void on_ble_event(ble_evt_t *p_ble_evt);
	///@endcond
};

#endif /* BLE_SERVICE_RSC_H_ */
