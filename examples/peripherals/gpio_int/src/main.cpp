/*
===============================================================================
 Name        : gpio_init
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : GPIO Interrupt Demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/3 v1.0.0	First Edition.									LEO
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
#include <class/power.h>
#include <class/pin.h>
#include <class/thread.h>
#include <class/gpio_int.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here

class tskGPIO: public CThread {
protected:
	virtual void run() {
		// setup led
		CPin led(19);							// declare a led to connect to P0.19
		led.output();							// set led as output pin

		// setup gpio interrupt
		gpioINT btn(17, INTERNAL_PULL_UP);		// delcare a btn to connect to interrupt on P0.17
		btn.enable(FALLING);					// enable interrupt with FALLING trigger.

		// interrupt loop code
		while(1) {
			// wait for interrupt
			btn.wait();							// wait interrupt
			led.toggle();						// do interrupt code here
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
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Your setup code here
	//
	tskGPIO t;
	t.start("gpio", 58, PRI_HARDWARE);	// set interrupt task priority to high

	CPin led(18);						// declare led to connect to P0.18
	led.output();

	CTimeout tmLED;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// blink led
    	//
    	if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led.toggle();
    	}
    }
}
