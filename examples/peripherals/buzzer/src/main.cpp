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
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif

// TODO: insert other include files here
#include <class/power.h>
#include <class/pin.h>
#include <class/button.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define BOARD_PCA10001
//#define BOARD_LILYPAD
#include <config/board.h>

#include "buzzer.h"

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
	CButton btn(BUTTON_PIN_0);

	CBuzzer buz(15);	// buzzer on P0.15
	buz.enable();

	CPin led(LED_PIN_0);
	led.output();

	CTimeout tmLED;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	switch(btn.isPressed()) {
    	case BTN_PRESSED:
    		buz.post(3);	// turn on buzzer x 3
    		break;
    	case BTN_RELEASED:
    		break;
    	case BTN_NOTHING:
    		break;
    	}

    	if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led.toggle();
    	}
    }
}
