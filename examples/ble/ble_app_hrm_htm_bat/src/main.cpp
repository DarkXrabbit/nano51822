/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Heart Rate Measurement & Heath Thermometer Measurement &
 	 	 	   Battery Level Service
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18	v1.0.0	First Edition for nano51822						Leo
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

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                         "nano51822"         /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                   "uCXpresso.NRF"     /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                    500                 /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	0x0059				/**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

static const uint8_t manufactory_code[] = {0x12, 0x34, 0x56};

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
	// SoftDevice
	bleDevice ble;
	ble.enable();						// enable BLE stack

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

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
	// Analog input (for VDD detected)
	//
	CAdc::init();
	CAdc::source(VDD_1_3);
	CAdc::enable();

	//
	// LED for debug
	//
	CPin led0(18);	// led0 for connection
	CPin led1(19);	// led1 for HRM service
	CPin led2(20);	// led2 for HTM service
	CPin led3(21);	// led3 for BAT service
	led0.output();
	led1.output();
	led2.output();
	led3.output();

	//
	// Use timeout class for HRM interval
	//
	CTimeout tmLED, tmHRM, tmHTM, tmBAT;

	uint16_t value;
	float 	 temp, percentage;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Check Connection
    	//
    	if ( ble.isConnected() ) {
    		led0 = LED_ON;
    	} else if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led0.toggle();
    	}

    	//
    	// Heart Rate Measurement Service
    	//
    	if ( hrm.isAvailable() ) {		// is service available (when remote app connected to the service)
    		// check HRM timer expired (1000ms)
    		if ( tmHRM.isExpired(1000) ) {
    			tmHRM.reset();	// reset timeout count
    			hrm.send(70);	// send Heart Rate Measurement
    			led1.toggle();
    		}
    	}

    	//
    	// Health Thermometer Measurement Service
    	//
    	if ( htm.isAvailable() ) {		// is service available (when remote app connected to the service)
    		if ( tmHTM.isExpired(1000)) {
    			tmHTM.reset();
      			// read the temperature from SoC
    			if ( bleServiceHTM::get_temperature(temp) ) {
					htm.send(temp);	// send temp
					led2.toggle();
    			}
    		}
    	}

    	//
    	// Battery Service
    	//
		if ( tmBAT.isExpired(1000) ) {
			tmBAT.reset();
			if ( CAdc::read(value) ) {
				percentage = (value / 1024.0f) * 100.0;
				bat.send(percentage);
				led3.toggle();
			}
		}

    	// Negotiate the "connection parameters update"
    	conn.negotiate();
    }
}
