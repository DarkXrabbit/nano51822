/*
 * ble_advertising.h
 *
 *  Created on: Jul 22, 2014
 *      Author: Jason
 */

#ifndef BLE_ADVERTISING_H_
#define BLE_ADVERTISING_H_

#include <class/ble/nrf51/ble_data.h>
#include <class/ble/ble_base.h>

#define DEF_ADV_INTERVAL	1000	// 1000 Milliseconds
#define DEF_ADV_TIMEOUT		0		// No Adv. timeout  (unit:second)

class bleAdvertising: public bleBase {
public:
	bleAdvertising();

	virtual void interval(uint16_t ms);
	virtual void timeout(uint16_t sec);
	virtual void name_type(ble_advdata_name_type_t type);
	virtual void commpany_identifier(uint16_t id);
	virtual void manuf_specific_data(const uint8_t *data, uint16_t size);
	virtual void flags(const uint8_t *data, uint16_t size);
	virtual void uuids_complete_list(const ble_uuid_t *p_uuids, uint16_t count);
	virtual uint32_t update();

	virtual uint32_t start();
	virtual uint32_t stop();

	inline ble_advdata_t* getAdvData() {
		return &m_adv_data;
	}

	inline ble_advdata_manuf_data_t* getManufData() {
		return &m_manuf_specific_data;
	}

protected:
	bleBase	 				*m_p_ble;
	ble_advdata_t			 m_adv_data;
	ble_advdata_manuf_data_t m_manuf_specific_data;
	ble_gap_adv_params_t 	 m_adv_params;

friend class bleDevice;
};

#define UUID_COUNT(x)	(sizeof(x)/sizeof(x[0]))

#endif /* BLE_ADVERTISING_H_ */
