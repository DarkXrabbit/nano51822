/*
===============================================================================
 Name        : ble_app_hrm_no_led
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Tickless Test with HRM and HTML services.
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/7	v1.0.0	First Edition for nano51822						Leo
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
#include <class/ble/ble_service_hrm.h>
#include <class/ble/ble_service_htm.h>
#include <class/power.h>
#include <class/ble/ble_conn_params.h>
#include <class/ble/ble_service_dfu.h>
#include <class/pin.h>
#include <class/thread.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nano51822"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     1000                    /**< The advertising interval (in ms). */

// Board Defined
//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

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
	// SoftDevice
	bleDevice ble;
	ble.enable();						// enable BLE stack

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

	// Device Manager (optional)
	ble.m_device_manager.settings();

	//
	// Declare a HRM service object
	//
	bleServiceHRM hrm(ble);

	//
	// Declare a HTM service object
	//
	bleServiceHTM htm(ble);

#ifndef DEBUG
	bleServiceDFU dfu(ble);
	dfu.enable();
#endif

	//
	// Connection Parameters Update negotiation
	//
	bleConnParams conn(ble);

	//
	// update ADVERTISING contents
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval

	ble.m_advertising.add_uuid_to_complete_list(hrm);				// add hrm object to the uuid list of advertising
	ble.m_advertising.add_uuid_to_complete_list(htm);				// add htm object to the uuid_list of advertising

	ble.m_advertising.appearance(BLE_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT);
	ble.m_advertising.update();										// update advertising data

	// Start advertising
	ble.m_advertising.start();

#ifdef DEBUG
	CPin led(LED_PIN_0);
	led.output();
#else
	CPowerSave::tickless(true);
#endif

	float temp;
	//
    // Enter main loop.
	//
    while(1) {

    	//
    	// Wait for connected
    	//
    	ble.wait();

#ifdef DEBUG
    	led.toggle();
#endif
		//
		// Heart Rate Measurement Service
		//
		if ( hrm.isAvailable() ) {
			hrm.send(70);
		}

		//
		// Health Thermometer Measurement Service
		//
		if ( htm.isAvailable() ) {
			if ( bleServiceHTM::get_temperature(temp) ) {
				htm.send(temp);	// send temp
			}
		}

		sleep(1000);	// give more idle time for sleep
    }
}
