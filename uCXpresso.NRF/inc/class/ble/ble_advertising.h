/*
 ===============================================================================
 Name        : ble_advertising.h
 Author      : uCXpresso
 Version     : v1.0.7
 Date		 : 2015/3/27
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
 2014/2/6	v1.0.5	Add update overload member functions.			Jason
 2015/3/2	v1.0.6	Add add_uuid_to_complete_list overload member.	Jason
 2015/3/27	v1.0.7	Reduce RAM used.								Jason
 2015/5/27	v1.0.8	Add manuf_specific_data() for RAW data.			Jason
 	 	 	 	 	Add add_uuid_to_complete_list() for RAW data.
 ===============================================================================
 */

#ifndef BLE_ADVERTISING_H_
#define BLE_ADVERTISING_H_

#include <stdarg.h>
#include <class/ble/nrf51/ble_data.h>
#include <class/ble/ble_service.h>

#define DEF_ADV_INTERVAL				1000	// 1000 Milliseconds
#define DEF_ADV_TIMEOUT					0		// No Adv. timeout  (unit:second)
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
	void interval(float ms);

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
	 * @brief set advertising flags.
	 */
	void flags(const uint8_t *flags, uint8_t size=1);

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

	/**
	 * @brief Additional manufacturer specific data.
	 * @param pdata Point to the raw of the @ref ble_advdata_manuf_data_t data.
	 */
	void manuf_specific_data(ble_advdata_manuf_data_t *pdata);

	/**
	 * @brief Add the uuid of service in the 'Complete' list of Adv.
	 */
	void add_uuid_to_complete_list(uint16_t uuid, uint8_t type=BLE_UUID_TYPE_BLE);

	/**
	 * @brief Overload the add_uuid_to_complete_list member function.
	 */
	inline void add_uuid_to_complete_list(bleService &service) {
		add_uuid_to_complete_list(service.uuid(), service.uuid_type());
	}

	/**
	 * @brief Additional manufacturer specific data.
	 * @param uuids Array point to the raw of the @ref ble_uuid_t list.
	 * @param count Indicate the number of uuid in the list.
	 */
	void add_uuid_to_complete_list(ble_uuid_t const *uuids, uint16_t count);

	/**@brief Set the Slave Connection Interval Range.
	 * @param max	Max. connection interval (unit ms).
	 * @param min	Min. connection interval (uint ms).
	 */
	void slave_connection_interval(float max, float min);

	/**@brief Set the TX Power Level field.
	 *
	 */
	void tx_power_level(int8_t const *dBm);

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
	uint32_t update(uint8_t flags=0);


	/**@brief Function for encoding and setting the advertising data and/or scan response data.
	 *
	 * @details This function encodes advertising data and/or scan response data based on the selections
	 *          in the supplied structures, and passes the encoded data to the stack.
	 *
	 * @param[in]   p_adv_data  Structure for specifying the content of the advertising data.
	 *                          Set to NULL if advertising data is not to be set.
	 * @param[in]   p_scn_data	Structure for specifying the content of the scan response data.
	 *                          Set to NULL if scan response data is not to be set.
	 *
	 * @return      NRF_SUCCESS on success, NRF_ERROR_DATA_SIZE if not all the requested data could fit
	 *              into the advertising packet. The maximum size of the advertisement packet is @ref
	 *              BLE_GAP_ADV_MAX_SIZE.
	 *
	 * @warning This API may override application's request to use the long name and use a short name
	 * instead. This truncation will occur in case the long name does not fit advertisement data size.
	 * Application is permitted to specify a preferred short name length in case truncation is required.
	 * For example, if the complete device name is ABCD_HRMonitor, application can specify short name
	 * length to 8 such that short device name appears as ABCD_HRM instead of ABCD_HRMo or ABCD_HRMoni
	 * etc if available size for short name is 9 or 12 respectively to have more apporpriate short name.
	 * However, it should be noted that this is just a preference that application can specify and
	 * if the preference too large to fit in Advertisement Data, this can be further truncated.
	 */
	uint32_t update(ble_advdata_t *p_adv_data, ble_advdata_t *p_scan_data);

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
	ble_advdata_t 			m_adv_data;
	ble_gap_adv_params_t 	m_adv_params;
	ble_advdata_uuid_list_t m_uuids_complete;

	uint8_t					m_adv_direct_cnt;
	float					m_adv_interval;
	uint16_t				m_adv_timeout;

	ADV_START_MODE_T		m_adv_start_mode;
	///@endcond
};

/**\example /ble/ble_beacon/src/main.cpp
 * This is an example of how to use the bleAdvertising class to implement the iBeacon application.
 * More details about this example.
 */

#endif /* BLE_ADVERTISING_H_ */
