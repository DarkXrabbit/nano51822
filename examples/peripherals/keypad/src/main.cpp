/*
===============================================================================
 Name        : main.c
 Author      :
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 :
 Description :
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------

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
#include <class/bus.h>
#include <class/timeout.h>

#include "keypad.h"

//
// key table 4x3
//
const char key_table[] = {
	'1', '4', '7', '*',
	'2', '5', '8', '0',
	'3', '6', '9', '#'
};

// TODO: insert other definitions and declarations here


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
	// Create keypad component
	//
	CBus rows(14, 15, 16, END);
	CBus cols(17, 18, 19, 20, END);

	CKeypad keypad(rows, cols, key_table);
	keypad.enable();


	CPin led0(7);	// led0 on P0.07
	led0.output();

	CTimeout tmLED;
	LPCTSTR pincode;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// check keypad input
    	//
    	pincode = keypad.wait(0, 0);
    	if ( pincode ) {
    		DBG("%s\n", pincode);
    	}

    	//
    	// blink LED
    	//
    	if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led0.toggle();
    	}

    }
}
