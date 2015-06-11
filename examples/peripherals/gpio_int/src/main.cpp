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
#include <class/gpio_int.h>

//
// Hardware
//
//#define BOARD_LILYPAD
//#define BOARD_PCA10001
#define BOARD_NANO51822_UDK
#include <config/board.h>

//
// LED
//
CPin led1(LED1);
CPin led2(LED2);

//
// Test: Interrupt Handle
//
void intButton(INT_T number) {
	switch(number) {
	case INT0:
		led1.invert();
		break;
	case INT1:
		led2.invert();
		break;
	default:
		break;
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

	led1.output();
	led2.output();

	//
	// declare interrupt
	//
	gpioINT int1(INT0, intButton, BTN1);
	int1.enable();

	gpioINT int2(INT1, intButton, BTN2);
	int2.enable();

	//
	//
	//
	CPin led3(LED3);
	led3.output();

	CPin led4(LED4);
	led4.output();

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Test: read the interrupt pin
    	//
    	if ( int1==LOW || int2==LOW ) {
    		led3 = LED_ON;
    	} else {
    		led3 = LED_OFF;
    	}

		//
		// Activity LED
		//
    	led4.invert();
    	sleep(500);
    }
}
