/*
===============================================================================
 Name        : BMP180 Sensor
 Author      : uCXpresso
 Version     : v1.0.0
 Description : I2Cdev library collection - BMP180 basic example sketch
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
#include <class/timeout.h>
#include <BMP085.h>

// TODO: insert other definitions and declarations here
#define BOARD_PCA10001
//#define BOARD_LILYPAD
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

	I2Cdev i2c(23, 24);	// SDA=P0.23, SCL=P0.24
	i2c.enable();

	// class default I2C address is 0x77 (default)
	// specific I2C addresses may be passed as a parameter here
	// (though the BMP085 supports only one address)
	BMP085 barometer(i2c);
	barometer.initialize();

	float temperature;
	float pressure;
	float altitude;

	CTimeout tm;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	if ( dbg.isDebugMode() ) {

    	    // request temperature
    	    barometer.setControl(BMP085_MODE_TEMPERATURE);
    		tm.reset();
     	    while ( tm.isExpired(barometer.getMeasureDelayMilliseconds())==false );

    	    // read calibrated temperature value in degrees Celsius
    	    temperature = barometer.getTemperatureC();

    	    // request pressure (3x oversampling mode, high detail, 23.5ms delay)
    	    barometer.setControl(BMP085_MODE_PRESSURE_3);
    	    tm.reset();
    	    while ( tm.isExpired(barometer.getMeasureDelayMilliseconds())==false );

    	    // read calibrated pressure value in Pascals (Pa)
    	    pressure = barometer.getPressure();

    	    // calculate absolute altitude in meters based on known pressure
    	    // (may pass a second "sea level pressure" parameter here,
    	    // otherwise uses the standard value of 101325 Pa)
    	    altitude = barometer.getAltitude(pressure);

    		DBG("T:%0.1f\t P:%0.2f\t A:%0.2f\n", temperature, pressure, altitude);
    		tm.wait(100);

    	} else {
    		led0.toggle();
    		sleep(500);
    	}
    }
}
