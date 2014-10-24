/*
===============================================================================
 Name        : RTC
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : RTC demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/24	v1.0.0	First Edition for nano51822						Leo
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
#define BOARD_PCA10001
#include <config/board.h>

#include <class/pin.h>
#include <class/timeout.h>
#include <class/thread.h>
#include <class/rtc.h>

// TODO: insert other definitions and declarations here


//
// RTC second count
//
class tskRTC : public CThread {
public:
	tskRTC() {
		m_seconds = 0;
	}

	inline uint32_t seconds() {
		return m_seconds;
	}

protected:
	uint32_t m_seconds;
	virtual void run() {
		CPin led(LED_PIN_1);
		led.output();

		gpRTC->interval(1000);		// set rtc timer interval 1000ms
		while(isAlive()) {
			if ( gpRTC->wait() ) {	// wait for timer interrupt
				led.toggle();
				m_seconds++;
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

	//
	// RTC
	//
	rtcMS::clockSource(LF_EXTERNAL);	// select LF Clock Source
	rtcMS rtc;							// declare a rtc object
	rtc.enable();						// enable rtc

	//
	// Task
	//
	tskRTC t;
	t.start("clock");

	//
	// LED
	//
	CPin led(LED_PIN_0);
	led.output();

	CTimeout tmLED;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Debug
    	//
    	if ( dbg.available() ) {	// any key detect from consol
    		dbg.read();				// dump
    		DBG("seconds=%d \t tick=%d \n", t.seconds(), rtc.tick_count());
    	}

    	//
    	// Blink LED
    	//
    	if ( tmLED.isExpired(200) ) {
    		tmLED.reset();
    		led.toggle();
    	}
    }
}
