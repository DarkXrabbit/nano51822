/*
===============================================================================
 Name        : ble_app_proximity
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : BLE Proximity Service Demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/18 v1.0.0	First Edition.									Leo
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
#include <class/ble/ble_device_manager.h>
#include <class/ble/ble_device.h>
#include <class/ble/ble_service.h>
#include <class/ble/ble_conn_params.h>
#include <class/ble/ble_service_proximity.h>
#include <class/ble/ble_service_tpl.h>
#include <class/ble/ble_service_bat.h>
#include <class/ble/ble_service_dfu.h>
#include <class/adc.h>
#include <class/timeout.h>
#include <class/power.h>
#include <class/pin.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "Proximity"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     500                    /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059                 /**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

CPin ledLeft(LED_PIN_0);
CPin ledRight(LED_PIN_1);

//
// my Proximity Class (to implement the on_alert_signal event)
//
class myProximity: public bleServiceProximity {
public:
	//
	// Construct to send the ble to constructor of bleServiceProximity parent class.
	//
	myProximity(bleDevice &ble) : bleServiceProximity(ble) { NOTHING }

	//
	// Implement the on_alert_signal event
	//
	virtual void on_alert_signal(ALERT_LEVEL_T level, bool is_link_loss) {
		switch(level) {
		case ALERT_LEVEL_NO_ALERT:
			ledLeft = LED_OFF;
			break;
		case ALERT_LEVEL_MILD_ALERT:
		case ALERT_LEVEL_HIGH_ALERT:
			ledLeft = LED_ON;
			break;
		}
	}
};

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

	// Button
	CPin btn(17);	// P0.17
	btn.input();

	// device manager
	bleDeviceManager man(ble, (btn==LOW ? true : false));

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

	//
	// Proximity Service
	//
	myProximity prox(ble);

	//
	// Tx Power Service
	//
	bleServiceTPL tpl(ble);

	//
	// Battery Level Service
	//
	bleServiceBattery bat(ble);

	//
	// DFU service
	//
	bleServiceDFU dfu(ble);
	dfu.enable();

	//
	// Optional: Add "Connection Parameters Update" negotiation.
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

	// Optional: add standard profile in advertisement
	ble.m_advertising.add_uuid_to_complete_list(tpl);
	ble.m_advertising.add_uuid_to_complete_list(prox);				// add prox object to the uuid list of advertisement.

	// Optional: Appearance who you are
	ble.m_advertising.appearance(BLE_APPEARANCE_GENERIC_KEYRING);
	ble.m_advertising.flag(BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE);
	ble.m_advertising.update();										// update advertisement data

	// Start advertising
	ble.m_advertising.mode(ADV_MODE_NO_ADV);
	ble.m_advertising.start();

	//
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Analog
	//
	CAdc::init();
	CAdc::source(VDD_1_3);	// to detect the VDD voltage
	CAdc::enable();

	//
	// Enable Tickless Technology
	//
	CPowerSave::tickless(true);

	//
	// LED
	//
	ledLeft.output();
	ledRight.output();

#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	CTimeout tmLED, tmBAT;
	uint16_t value;
	float percentage;
	PIN_LEVEL_T pl = HIGH;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Proximity immediate alert send.
    	//
    	if ( prox.isAvailable() ) {
    		if ( btn!=pl ) {
				if ( btn==LOW ) {
					prox.send(ALERT_LEVEL_HIGH_ALERT);
				} else {
					prox.send(ALERT_LEVEL_NO_ALERT);
				}
				pl = btn;
    		}
    	}

    	//
    	// Battery voltage detect
    	//
    	if ( bat.isAvailable() && tmBAT.isExpired(1000) ) {
    		tmBAT.reset();
			if ( CAdc::read(value) ) {
				percentage = (value / 1024.0f) * 100;
				bat.send(percentage);
			}
    	}

    	//
    	// Blink LED
    	//
    	ledRight = LED_ON;
    	sleep(10);
    	ledRight = LED_OFF;
    	if ( ble.isConnected() ) {
    		sleep(190);
    	} else {
    		sleep(990);
    	}
    }
}
