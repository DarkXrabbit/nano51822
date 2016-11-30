/*
 ===============================================================================
 Name        : ble_gap
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/11
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE GAP module
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/1	v1.0.0	First Edition.									Jason
 ===============================================================================
 */

#ifndef _BLE_GAP_H_
#define _BLE_GAP_H_

#include <class/ble/ble_base.h>

/**setTxPower sets the output power level of the Bluetooth Low Energy radio.
 * \ingroup Enumerations
 */
typedef enum {
	BLE_TX_4dBm		=  4,	///<  4dBm
	BLE_TX_0dBm 	=  0,	///<  0dBm
	BLE_TX_m4dBm	= -4,	///< -4dBm
	BLE_TX_m8dBm 	= -8,	///< -18dBm
	BLE_TX_m12dBm 	= -12,	///< -12dBm
	BLE_TX_m16dBm	= -16,	///< -16dBm
	BLE_TX_m20dBm	= -20,	///< -20dBm
	BLE_TX_m30dBm	= -30,	///< -30dBm
	BLE_TX_m40dBm	= -40	///< -40dBm
}BLE_TX_POWER_T;

typedef enum {
	BTLE_CONN_INTERVAL_UNACCEPTABLE	= 0x3B,
	BTLE_REMOTE_USER_TERMINATED_CONNECTION		= 0x13
}GAP_DISCONN_REASON_T;

/**
 * @brief BLE GAP class
 * @class bleGAP ble_gap.h "class/ble/ble_gap.h"
 * @ingroup Bluetooth
 */
class bleGAP: public bleBase {
public:
	/*
	 * @brief Set GAP Peripheral Preferred Connection Parameters.
	 * @param device_name		Pointer to the device name string.
	 * @param min_conn_interval	Minimum Connection Interval in ms units.
	 * @param max_conn_interval Maximum Connection Interval in ms units.
	 * @param slave_latency		Slave Latency in number of connection events.
	 * @param conn_sup_timeout	Connection Supervision Timeout in ms units.
	 *
	 * @return
	 * @retval NRF_SUCCESS Peripheral Preferred Connection Parameters set successfully.
	 * @retval NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 * @retval NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied.
	 */
	virtual uint32_t settings(LPCTSTR device_name,
							  float min_conn_interval = 50,		// default 50ms
							  float max_conn_interval = 500,		// default 500ms
							  uint16_t slave_latency 	 = 0,		//
							  uint16_t conn_sup_timeout  = 4000		// default connection supervisory timeout 4 seconds.
							);
	/**
	 * @brief Get GAP Peripheral Preferred Connection Parameters.
	 *
	 * @param[out] p_conn_params Pointer to a @ref ble_gap_conn_params_t structure where the parameters will be stored.
	 *
	 * @return @ref NRF_SUCCESS Peripheral Preferred Connection Parameters retrieved successfully.
	 * @return @ref NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 */
	uint32_t preferred_conn_params(ble_gap_conn_params_t *p_conn_params);

	/**@brief Set GAP Appearance value.
	 *
	 * @param[in] appearance Appearance (16-bit), see @ref BLE_APPEARANCES.
	 *
	 * @return @ref NRF_SUCCESS  Appearance value set successfully.
	 * @return @ref NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied.
	 */
	virtual uint32_t appearance(uint16_t value);

	/**@brief Set the radio's transmit power.
	 *
	 * @param[in] tx_power Radio transmit power in dBm, see @ref BLE_TX_POWER_T.
	 *
	 * @note -40 dBm will not actually give -40 dBm, but will instead be remapped to -30 dBm.
	 *
	 * @return @ref NRF_SUCCESS Successfully changed the transmit power.
	 * @return @ref NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied.
	 * @return @ref NRF_ERROR_BUSY The stack is busy, process pending events and retry.
	 */
	virtual uint32_t tx_power(BLE_TX_POWER_T power);

	/**@brief Disconnect (GAP Link Termination).
	 *
	 * @details This call initiates the disconnection procedure, and its completion will be communicated to the application
	 *          with a BLE_GAP_EVT_DISCONNECTED event.
	 *
	 * @param[in] hci_status_code HCI status code, see @ref GAP_DISCONN_REASON_T (accepted values are BTLE_REMOTE_USER_TERMINATED_CONNECTION and BTLE_CONN_INTERVAL_UNACCEPTABLE).
	 *
	 * @return @ref NRF_SUCCESS The disconnection procedure has been started successfully.
	 * @return @ref NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied.
	 * @return @ref BLE_ERROR_INVALID_CONN_HANDLE Invalid connection handle supplied.
	 * @return @ref NRF_ERROR_INVALID_STATE Invalid state to perform operation (disconnection is already in progress or not connected at all).
	 */
	virtual uint32_t disconnect(GAP_DISCONN_REASON_T reason=BTLE_REMOTE_USER_TERMINATED_CONNECTION);

	/**@brief Get local Bluetooth address.
	 *
	 * @param[out] p_addr Pointer to address structure.
	 *
	 * @return @ref NRF_SUCCESS Address successfully retrieved.
	 * @return @ref NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 */
	uint32_t getAddress(ble_gap_addr_t *p_addr);

	/**@brief Set, clear or update advertisement and scan response data.
	 *
	 * @note The format of the advertisement data will be checked by this call to ensure interoperability.
	 *       Limitations imposed by this API call to the data provided include having a flags data type in the scan response data and
	 *       duplicating the local name in the advertisement data and scan response data.
	 *
	 * @note: To clear the advertisement data and set it to a 0-length packet, simply provide a valid pointer (p_data/p_sr_data) with its corresponding
	 *        length (dlen/srdlen) set to 0.
	 *
	 * @note: The call will fail if p_data and p_sr_data are both NULL since this would have no effect.
	 *
	 * @param[in] p_data    Raw data to be placed in advertisement packet. If NULL, no changes are made to the current advertisement packet data.
	 * @param[in] dlen      Data length for p_data. Max size: @ref BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if p_data is NULL, can be 0 if p_data is not NULL.
	 * @param[in] p_sr_data Raw data to be placed in scan response packet. If NULL, no changes are made to the current scan response packet data.
	 * @param[in] srdlen    Data length for p_sr_data. Max size: @ref BLE_GAP_ADV_MAX_SIZE octets. Should be 0 if p_sr_data is NULL, can be 0 if p_data is not NULL.
	 *
	 * @return @ref NRF_SUCCESS Advertisement data successfully updated or cleared.
	 * @return @ref NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 * @return @ref NRF_ERROR_INVALID_FLAGS Invalid combination of advertising flags supplied.
	 * @return @ref NRF_ERROR_INVALID_DATA Invalid data type(s) supplied, check the advertising data format specification.
	 * @return @ref NRF_ERROR_INVALID_LENGTH Invalid data length(s) supplied.
	 * @return @ref BLE_ERROR_GAP_UUID_LIST_MISMATCH Invalid UUID list supplied.
	 * @return @ref NRF_ERROR_BUSY The stack is busy, process pending events and retry.
	 */
	uint32_t setAddress(ble_gap_addr_t *p_addr, uint8_t addr_cycle_mode = BLE_GAP_ADDR_CYCLE_MODE_NONE);

	//
	/// @cond PRIVATE (internal used)
	//
	bleBase *m_p_ble;
	/// @endcond
};

#endif /* BLE_GAP_H_ */
