/*
===============================================================================
 Name        : UART Echo
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : UART Echo example
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18 v1.0.0	First Edition.									Jason
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
#include <class/pin.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here


//
// Main Routine
//
int main(void) {
//#ifdef DEBUG
//	CSerial ser;		// declare a UART object
//	ser.enable();
//	CDebug dbg(ser);	// Debug stream use the UART object
//	dbg.start();
//#endif

	//
	// Your setup code here
	//
	CSerial	uart;		// declare a uart object
	uart.enable();

	CPin led0(18);		// declare led0 on P0.18
	led0.output();

	CTimeout tmLED;

	uint8_t ch;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// UART Echo
    	//
    	if ( uart.available() ) {
    		ch = uart;		// read a byte
    		uart << ch;		// write a byte
    	}

    	//
    	// LED blink
    	//
    	if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led0.toggle();
    	}
    }
}
