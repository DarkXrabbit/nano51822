/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 License	 : MIT
 Description : GPIO Interrupt Demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/5	v1.0.0	First for nano51822								Jason
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
#include <class/timeout.h>
#include <class/pin.h>
#include <class/thread.h>
#include <class/gpio_int.h>

// TODO: insert other definitions and declarations here

//
// GPIO Interrupt Task
//
class tskGPIO : public CThread {
protected:
	virtual void run() {
		gpioINT	btn(16, INTERNAL_PULL_UP);	// declare a button on P0.16 with internal pull up.
		btn.enable(FALLING);				// Interrupt trigger on Falling.

		CPin led1(19);						// declare a LED on P0.19
		led1.output();						// set led1 as an output pin
		while(isAlive()) {
			if ( btn.wait() ) {				// block and waiting for an interrupt
				led1.invert();				// blink led1
			}
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
	tskGPIO t;
	t.start("gpio", 96, PRI_HIGH);

	CPin led0(18);	// declare the led0 on P0.18
	led0.output();	// set led0 as an output pin

	CTimeout tm;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	if ( tm.isExpired(500) ) {	// simple blink led demo (interval 500ms)
    		tm.reset();
    		led0.invert();
    	}
    }
}
