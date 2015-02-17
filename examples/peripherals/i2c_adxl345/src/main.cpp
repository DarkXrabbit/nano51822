/*
===============================================================================
 Name        : ADXL345 Example
 Author      : uCXpresso
 Version     : v1.0.0
 Description : ADXL345 demo for I2Cdev class
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/2/15 v1.0.0	First Edition.									LEO
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
#include <class/power.h>
#include <class/pin.h>
#include <ADXL345.h>

// TODO: insert other definitions and declarations here
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
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Your setup code here
	//
	CPin led0(LED_PIN_0);
	led0.output();

	I2Cdev i2c(23, 24);		// SDA=P0.23, SCL=P0.24
	i2c.enable();

	// class default I2C address is 0x53
	// specific I2C addresses may be passed as a parameter here
	// ALT low = 0x53 (default for SparkFun 6DOF board)
	// ALT high = 0x1D
	// CS high = I2C I/F
	ADXL345 accel(i2c);

	// initialize device
	accel.initialize();

	int16_t ax, ay, az;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Show accelerometer value
    	//
    	if ( dbg.isDebugMode() ) {
    		// read raw accel measurements from device
    		accel.getAcceleration(&ax, &ay, &az);
    		DBG("ax=%d, ay=%d, az=%d\n", ax, ay, az);
    		sleep(100);
    	} else {
    		led0.toggle();
    		sleep(500);
    	}
    }
}
