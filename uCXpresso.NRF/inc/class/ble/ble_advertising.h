/*
 ===============================================================================
 Name        : ble_advertising.h
 Author      : uCXpresso
 Version     : v1.0.4
 Date		 : 2014/1/10
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE advertising
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/1	v1.0.0	First Edition for nano51822						Jason
 2014/11/13 v1.0.1	Add type() member to indicate the ADV. type.	Jason
 2014/11/18 v1.0.2	Support white-list for Device Manager module.	Jason
 2014/12/4  v1.0.3	Add "Directed Advertising" scheme for BT4.1 	Jason
 2014/1/10  v1.0.4	Add isActive member function.					Jason
 ===============================================================================
 */

#ifndef BLE_ADVERTISING_H_
#define BLE_ADVERTISING_H_

#include <stdarg.h>
#include <class/ble/nrf51/ble_data.h>
#include <class/ble/ble_service.h>

#define DEF_ADV_INTERVAL				1000	// 1000 Milliseconds
#define DEF_ADV_TIMEOUT					0		// No Adv. timeout  (unit:second)
#define DEF_ADV_FLAG					BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE
#define DEF_ADV_FAST_INTERVAL			50		// for bond connection, adv. interval = 50ms
#define DEF_ADV_FAST_TIMEOUT			40		// for bond connection, adv. timeout = 40 sec.
#define DEF_ADV_FAST_WHITELIST_TIMEOUT	20		// for bond white-list, adv. timeout = 20 sec.

#define MAX_ADV_UUID_COMPLETE_LIST		16

/**
 * @brief GAP Advertising types
 * @ingroup Enumerations
 */
enum ADV_TYPE_T {
	ADV_TYPE_ADV_IND		= 0x00,			///< Connectable undirected. (Default)
	ADV_TYPE_ADV_DIRECT_IND = 0x01,			///< Connectable directed.
	ADV_TYPE_ADV_SCAN_IND   = 0x02,			///< Scannable undirected.
	ADV_TYPE_ADV_NONCONN_IND= 0x03			///< Non connectable undirected.
};

/**
 * @brief Advertising Start Mode
 * @ingroup Enumerations
 */
enum ADV_START_MODE_T {
	ADV_MODE_NORMAL = 0,	// default
	ADV_MODE_PREV_NORMAL,
	ADV_MODE_FAST,
	ADV_MODE_DIRECTED,
	ADV_MODE_PREV_DIRECT,
	ADV_MODE_WHITELIST,
	ADV_MODE_NO_ADV			// for bond connection
};

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
	/**
	 * @brief GAP Advertising types
	 */
	void type(ADV_TYPE_T adv_type);

	/**
	 * @brief Set the advertising interval between 20ms to 10.24s. (for normal mode)
	 */
	void interval(uint16_t ms);

	/**
	 * @brief Set advertising timeout between 0x0001 and 0x3FFF in seconds, 0x0000 disables the timeout.
	 * @note Maximum advertising time in limited discoverable mode = 180 seconds.
	 */
	void timeout(uint16_t sec);

	/**
	 * @brief Type of the device name.
	 * @ref ble_advdata_name_type_t
	 */
	void name_type(ble_advdata_name_type_t type);

	/**
	 * @brief single advertising flag.
	 */
	void flag(uint8_t val);

	/**
	 * masked, replace by flag() member.
	 */
	//void flags(const uint8_t *data, uint16_t size);

	/**
	 * @brief Set the Company Identifier Code
	 */
	void commpany_identifier(uint16_t id);

	/**
	 * @brief Additional manufacturer specific data.
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

	/**
	 * @brief Update the all fields into Advertising
	 * @param flags Set the advertising flags. @ref BLE_GAP_ADV_FLAGS
	 */
	uint32_t update(uint8_t flags=0, ble_advdata_t *scan=NULL);

	/**
	 * @brief Set, clear or update advertisement and scan response raw data.
	 * @note The format of the advertisement data will be checked by this call to ensure interoperability.
	 *       Limitations imposed by this API call to the data provided include having a flags data type in the scan response data and
	 *       duplicating the local name in the advertisement data and scan response data.
	 *
	 * @note: To clear the advertisement data and set it to a 0-length packet, simply provide a valid pointer (p_data/p_sr_data) with its corresponding
	 *        length (dlen/srdlen) set to 0.
	 *
	 * @note: The call will fail if p_data and p_sr_data are both NULL since this would have no effect.
	 *
	 * @param[in] adv_data	Raw data to be placed in advertisement packet. If NULL, no changes are made to the current advertisement packet data.
	 * @param[in] adv_len	Data length for adv_data. Max size: @ref BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if p_data is NULL, can be 0 if adv_data is not NULL.
	 * @param[in] scn_data	Raw data to be placed in scan response packet. If NULL, no changes are made to the current scan response packet data.
	 * @param[in] scn_len	Data length for scn_data. Max size: @ref BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if scn_data is NULL, can be 0 if p_data is not NULL.
	 */
	uint32_t update(uint8_t *adv_data, uint8_t adv_len, uint8_t *scn_data, uint8_t scn_len);

	/**@brief Reset the all fields
	 */
	void reset();

	/**
	 * @brief Set the advertising start mode
	 * @param mode The start @ref ADV_START_MODE_T.
	 */
	void mode(ADV_START_MODE_T mode);	// set start mode

	/**
	 * @brief Start the advertising
	 */
	virtual uint32_t start();

	/**
	 * @brief Stop the advertising
	 */
	virtual uint32_t stop();

	/**
	 * @brief Check advertising started
	 */
	virtual bool isActive();

	//
	///@cond PRIVATE (internal used)
	//
	bleAdvertising();
	bool is_memory_access_in_progress();

	inline ADV_START_MODE_T mode() {
		return m_adv_start_mode;
	}
	uint32_t				 m_flag;
protected:
	ble_advdata_t			 m_adv_data;
	ble_uuid_t				*m_uuid_list;
	ble_gap_adv_params_t 	 m_adv_params;
	uint8_t					 m_uuid_count;
	int8_t					 m_tx_power_level;
	uint8_t					 m_adv_flag;
	uint8_t					 m_adv_direct_cnt;
	uint16_t				 m_adv_interval;
	uint16_t				 m_adv_timeout;

	ADV_START_MODE_T		 m_adv_start_mode;
	///@endcond
};

/**\example /ble/ble_beacon/src/main.cpp
 * This is an example of how to use the bleAdvertising class to implement the iBeacon application.
 * More details about this example.
 */

#endif /* BLE_ADVERTISING_H_ */
