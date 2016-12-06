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
#include <class/ble/ble_service.h>
#include <class/pin.h>

#include <class/ble/ble_service_uart.h>
#include <class/ble/ble_service_dfu.h>
#include <class/ble/ble_conn_params.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nanoUART"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     50                    	/**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059					/**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

#define BLE_ECHO	1

//#define BOARD_LILYPAD
#define BOARD_NANO51822_UDK
#include <config/board.h>

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
	bleServiceUART nus(ble);			// declare a BLE "Nordic UART Service" (NUS) object

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

	CPin led1(LED1);	// led0 on P0.18
	CPin led2(LED2);	// led1 on P0.19

	led1.output();	// set led0 as an output pin
	led2.output();	// set led1 as an output pin

	CTimeout	tm;
	uint8_t		ch, len, buffer[64];

	//
    // Enter main loop.
	//
    while(1) {
    	if ( nus.isAvailable() ) {	// check BLE NUS service
    		if ( nus.readable() ) {
    			led2.invert();
    			len = nus.read(buffer, nus.available());
#if BLE_ECHO
    			nus.write(buffer, len);
    			for (ch=0; ch<len; ch++) {
    				dbg.putc(buffer[ch]);
    			}
#else
    			dbg.write(buffer, len);		// echo to Debug Console
#endif
    		}

    		if ( dbg.available() ) {
    			ch = dbg.read();
    			nus.write(ch);		// echo to BLE NUS service
    		}

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
