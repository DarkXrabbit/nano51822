/*
 ===============================================================================
 Name        : delete task
 Author      :
 Version     : v1.0.0
 Date		 :
 Copyright   :
 License	 :
 Description : A demo to create and delete a task repeated.
 ===============================================================================
  	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18 v1.0.0	First Edition.									LEO
 ===============================================================================
 */

#include <uCXpresso.h>
#include <class/serial.h>

#ifdef DEBUG
#include "debug.h"
#define DBG		dbg_printf
#else
#define DBG(...)
#endif

//
// TODO: insert other include files here
//
#include <class/thread.h>

#define LED0 18
#define LED1 19

//
// TODO: insert other definitions and declarations here
//

class ledTask: public CThread {
public:
	virtual void run() {
		CPin led(LED1);
		led.output();

		while(isAlive()) {		// in task loop
			led.toggle();		// blink LED1 (first)
			sleep(100);
		}
		led = LED_OFF;
	}
};

//
// main task
//
int main(void) {

#ifdef DEBUG
	CSerial ser;
	ser.enable();
	CDebug dbg(ser);
	dbg.start();
#endif

	/*************************************************************************
	 *
	 *                         your setup code here
	 *
	 **************************************************************************/
	ledTask *t = NULL;

	CPin led(LED0);
	led.output();

	while(1) {
		/**********************************************************************
		 *
		 *                         your loop code here
		 *
		 **********************************************************************/
		if ( t==NULL ) {
			t = new ledTask;	// alloc a LED task
			t->start("LED");	// start the task
		} else {
			delete t;			// delete the LED task
			t = NULL;
		}

		led.toggle();			// in main-loop, blink LED0 (slow)
		sleep(500);
	}
    return 0 ;
}
