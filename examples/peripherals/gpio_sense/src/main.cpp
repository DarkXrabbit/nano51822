/*
===============================================================================
 Name        : gpio_sense
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : GPIO sense test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/15 v1.0.0	First Edition.									LEO
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

//
// task parameter structure for demo
//
typedef struct {
	uint8_t sense_pin;
	SENSE_T trigger;
	uint8_t led_pin;
}SENSE_PARAM_T;

//
// Sense Test Task
//
void senseTask(CThread *p_thread, xHandle p_param) {
	SENSE_PARAM_T *p_sense = (SENSE_PARAM_T *)  p_param;

	gpioSense sense(p_sense->sense_pin, p_sense->trigger, NEITHER);
	sense.enable();

	CPin led(p_sense->led_pin);
	led.output();

	while( p_thread->isAlive() ) {
		if ( sense.wait() ) {
			led.toggle();
		}
	}
}

//
// Hardware
//
//#define BOARD_LILYPAD
//#define BOARD_PCA10001
#define BOARD_NANO51822_UDK
#include <config/board.h>

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
	// task 1
	//
	static const SENSE_PARAM_T sense_t1 = {16, FALLING, LED_PIN_0};	// task parameters, Sense=P0.16, LED=LED0
	CThread t1(senseTask, (xHandle) &sense_t1);
	t1.start("t1", 62, PRI_HARDWARE);

	//
	// task 2
	//
	static const SENSE_PARAM_T sense_t2 = {17, TOGGLE, LED_PIN_1};	// task parameters, Sense=P0.17, LED=LED1
	CThread t2(senseTask, (xHandle) &sense_t2);
	t2.start("t2", 62, PRI_HARDWARE);

	//
	// test pin
	//
	CPin test(15);
	test.output();

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	test.toggle();	// Use wire to connect the test pin to sense pin for test.
    }
}
