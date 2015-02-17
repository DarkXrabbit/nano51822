/*
===============================================================================
 Name        : MPU6050 Example
 Author      : uCXpresso
 Version     : v1.0.0
 Description : Exmple MPU6050 for I2CDev Class
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
#include <MPU6050.h>

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

	CPin led1(LED_PIN_1);
	led1.output();

	I2Cdev	i2c(23, 24);	// SDA=P0.23, SCL=P0.24, default CLK=100KHz
	i2c.enable();

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

	int16_t ax, ay, az;
	int16_t gx, gy, gz;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Show Gyroscope & Accelerometer values
    	//

    	if ( dbg.isDebugMode() ) {
			//
			// read raw accel/gyro measurements from device
			//
			accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
			DBG("ax=%d, ay=%d, az=%d, gx=%d, gy=%d, gz=%d\n",
					ax,
					ay,
					az,
					gx,
					gy,
					gz);

			sleep(100);

    	} else {
    		led1.toggle();
    		sleep(500);
    	}
    }
}
