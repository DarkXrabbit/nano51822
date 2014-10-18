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
public:
	tskTimer(float sec, int led_pin) {
		m_interval = sec;
		m_led_pin = led_pin;
	}

protected:
	float m_interval;
	int	  m_led_pin;

	//
	// Implement CThread::run() member function
	//
	virtual void run() {
		CPin led(m_led_pin);	// declare a LED object
		led.output();			// set the LED as an output pin

		CTimer t;				// declare a Timer object
		t.second(m_interval);	// set Timer interval
		t.enable();				// enable timer interrupt

		while(isAlive()) {
			if ( t.wait() ) {	// block and waiting a timer interrupt
				led.invert();
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

	tskTimer t1(0.1, 18);			// set timer interval 0.1 second with P0.18 led
	t1.start("Timer1", 56, PRI_HIGH);

//	CRTC::clockSource(LF_EXTERNAL);	// set RTC clock source from External crystal.
	CRTC rtc;						// declare a RTC object
	rtc.interval(1.0);				// set RTC interval 1 second
	rtc.enable();					// enable RTC interrupt

	CPin led1(19);					// declare a LED on P0.19
	led1.output();					// set the LED as an output pin

	//
    // Enter main loop.
	//
    while(1) {

    	if ( rtc.wait() ) {			// block and waiting for RTC interrupt
    		led1.invert();
    	}
    }
}
