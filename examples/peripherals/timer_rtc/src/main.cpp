/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Example for TIMER & RTC
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/1	v1.0.0	First Edition for nano51822						Leo
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
#include <class/ble/ble_device.h>
#include <class/pin.h>
#include <class/timer.h>
#include <class/rtc.h>
#include <class/thread.h>

// TODO: insert other definitions and declarations here
class tskTimer: public CThread {
protected:
	virtual void run() {
		CPin led0(18);
		led0.output();
		CTimer t;
		t.second(0.2);
		t.enable();
		while(isAlive()) {
			if ( t.wait() ) {
				led0.invert();
			}
		}
	}
};

int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif

	CPin led1(19);
	led1.output();

	tskTimer t;
	t.start("Timer", 56, PRI_HIGH);

	CRTC::clockSource(LF_INTERNAL);
	CRTC rtc;
	rtc.interval(0.5);
	rtc.enable();

	//
    // Enter main loop.
	//
    while(1) {

    	if ( rtc.wait() ) {
    		led1.invert();
    	}

    	//
    	// BLE event manager
    	//
    	bleDevice::waitForEvent();
    }
}
