/*
===============================================================================
 Name        : semaphore
 Author      : uCXpresso
 Version     : v1.0.0
 Description : A semaphore of RTOS test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/12/1 v1.0.0	First Edition.									Leo
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
#include <class/thread.h>
#include <class/semaphore.h>
#include <class/button.h>

// TODO: insert other definitions and declarations here
#define BOARD_PCA10001
//#define BOARD_LILYPAD
#include <config/board.h>

CSemaphore	m_semButton;

void tskLED1(CThread *p_thread, xHandle p_params) {
	CPin led1(LED_PIN_0);
	led1.output();
	while( p_thread->isAlive() ) {
		if ( m_semButton.wait() ) {	// wait for the semaphore
			led1.toggle();
		}
	}
}

void tskLED2(CThread *p_thread, xHandle p_params) {
	CPin led2(LED_PIN_1);
	led2.output();
	while( p_thread->isAlive() ) {
		if ( m_semButton.wait() ) {	// wait for the semaphore
			led2.toggle();
		}
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
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Your setup code here
	//

//	m_semButton.counting(2, 2);
	m_semButton.binary();

	CThread t1(tskLED1);
	t1.start("t1");

	CThread t2(tskLED2);
	t2.start("t2");

	// button
	CButton btn(BUTTON_PIN_0);

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	if ( btn.isPressed()==BTN_PRESSED ) {
    		m_semButton.release();	// signal the semaphore
    	}
    }
}
