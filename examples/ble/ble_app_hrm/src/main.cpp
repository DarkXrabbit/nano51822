/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Heart Rate Measurement & Heath Thermometer Measurement
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
#include <class/ble/ble_service_htm.h>

#include <class/pin.h>
#include <class/thread.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nano51822"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     500                    /**< The advertising interval (in ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS           180                    /**< The advertising timeout in units of seconds. */
#define APP_COMPANY_IDENTIFIER           	 0x004C                 /**< Company identifier for Apple Inc. as per www.bluetooth.org. */

static const uint8_t manufactory_code[] = {0x12, 0x34, 0x56};

//
// A simple RTOS task (led blink) for test
//
class ledTask: public CThread {
protected:
	virtual void run() {
		CPin led(18);
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
	ble.m_gap.tx_power(BLE_TX_0dBm);

	// Declare a HRM service object
	bleServiceHRM hrm(ble);

	// Declare a HTM service object
	bleServiceHTM htm(ble);

	// update ADVERTISING contents
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

	ble.m_advertising.add_uuid_to_complete_list(hrm);				// add hrm object to the uuid list of advertising
	ble.m_advertising.add_uuid_to_complete_list(htm);				// add htm object to the uuid_list of advertising

	ble.m_advertising.manuf_specific_data(manufactory_code, sizeof(manufactory_code));
	ble.m_advertising.update();													// update advertising data

	// Start advertising
	ble.m_advertising.start();

	//
	// A RTOS task test
	//
	ledTask t;
	t.start("LED", 42);

	//
	// LED for debug
	//
	CPin led1(19);	// led1 for connection
	CPin led2(20);	// led2 for HRM service
	CPin led3(21);	// led3 for HTM service
	led1.output();
	led2.output();
	led3.output();

	//
	// Use timeout class for HRM interval
	//
	CTimeout tmHRM, tmHTM;

	float temp;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Check Connection
    	//
    	led1 = ble.isConnected() ? LED_ON : LED_OFF;

    	//
    	// Heart Rate Measurement Service
    	//
    	if ( hrm.isAvailable() ) {
    		// check HRM timer expired (1000ms)
    		if ( tmHRM.isExpired(1000) ) {
    			led2 = !led2;
    			tmHRM.reset();	// reset timeout count
    			hrm.send(70);	// send Heart Rate Measurement
    		}
    	}

    	//
    	// Health Thermometer Measurement Service
    	//
    	if ( htm.isAvailable() ) {
    		if ( tmHTM.isExpired(1000)) {
    			tmHTM.reset();
      			// read the temperature from SoC
    			if ( bleServiceHTM::get_temperature(temp) ) {
					led3 = !led3;
					htm.send(temp);	// send temp
    			}
    		}
    	}

    }
}
