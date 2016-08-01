/*
===============================================================================
 Name        : Quake Science
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : A BLE UART to Google Science Journal example
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016/7/28 v1.0.0	First Edition.									Jason
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
#include <class/ble/ble_conn_params.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     50                    	/**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059					/**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

#define BLE_ECHO	1
#define BOARD_NANO51822_UDK
#include <config/board.h>

const ble_uuid128_t science_base_uuid = {
    0xE8, 0x74, 0x2C, 0x65, 0xF0, 0x01, 0x38, 0x95,
	0x7A, 0x46, 0xAA, 0x0A, 0x00, 0x00, 0x5A, 0x55
};

#define UUID_SCIENCE_SERVICE	0x0001
#define UUID_SCIENCE_VALUE		0x0003	// Output (TXD)
#define UUID_SCIENCE_CONFIG		0x0010	// Input (RXD)

#include "config_change.h"
#include "goosci_utility.h"
#include <class/adc.h>
#include <class/watchdog.h>
#include <utils/utils.h>
#include <arm_math.h>
#include "HMC5883L.h"

float sqrt1(const float x) {
	union{
		int i;
		float x;
	} u;
	u.x = x;
	u.i = (1<<29) + (u.i >> 1) - (1<<22);

	// Two Babylonian Steps (simplified from:)
	// u.x = 0.5f * (u.x + x/u.x);
	// u.x = 0.5f * (u.x + x/u.x);
	u.x =       u.x + x/u.x;
	u.x = 0.25f*u.x + x/u.x;

	return u.x;
}

//
// Main Routine
//
int main(void) {
	CSerial ser(64, 64);		// declare a Serial object
	ser.enable();
#ifdef DEBUG
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
//	dbg.waitToDebugMode();
#endif

	//
	// SoftDevice
	//
	bleDevice ble;	// use internal 32.768KHz for SoftDevice
	ble.enable();	// enable BLE SoftDevice stack

	// GAP
	char *device_name = spn_malloc(17, "地震電訊%02X", ble.address()[0]);
	ble.m_gap.settings(device_name, 20, 20);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_4dBm);	// set Output power
	free(device_name);

	//
	// Add BLE UART Service
	//
	bleServiceUART	bleScience( ble,
								false,
								&science_base_uuid,
								UUID_SCIENCE_SERVICE,
								UUID_SCIENCE_VALUE,
								UUID_SCIENCE_CONFIG
								);

	//
	// Add "connection parameters update" negotiation. (optional)
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier
	ble.m_advertising.add_uuid_to_complete_list(bleScience);
	ble.m_advertising.update();										// update advertising data

	// Start advertising
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.start();

	//
	// Your Application setup code here
	//
	CPin led1(LED1);	// led0 on P0.18
	CPin led2(LED2);	// led1 on P0.19
	CPin led3(LED3);

	led1.output();	// set led0 as an output pin
	led2.output();	// set led1 as an output pin
	led3.output();

	//
	// I2C
	//
	I2Cdev i2c;			// declare the i2c (SDA=29, SCL=28)
	i2c.enable();		// enable the i2c

	// class default I2C address is 0x1E
	// specific I2C addresses may be passed as a parameter here
	// this device only supports one I2C address (0x1E)
	HMC5883L mag(&i2c);
	mag.initialize();

	int16_t x, y, z;

	//
	// ADC
	//
	CAdc::init();
	CAdc::enable();

	//
	// Other
	//
	CTimeout	tm, period;
	uint8_t		buffer[64];
	uint16_t 	size, value1, value2;
	float 		minOffset = 0, last  = 0, sensorValue = 0;
	uint16_t 	offset = 0;

	Console con(ser);
	bool sendForFirst = true;

	// watchdog
	WDT::timeout(5.0f);
	WDT::enable();

	//
    // Enter main loop.
	//
    while(1) {

    	WDT::feed();
    	//
		// read analog
    	//
		if ( pin_type == ANALOG ) {

			switch(pin) {
			// measure Analog
			case 0:
				CAdc::read(AD1, value1);
				CAdc::read(AD3, value2);
				sensorValue = (value1 - value2) * 3600.0f / 1024;
				minOffset = 100;
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				CAdc::read(analog_pin[pin+1], value1);
				sensorValue = (value1 * 3600.0f / 1024);
				minOffset = 50;
				break;

			// measure I2C device
			default:
				if ( mag.getReadyStatus() ) {
					mag.getHeading(&x, &y, &z);
					sensorValue = sqrt1((x*x) + (y*y) + (z*z));
					minOffset = 10;
				}
			}
			offset = fabs(last - sensorValue);
		//
		// read digital data
		//
		} else {
			CPin di(pin);
			di.input();
			sensorValue = di.read();
		}

		//
		// Science Journal App connected
		//
    	if ( bleScience.isAvailable() ) {	// check BLE NUS service
    		led2 = LED_ON;

    		// receive configurations
    		size = bleScience.readable();
    		if ( size > 0 ) {
    			bleScience.read(buffer, size);
    			handle(buffer, size);
    			sendForFirst = true;
    			DBG("Google Pin:%d\n", pin);
    		}

			// send data
			if ( period.isExpired(60000) || (offset >= minOffset && bleScience.isTxBusy() == false) || sendForFirst ) {
				led3 = LED_ON;
				period.reset();
				if (pin==0) {
					send_data(bleScience, GetSystemTickCount(), sensorValue + 3600.0);	// with shift
				} else {
					send_data(bleScience, GetSystemTickCount(), sensorValue);
				}
				last = sensorValue;
				led3 = LED_OFF;
				sendForFirst = false;
			}

		//
		// Disconnected
		//
    	} else {
    		led2 = LED_OFF;
    		// Serial Data
    		if ( dbg.isDebugMode() == false ) {
				if ( period.isExpired(1000) || (offset >= minOffset && period.isExpired(10)) ) {
					led3 = LED_ON;
					period.reset();
					con.printf("%d,%0.2f\n",  GetSystemTickCount(), sensorValue);
					last = sensorValue;
					led3 = LED_OFF;
				}
    		}
    	}

    	//
    	// blink led
    	//
    	if ( tm.isExpired(500) ) {
    		tm.reset();
    		led1 = !led1;	// blink led
    	}

    	//
    	// Negotiate the "Connect Parameters Update"
    	//
    	conn.negotiate();
    }
}
