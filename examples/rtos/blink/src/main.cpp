/*
===============================================================================
 Name        : blink
 Author      : uCXpresso
 Version     : v1.0.1
 Copyright   : www.ucxpresso.net
 Description : A LED blink example with RTOS
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18 v1.0.0	First Edition.									LEO
 2014/12/8	v1.0.1	Use task handle instead of the run() member.	LEO
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
#include <class/thread.h>

// TODO: insert other definitions and declarations here
//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

/*
 * A task class to blink the led1
 */
void tskBlink(CThread *p_thread, xHandle p_param) {
	CPin led1(LED_PIN_1);					// declare led1 on P0.19
	led1.output();					// set led1 as output pin.
	while( p_thread->isAlive() ) {	// check task alive
		led1.toggle();				// toggle the led1
		sleep(100);
	}
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
	// Your setup code here
	//
	CThread t(tskBlink);
	t.start("blink");	// start the blink task

	CPin led0(LED_PIN_0);		// declare led0 on p0.18
	led0.output();

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	led0.toggle();	// toggle the led0
    	sleep(500);
    }
}
