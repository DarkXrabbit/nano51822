/*
===============================================================================
 Name        : adc_touch_key
 Author      : uCXpresso
 Version     : v1.0.1
 Copyright   : www.ucxpresso.net
 Description : Make Touch Key/Switch by ADC
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/4/11 v1.0.0	First Edition.									LEO
 2015/4/18 v1.0.1	Add "Auto Tuning".								Jason
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
#include <class/gpio_sense.h>
#include <class/timeout.h>
#include <class/adc.h>

//
// Hardware
//
//#define BOARD_LILYPAD
//#define BOARD_PCA10001
#define BOARD_NANO51822_UDK
#include <config/board.h>

//
// Sense Test Task
//
#define TK_PRESSED	0
void senseTask(CThread *p_thread, xHandle p_param) {

	CPin led(LED_PIN_0);
	led.output();

	CTimeout tmBounce;
	uint16_t avg=0, max, min, value;

	//
	// auto tuning
	//
	for (int i=0; i<10; i++) {
		if ( CAdc::read(AD0, value) ) {
			avg += value;
		}
		sleep(100);
	}
	avg = avg / 10;
	max = avg * 1.1f;
	min = avg * 0.9f;

#ifdef DEBUG
//	gpDBG->waitToDebugMode();
//	DBG("avg=%d, max=%d, min=%d\n", avg, max, min);
#endif

	// touch key task loop
	uint16_t flag = 0;
	while( p_thread->isAlive() ) {
		if ( CAdc::read(AD0, value) ) {
			if ( value>max || value<min ) {
				//
				// Touch
				//
				if ( bit_chk(flag, TK_PRESSED)==false ) {
					if ( tmBounce.isExpired(10) ) {
						bit_set(flag, TK_PRESSED);
						led = LED_ON;
					}
				} else tmBounce.reset();
			} else {
				//
				// Release
				//
				if ( bit_chk(flag, TK_PRESSED)==true ) {
					if ( tmBounce.isExpired(10) ) {
						bit_clr(flag, TK_PRESSED);
						led = LED_OFF;
					}
				} else tmBounce.reset();
			}
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

	CAdc::init();			// AREF internal VBG
	CAdc::source(AIN);	// source from internal: VDD x 1/3
	CAdc::enable();

	//
	// task 1
	//
	CThread t1(senseTask);
#ifdef DEBUG
	t1.start("t1", 128);	// more stack size for DBG
#else
	t1.start("t1", 72);
#endif

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    }
}
