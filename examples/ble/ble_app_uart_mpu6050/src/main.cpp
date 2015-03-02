/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : free
 Description : A G+A (MPU6050) sensor demo wtih BLE UART (nRF UART)
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/3/2	v1.0.0	First Edition.									LEO
 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif

// TODO: insert other include files here
//#include <class/ble/ble_device_manager.h>
#include <class/ble/ble_device.h>
#include <class/ble/ble_conn_params.h>
#include <class/ble/ble_service_uart.h>
#include <class/power.h>
#include <class/pin.h>

#include <class/console.h>
#include "MPU6050.h"

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "MPU6050"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     500                    /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059                 /**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

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
	//
	// SoftDevice
	//
	bleDevice ble;
	ble.enable();	// enable BLE SoftDevice task

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

	//
	// Add BLE UART Service
	//
	bleServiceUART nus(ble);			// declare a BLE "Nordic UART Service" (NUS) object

	//
	// Optional: Add "Connection Parameters Update" negotiation.
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

	// Optional: add standard profile uuid in advertisement.

	// Optional: add appearance to indicate who you are in advertisement.
	ble.m_advertising.update();										// update advertisement data

	// Start advertising
	ble.m_advertising.start();

	//
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Console output to BLE UART
	//
	Console con(nus);	// assign the nus (BLE-UART) stream to console.

	//
	// LEDs
	//
	CPin led0(LED_PIN_0);
	led0.output();

	CPin led1(LED_PIN_1);
	led1.output();

	//
	// I2C Interface
	//
	I2Cdev	i2c(23, 24);	// SDA=P0.23, SCL=P0.24, default CLK=100KHz
	i2c.enable();

	// MPU6050
	// class default I2C address is 0x68
	// specific I2C addresses may be passed as a parameter here
	// AD0 low = 0x68 (default for InvenSense evaluation board)
	// AD0 high = 0x69
	MPU6050 accelgyro(i2c);

	// initialize device
	accelgyro.initialize();

	// check device
	if ( accelgyro.testConnection() ) {
		led0 = LED_ON;
	}

	// Variable
	int16_t ax, ay, az;
	int16_t gx, gy, gz;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Negotiate the "connection parameters update" in main-loop
    	//
    	conn.negotiate();

    	//
    	// check BLE UART connected
    	//
    	if ( nus.isConnected() ) {
			//
			// read raw accel/gyro measurements from device
			//
			accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
			con.printf("ax=%d, ay=%d, az=%d", ax, ay, az);
			con.printf("gx=%d, gy=%d, gz=%d\n", gx, gy, gz);

			sleep(500);

    	} else {
    		led0 = LED_ON;
    		sleep(10);
    		led0 = LED_OFF;
    		sleep(990);
    	}
    }
}
