/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : A BLE UAET to Debug Console (Serial I/F) example
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/14 v1.0.0	First Edition.									LEO
 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG dbg_printf
#else
#define DBG(...)
#endif

// TODO: insert other include files here
#include <class/ble/ble_device.h>
#include <class/ble/ble_conn_params.h>
#include <class/ble/ble_service.h>
#include <class/ble/ble_service_uart.h>
#include <class/ble/uuid.h>
#include <class/pin.h>
#include <class/timeout.h>
#include <class/sstream.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nanoUART"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     127                    	/**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059					/**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

#define BLE_ECHO	1
#define AES_STREAM	1

//#define BOARD_LILYPAD
#define BOARD_NANO51822_UDK
#include <config/board.h>

const char *uuid_service_base = "6E400000-B5A3-F393-E0A9-E50E24DCCA9E";
const uint8_t txKey[] = {0x1B, 0xDE, 0x2A, 0xE5, 0x86, 0x2D, 0x17, 0x48, 0xE5, 0x3F, 0xE9, 0xB1, 0xFF, 0x97, 0x21, 0x1B};    // for BLE -> iOS
const uint8_t rxKey[] = {0x1B, 0xEC, 0x2A, 0xE6, 0x87, 0x2D, 0x17, 0x48, 0xC5, 0x3F, 0xE9, 0xB1, 0xFE, 0x77, 0x23, 0x1B};    // for iOS -> BLE

//
// Main Routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a Serial object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif

	//
	// SoftDevice
	//
	bleDevice ble;	// use internal 32.768KHz for SoftDevice
	ble.enable();	// enable BLE SoftDevice stack

	// GAP
	ble.m_gap.settings(DEVICE_NAME, 50, 50, 0, 3000);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);	// set Output power

	//
	// Add BLE UART Service
	//
	CUUID base(uuid_service_base);
	bleServiceUART nus(ble, &base.uuid);			// declare a BLE "Nordic UART Service" (NUS) object

	//
	// Add "connection parameters update" negotiation. (optional)
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	int8_t const txPowerLevel = -55;
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier
	ble.m_advertising.tx_power_level(&txPowerLevel);
	ble.m_advertising.add_uuid_to_complete_list(nus);
//	ble.m_advertising.add_uuid_to_complete_list(bat);

	ble.m_advertising.update();										// update advertising data

	// Start advertising
	ble.m_advertising.start();

	//
	// Your Application setup code here
	//
#if AES_STREAM
	SStream aes(txKey, rxKey, nus);
	CStream *air = &aes;
#else
	CStream *air = &nus;
#endif

	CPin led1(LED1);	// led0 on P0.18
	CPin led2(LED2);	// led1 on P0.19

	led1.output();	// set led0 as an output pin
	led2.output();	// set led1 as an output pin

	CTimeout	tm;
	uint8_t		len, buffer[64];

	//
    // Enter main loop.
	//
    while(1) {
    	if ( air->isConnected() ) {	// check BLE NUS service
    		if ( air->readable() ) {
    			led2.invert();
    			len = air->read(buffer, air->available());
#if BLE_ECHO
    			air->write(buffer, len);
#endif

#ifdef DEBUG
    			for (uint8_t ch=0; ch<len; ch++) {
    				dbg.putc(buffer[ch]);
    			}
#endif
    		}

#ifdef DEBUG
    		if ( dbg.available() ) {
    			air->write(dbg.read());		// echo to BLE NUS service
    		}
#endif
    	} else {
    		led2 = LED_OFF;
    	}

    	//
    	// blink led
    	//
    	if ( tm.isExpired(500) ) {
    		tm.reset();
    		led1 = !led1;	// blink led
    	}

    	// Negotiate the "Connect Parameters Update"
    	conn.negotiate();
    }
}
