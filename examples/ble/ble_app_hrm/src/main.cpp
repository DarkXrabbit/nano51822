/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Heart Rate Measurement Service
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/5	v1.0.0	First Edition for nano51822						Leo
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
#include <class/pin.h>
#include <class/thread.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nano51822"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     40                     /**< The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS           180                    /**< The advertising timeout in units of seconds. */
#define APP_COMPANY_IDENTIFIER           	 0x004C                 /**< Company identifier for Apple Inc. as per www.bluetooth.org. */

static const ble_uuid_t adv_uuids[] = {
	{BLE_UUID_HEART_RATE_SERVICE, BLE_UUID_TYPE_BLE}
};

//
// A simple RTOS task (led blink) for test
//
class ledTask: public CThread {
protected:
	virtual void run() {
		CPin led(P38);
		led.output();
		while(1) {
			led.invert();
			sleep(200);
		}
	}
};

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

	// ADVERTISING
	ble.m_advertising.interval(APP_ADV_INTERVAL);								// set advertising interval
	ble.m_advertising.uuids_complete_list(adv_uuids, UUID_COUNT(adv_uuids));	// add HRM UUID on advertising
	ble.m_advertising.update();													// update advertising data

	// Declare a HRM service object
	bleServiceHRM hrm(ble);

	// Setup connection parameters
	ble.conn_params(hrm.cccd_handle());

	// Start advertising
	ble.m_advertising.start();

	//
	// A RTOS task test
	//
	ledTask t;
	t.start("LED", 38);

	//
	// LED for debug
	//
	CPin led1(P4);
	CPin led2(P5);
	led1.output();
	led2.output();

	//
	// Use timeout class for HRM interval
	//
	CTimeout tmHRM;

	//
    // Enter main loop.
	//
    while(1) {
    	if ( ble.isConnected() ) {
    		led1 = LED_ON;		// set led on when BLE connected.

    		// check HRM timer expired (800ms)
    		if ( tmHRM.isExpired(800) ) {
    			tmHRM.reset();	// reset timeout count
    			led2 = !led2;
    			hrm.send(70);	// send Heart Rate Measurement
    		}
    	} else {
    		led1 = LED_OFF;		// set led off when BLE disconnected.
    	}
    }
}
