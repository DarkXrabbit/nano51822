/*
===============================================================================
 Name        : blink
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : A LED blink example with RTOS
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
#include <class/thread.h>

// TODO: insert other definitions and declarations here

/*
 * A task class to blink the led1
 */
class tskBlink : public CThread {
protected:
	virtual void run() {
		CPin led1(19);			// declare led1 on P0.19
		led1.output();			// set led1 as output pin.
		while( isAlive() ) {
			led1.toggle();		// toggle the led1
			sleep(100);
		}
	}
};

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
	tskBlink t;
	t.start("blink");	// start the blink task

	CPin led0(18);		// declare led0 on p0.18
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
