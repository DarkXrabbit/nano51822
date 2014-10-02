/*
 * ble_gap.h
 *
 *  Created on: Jul 24, 2014
 *      Author: Jason
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

class bleGAP: public bleBase {
public:
	bleGAP();

	virtual uint32_t settings(LPCTSTR device_name,
							  uint16_t min_conn_interval = 500,
							  uint16_t max_conn_interval = 1000,
							  uint16_t slave_latency 	 = 0,
							  uint16_t conn_sup_timeout  = 4000
							);

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

protected:
	bleBase	 	*m_p_ble;
	ble_gap_conn_params_t	m_gap_conn_params;

friend class bleDevice;
};

#endif /* BLE_GAP_H_ */
