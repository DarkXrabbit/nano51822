/*
 ===============================================================================
 Name        : ble_service_uart.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/12
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE UART Service class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/12	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_UART_H_
#define BLE_SERVICE_UART_H_

#include <class/ble/ble_service_customer.h>
#include <class/stream.h>

#define BLE_UUID_UART_SERVICE            0x0001                       /**< The UUID of the UART Service. */
#define BLE_UUID_UART_TX_CHARACTERISTIC  0x0002                       /**< The UUID of the TX Characteristic. (Device to App) */
#define BLE_UUID_UART_RX_CHARACTERISTIC  0x0003                       /**< The UUID of the RX Characteristic. (App to Device) */

extern const ble_uuid128_t nus_base_uuid;	/**< Default UART's BLE base UUID */

/**
 * @brief BLE UART Service class.
 * @class bleServiceUART ble_service_uart.h "class/ble/ble_service_uart.h"
 * @ingroup Bluetooth
 */
class bleServiceUART: public bleServiceCustomer, public CStream {
public:
	/**@brief bleServiceUART constructor
	 *
	 * @param ble is a bleDevice object.
	 *
	 */
	bleServiceUART(bleDevice &ble,
				   ble_uuid128_t const *base_uuid = &nus_base_uuid,
				   uint16_t service_uuid = BLE_UUID_UART_SERVICE,
				   uint16_t tx_char_uuid = BLE_UUID_UART_TX_CHARACTERISTIC,
				   uint16_t rx_char_uuid = BLE_UUID_UART_RX_CHARACTERISTIC,
				   size_t tx_fifo_size = 64,
				   size_t rx_fifo_size = 64);

	virtual bool isAvailable();

	virtual inline bool isConnected() {
		return isAvailable();
	}

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceUART();
	virtual void onSend(bool fromISR);
protected:

    ble_gatts_char_handles_t m_tx_handles;              /**< Handles related to the TX characteristic. (as provided by the S110 SoftDevice)*/
    ble_gatts_char_handles_t m_rx_handles;              /**< Handles related to the RX characteristic. (as provided by the S110 SoftDevice)*/
    uint32_t m_flag;
    uint8_t	 *m_p_send_buf;

	uint32_t rx_char_add(uint16_t rx_char_uuid);
	uint32_t tx_char_add(uint16_t tx_char_uuid);

	virtual void on_data_receive(uint8_t * data, uint16_t length);
	virtual uint32_t on_data_transmit(uint8_t *data, uint16_t length);

	virtual void on_disconnected(xHandle evt);
	virtual void on_write(xHandle evt);
	virtual inline void on_send(xHandle evt) { onSend(true); }
	///@endcond
};

#endif /* BLE_SERVICE_UART_H_ */
