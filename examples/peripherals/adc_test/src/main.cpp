/*
===============================================================================
 Name        : ADC Test
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : Analog to DC convertor
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18 v1.0.0	First Edition.									LEO
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
#include <class/adc.h>
#include <class/timeout.h>

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
	// Analog
	//
	CAdc::init();		// Initialize ADC module
	CAdc::enable();		// Enable the ADC module
	CAdc::pin(AD0);		// Select analog input on AD0 (P0.1)

	//
	// LED
	//
	CPin led0(18);		// declare led0 on P0.18
	CPin led1(19);		// declare led1 on P0.19
	led0.output();		// Set led0 as output pin
	led1.output();		// Set led1 as output pin

	CTimeout tmLED, tmADC;
	uint16_t value;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	if ( tmADC.isExpired(200) ) {
    		tmADC.reset();
    		if ( CAdc::read(value) ) {
    			DBG("%d\n", value);
    			led1.toggle();
    		}
    	}

    	//
    	// blink LED0
    	//
    	if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led0.toggle();
    	}
    }
}
