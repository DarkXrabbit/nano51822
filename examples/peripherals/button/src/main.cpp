/*
===============================================================================
 Name        : button test
 Author      : uCXpresso
 Version     : v1.0.0
 License	 : MIT
 Description : A button pin test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/13 v1.0.0	First Edition.									Jason
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
#include <button.h>

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
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Your setup code here
	//
	CButton btn(16);	// declare a button input pin on P0.16

	CPin led(18);		// declare a led on P0.18
	led.output();

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// button detect
    	//
    	if ( btn.isPress() ) {
    		led.toggle();
    	}

    }
}
