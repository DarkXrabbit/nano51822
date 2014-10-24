/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Example for TIMER & RTC
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/1	v1.0.0	First Edition for nano51822						Leo
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
#define BOARD_PCA10001
#include <config/board.h>

#include <class/ble/ble_device.h>
#include <class/pin.h>
#include <class/timer.h>
#include <class/thread.h>

// TODO: insert other definitions and declarations here

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

	CTimer t;				// declare a Timer object
	t.second(0.1);			// set Timer interval = 0.1 sec = 100ms
	t.enable();				// enable timer interrupt

	CPin led1(LED_PIN_0);	// declare a LED on P0.19
	led1.output();			// set the LED as an output pin

	//
    // Enter main loop.
	//
    while(1) {

    	if ( t.wait() ) {			// block and waiting for RTC interrupt
    		led1.toggle();
    	}
    }
}
