/*
===============================================================================
 Name        : system_power_off
 Author      : uCXpresso
 Version     : v1.0.0
 Description : A system power off test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
2014/11/20 v1.0.0	First Edition.									Leo
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
#include <class/gpio_sense.h>
#include <class/timeout.h>

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
	// Wake-Up by a gpioSense pin.
	//
	gpioSense btn(1, FALLING, INTERNAL_PULL_UP);	// set sense pin on P0.1
	btn.enable();

	//
	// LED
	//
	CPin led(LED_PIN_0);
	led.output();

	CTimeout tmPowerOff;
	//
    // Enter main loop.
	//
    while(1) {
    	// check button
    	if ( btn.wait(0) ) {
    		led = LED_ON;				// button pressed
    	} else {
    		led.toggle();
    	}

    	// check timeout
    	if ( tmPowerOff.isExpired(30000) ) {
    		led = LED_OFF;
    		CPowerSave::system_off();	// enter to power off mode
    	}

    	sleep(500);
    }
}
