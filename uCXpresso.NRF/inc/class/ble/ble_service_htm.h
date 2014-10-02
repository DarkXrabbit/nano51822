/*
 * ble_service_htm.h
 *
 *  Created on: 2014/9/23
 *      Author: Jason
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



class bleServiceHTM: public bleService {
public:
	bleServiceHTM(bleDevice &ble, hts_temp_type_t type=HTS_TEMP_TYPE_BODY);

	virtual bool isAvailable();
	virtual uint32_t send(float temperature, hts_unit_t unit=HTS_UNIT_CELCIUS, hts_temp_type_t type=HTS_TEMP_TYPE_BODY);

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
