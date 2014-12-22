/*
===============================================================================
 Name        : rtos timer
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : A RTOS software timer demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/12/22 v1.0.	First Edition.									LEO
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
#include <class/ostimer.h>

// TODO: insert other definitions and declarations here
#define BOARD_PCA10001
//#define BOARD_LILYPAD
#include <config/board.h>

//
// OS timer handler
//
void tmrLED(osTimer *p_timer, xHandle param) {
	CPin *led = (CPin *) param;
	led->toggle();
}

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

	osTimer t(200, tmrLED, &led1);
	t.start();			// start the os timer

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	led0.toggle();
    	sleep(500);
    }
}
