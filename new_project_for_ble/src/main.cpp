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
#define DBG dbg_printf
#else
#define DBG(...)
#endif

// TODO: insert other include files here
#include <class/ble/ble_device.h>
#include <class/ble/ble_service.h>
#include <class/pin.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nano51822"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     500                    /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x004C                 /**< Company identifier for Apple Inc. as per www.bluetooth.org. */

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
//	bleDevice ble(NRF_LFCLKSRC_XTAL_20_PPM);	/**< use external 32.768Khz crystal for SoftDevice */
	bleDevice ble;	// use internal 32.768KHz for SoftDevice
	ble.enable();	// enable BLE SoftDevice stack

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

	//
	// Add BLE Service
	//

	//
	// BLE Advertising
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

//	ble.m_advertising.add_uuid_to_complete_list(hrm);				// add hrm object to the uuid list of advertising
//	ble.m_advertising.appearance(BLE_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT);

//	ble.m_advertising.manuf_specific_data(manufactory_code, sizeof(manufactory_code));
	ble.m_advertising.update();													// update advertising data

	// Start advertising
	ble.m_advertising.start();

	//
	// Your Application setup code here
	//


	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//

    }
}
