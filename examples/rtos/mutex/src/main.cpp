/*
===============================================================================
 Name        : mutex
 Author      : uCXpresso
 Version     : v1.0.0
 Description : A mutex of RTOS test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/12/1	v1.0.0	First Edition.									Leo
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
#include <class/mutex.h>
#include <class/button.h>

// TODO: insert other definitions and declarations here
#define BOARD_PCA10001
//#define BOARD_LILYPAD
#include <config/board.h>

CMutex	m_muxLED;
CPin led(LED_PIN_0);

//
// LED (Use mutex to lock/unlock the Resource)
//
void led_toggle() {
	m_muxLED.lock();
	led.toggle();
	m_muxLED.unlock();
}

void tskButton1(CThread *p_thread, xHandle p_params) {
	CButton btn(BUTTON_PIN_0);
	while( p_thread->isAlive() ) {
		if ( btn.isPressed()==BTN_PRESSED ) {
			led_toggle();
		}
	}
}

void tskButton2(CThread *p_thread, xHandle p_params) {
	CButton btn(BUTTON_PIN_1);
	while( p_thread->isAlive() ) {
		if ( btn.isPressed()==BTN_PRESSED ) {
			led_toggle();
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
	led.output();

	CThread t1(tskButton1);
	t1.start("t1");

	CThread t2(tskButton2);
	t2.start("t2");

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	NOTHING
    }
}
