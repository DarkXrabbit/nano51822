/*
===============================================================================
 Name        : ble_app_hrm_htm_bat_lilypad
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : Heart Rate Measurement & Heath Thermometer Measurement &
 	 	 	   Battery Level Service on LilyPad
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/10	v1.0.0	First Edition for nano51822						Leo
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
#include <class/ble/ble_service_bat.h>
#include <class/ble/ble_conn_params.h>
#include <class/pin.h>
#include <class/adc.h>
#include <class/timeout.h>
#include <class/thread.h>
#include <class/power.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                         "nano51822"         /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                   "uCXpresso.NRF"     /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                    1000                /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	0x0059				/**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

//
// Board Define
//
#ifdef DEBUG
#define BOARD_PCA10001
#else
#define BOARD_LILYPAD
#endif
#include <config/board.h>

//
// Status LED task
//
class tskLED : public CThread {
protected:
	virtual void run() {
		CPin led(LED_PIN_0);
		led.output();
		while(1) {
			if ( gpBLE->isConnected() ) {
				led = LED_ON;
				sleep(50);		// ON with 50ms when connected
				led = LED_OFF;
				sleep(950);
			} else {
				led = LED_ON;
				sleep(5);		// ON with 5ms when disconnected.
				led = LED_OFF;
				sleep(995);
			}
		}
	}
};

//
// main routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif
	//
	// Declare SoftDevice Object
	//
	bleDevice ble;
	ble.enable();						// enable BLE stack

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);	// set output radio Power

	//
	// Declare a HRM service object
	//
	bleServiceHRM hrm(ble);

	//
	// Declare a HTM service object
	//
	bleServiceHTM htm(ble);

	//
	// Declare a BAT service object
	//
	bleServiceBattery bat(ble);

	//
	// Add "connection parameters update" negotiation. (optional)
	//
	bleConnParams conn(ble);

	//
	// update advertisement contents
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

	ble.m_advertising.add_uuid_to_complete_list(hrm);				// add hrm object to the uuid list of advertisement
	ble.m_advertising.add_uuid_to_complete_list(htm);				// add htm object to the uuid_list of advertisement
	ble.m_advertising.add_uuid_to_complete_list(bat);				// add bat object to the uuid_list of advertisement

	ble.m_advertising.appearance(BLE_APPEARANCE_GENERIC_HEART_RATE_SENSOR);
	ble.m_advertising.update();										// update advertisement data

	// Start advertising
	ble.m_advertising.start();

	//
	// Tickless Low Power Feature
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Analog input (for VDD detected)
	//
	CAdc::init();			// AREF internal VBG
	CAdc::source(VDD_1_3);	// source from internal: VDD x 1/3
	CAdc::enable();

	//
	// LED Task
	//
	tskLED t;
	t.start("LED", 45);	// stack size=45 DWORD

	//
	uint16_t value;
	float 	 temp, percentage;

	//
    // Enter main loop.
	//
    while(1) {

    	//
    	// wait for BLE connected, the task will be blocked until connected.
    	//
    	ble.wait();

    	//
    	// Heart Rate Measurement Service
    	//
    	if ( hrm.isAvailable() ) {	// is service available (when remote app connected to the service)
    		hrm.send(70);			// send Heart Rate Measurement
    	}

    	//
    	// Health Thermometer Measurement Service
    	//
    	if ( htm.isAvailable() ) {		// is service available (when remote app connected to the service)
			if ( bleServiceHTM::get_temperature(temp) ) {
				htm.send(temp);	// send temp
			}
    	}

    	//
    	// Battery Service
    	//
    	if ( bat.isAvailable() ) {		// is service available (when remote app connected to the service)
			if ( CAdc::read(value) ) {
				percentage = (value / 1024.0f) * 100.0;
				bat.send(percentage);
			}
    	}

    	sleep(500);	// sleep to make more idle time for tickless.
    }
}
