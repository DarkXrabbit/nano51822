/*
===============================================================================
 Name        : main.c
 Author      :
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 :
 Description :
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------

 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif

// TODO: insert other include files here
//#include <class/ble/ble_device_manager.h>
#include <class/ble/ble_device.h>
#include <class/ble/ble_service.h>
#include <class/ble/ble_conn_params.h>
#include <class/ble/ble_service_uart.h>
#include <class/ble/uuid.h>
#include <class/power.h>
#include <class/pin.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "swiftIO"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"      /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     127                   /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059               /**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

//#define BOARD_LILYPAD
#define BOARD_NANO51822_UDK
#include <config/board.h>

#define AES_STREAM	0

//
// SwiftIO Stream UUID for BLE
//
#include "SwiftIO.h"
const char *swiftIO_base_uuid = "AFEA0000-17D0-42B2-BBD2-14718591D65E";

//
// Main Routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif
	//
	// SoftDevice
	//
	bleDevice ble;
	ble.enable();	// enable BLE SoftDevice task

	// Device Manager for bond device. (Optional, for bond link device only)
//	bleDeviceManager man(ble);

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

	//
	// TODO: Add BLE Service
	//
	bleServiceUART stream1(ble);				// stream1 for BLE UART

	CUUID base(swiftIO_base_uuid);
	bleServiceUART stream2(ble, &base.uuid);	// stream2 for SwiftIO

	//
	// Optional: Add "Connection Parameters Update" negotiation.
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

	// Optional: add standard profile uuid in advertisement.
	ble.m_advertising.add_uuid_to_complete_list(stream2);

	// Optional: add appearance to indicate who you are in advertisement.
	ble.m_advertising.update();										// update advertisement data

	// Start advertising
	ble.m_advertising.start();

	//
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Your Application setup code here
	//
	CPin led(LED_PIN_0);
	led.output();

	// Declare SwiftIO
	swiftIO swift(stream2);
	swiftIO_packet_t *packet_in;

	CTimeout tm;

	//
    // Enter main loop.
	//
    while(1) {

		swift.runloop();

		if ( (packet_in = swift.read()) != NULL ) {
			switch(packet_in->opcode) {
			case OP_DO_SET:
				// data[0] : pin number
				// data[1] : pin value  0=LOW, 1=HIGH
				uint8_t pin = packet_in->data[0];
				CPin DO(pin);
				DO.output((PIN_LEVEL_T) packet_in->data[1]);
				break;
			}
			// free packet & data
			delete packet_in->data;
			delete packet_in;
		}

		if ( tm.isExpired(500) ) {
			tm.reset();
			led.invert();
		}
    	//
    	// Negotiate the "connection parameters update" in main-loop
    	//
    	conn.negotiate();
    }
}
