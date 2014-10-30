/*
===============================================================================
 Name        : Tickless Test
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : To measure the current when tickless enable and disable.
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/30 v1.0.0	First Edition.									Jason
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
#include <class/power.h>


// TODO: insert other definitions and declarations here
//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>


//
// Main Routine
//
int main(void) {
// for Tickless Technology, Must build by "Release build".
#ifdef DEBUG
	CSerial ser;
	ser.enable();
	CDebug dbg(ser);
	dbg.start();
#endif
	//
	// Your setup code here
	//
	CPin led(LED_PIN_0);
	led.output();

	CPin btn(1);
	btn.input();

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Enable/Disable tickless technology
    	//
    	if ( btn==HIGH ) {
    		CPowerSave::tickless(true);	// default (internal pull-up)
    	} else {
    		CPowerSave::tickless(false);
    	}

    	//
    	// Blink led with short time
    	//
    	led = LED_ON;
    	sleep(10);
    	led = LED_OFF;
    	sleep(500);
    }
}
