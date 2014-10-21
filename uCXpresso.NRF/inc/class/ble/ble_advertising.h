/*
 ===============================================================================
 Name        : ble_advertising.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/8/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE advertising
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/1	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_ADVERTISING_H_
#define BLE_ADVERTISING_H_

#include <stdarg.h>
#include <class/ble/nrf51/ble_data.h>
#include <class/ble/ble_service.h>

#define DEF_ADV_INTERVAL			1000	// 1000 Milliseconds
#define DEF_ADV_TIMEOUT				0		// No Adv. timeout  (unit:second)
#define MAX_ADV_UUID_COMPLETE_LIST	16

/**@brief	BLE Advertising Class.
 *
 * @class 	bleAdvertising ble_advertising.h "class/ble/bleAdvertising.h"
 *
 * @details The bleAdvertising class for encoding the advertising data
 * 			and/or scan response data, and passing them to the stack.
 *
 * @note	The bleAdvertising object provides in the @ref bleDevice class.
 *
 * @ingroup Bluetooth
 */
class bleAdvertising: public bleBase {
public:
	/**@brief bleAdvertising constructor.
	 *
	 */
	bleAdvertising();

	/**@brief Set the advertising interval between 20ms to 10.24s.
	 *
	 */
	void interval(uint16_t ms);

	/**@brief Set advertising timeout between 0x0001 and 0x3FFF in seconds, 0x0000 disables the timeout.
	 *
	 */
	void timeout(uint16_t sec);

	/**@brief Type of the device name.
	 * @ref ble_advdata_name_type_t
	 */
	void name_type(ble_advdata_name_type_t type);

	/**@brief Advertising data Flags field.
	 *
	 */
	void flags(const uint8_t *data, uint16_t size);

	/**@brief Set the Company Identifier Code
	 *
	 */
	void commpany_identifier(uint16_t id);

	/**@brief Additional manufacturer specific data.
	 *
	 */
	void manuf_specific_data(const uint8_t *data, uint16_t size);

	/**@brief Set the list of UUIDs in the 'Complete' list.
	 *
	 */
	void add_uuid_to_complete_list(bleService &service);

	/**@brief Set the Slave Connection Interval Range.
	 *
	 */
	void slave_connection_interval(uint16_t max, uint16_t min);

	/**@brief Set the TX Power Level field.
	 *
	 */
	void tx_power_level(int8_t value);

	/**@brief Set GAP Appearance value.
	 *
	 * @param[in] value Appearance (16-bit), see @ref BLE_APPEARANCES.
	 *
	 * @return @ref NRF_SUCCESS  Appearance value set successfully.
	 * @return @ref NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied.
	 */
	uint32_t appearance(uint16_t value);

	/**@brief Update the all fields into Advertising
	 *
	 */
	uint32_t update();

	/**@brief Reset the all fields
	 */
	void reset();

	/**@brief Start the advertising
	 */
	virtual uint32_t start();

	/**@brief Stop the advertising
	 */
	virtual uint32_t stop();

	/**@brief get adv. data member.
	 */
	inline ble_advdata_t* getAdvData() {
		return &m_adv_data;
	}

	/**@brief get manufacturer data.
	 *
	 */
	inline ble_advdata_manuf_data_t* getManufData() {
		return &m_manuf_specific_data;
	}

	//
	///@cond PRIVATE
	//
protected:
	bleBase	 				*m_p_ble;
	ble_advdata_t			 m_adv_data;
	ble_advdata_manuf_data_t m_manuf_specific_data;
	ble_advdata_conn_int_t	 m_slave_conn_interval;
	ble_gap_adv_params_t 	 m_adv_params;
	int8_t					 m_tx_power_level;
	ble_uuid_t				*m_uuid_list;
	uint8_t					 m_uuid_count;
friend class bleDevice;
	///@endcond
};

/**\example /ble/ble_beacon/src/main.cpp
 * This is an example of how to use the bleAdvertising class to implement the iBeacon application.
 * More details about this example.
 */


#endif /* BLE_ADVERTISING_H_ */
