/*
 ===============================================================================
 Name        : ble_service_htm.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/12
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Health Thermometer service class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/12	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_HTM_H_
#define BLE_SERVICE_HTM_H_

#include <class/ble/ble_device.h>

typedef enum {
	HTS_TEMP_TYPE_ARMPIT = 1,
	HTS_TEMP_TYPE_BODY,
	HTS_TEMP_TYPE_EAR,
	HTS_TEMP_TYPE_FINGER,
	HTS_TEMP_TYPE_GI_TRACT,
	HTS_TEMP_TYPE_MOUTH,
	HTS_TEMP_TYPE_RECTUM,
	HTS_TEMP_TYPE_TOE,
	HTS_TEMP_TYPE_EAR_DRUM
}hts_temp_type_t;

typedef enum {
	HTS_UNIT_FAHR = 0,
	HTS_UNIT_CELCIUS,
}hts_unit_t;


/**@brief 	Health Thermometer Service class
 * @class 	bleServiceHTM ble_service_htm.h "class/ble/ble_service_htm.h"
 *
 * @details he Health Thermometer service exposes temperature and other data
 * from a thermometer intended for healthcare and fitness applications.
 *
 * @ingroup BLE Class
 */

class bleServiceHTM: public bleService {
public:
	bleServiceHTM(bleDevice &ble, hts_temp_type_t type=HTS_TEMP_TYPE_BODY);

	/**@brief Override the @ref bleService isAvailable member
	 */
	virtual bool isAvailable();

	/**@brief Function for sending health thermometer measurement if client indication has been enabled.
	 *
	 * @details The application calls this function after having performed a Health Thermometer
	 *          measurement. If indication has been enabled, the measurement data is encoded and
	 *          sent to the client.
	 *
	 * @param[in]	temperature	Health Thermometer measurement value.
	 * @param[in]   unit        measurement unit.
	 * @param[in]   p_hts_meas  Thermometer sensor location.
	 *
	 * @return      NRF_SUCCESS on success, otherwise an error code.
	 */
	virtual uint32_t send(float temperature, hts_unit_t unit=HTS_UNIT_CELCIUS, hts_temp_type_t type=HTS_TEMP_TYPE_BODY);

	/**@brief Get the temperature measured on the nano51822
	 *
	 * @param[out] p_temp Result of temperature measurement. Die temperature in celsius.
	 *
	 * @retval ::NRF_SUCCESS A temperature measurement was done, and the temperature was written to temp
	 *
	 * @warning This function will block until the temperature measurement is done.
	 * It takes around 50us from call to return.
	 */
	static bool get_temperature(float &temp);

	//
	///@cond
	//
	virtual ~bleServiceHTM();
	bool	m_bIndicate;
protected:
	xHandle	m_handle;
	virtual void on_ble_event(xHandle evt);
	///@endcond
};

#endif /* BLE_SERVICE_HTM_H_ */
