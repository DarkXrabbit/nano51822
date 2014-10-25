/*
===============================================================================
 Name        : FireFly
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : A software PWM demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18 v1.0.0	First Edition.									LEO
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
#include <class/pin.h>
#include <class/timeout.h>
#include <class/hw_pwm.h>

// TODO: insert other definitions and declarations here
#define BOARD_PCA10001
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
	// PWM (Using Timer2)
	//
	hwPWM pwm(5, 6, 7);				// set PWM pins on P0.5 (CH1), P0.6 (CH2) and P0.7 (CH3)
	pwm.period(0.0002);				// period time = 200us
	pwm.enable();					// enable PWM module

	// update pwm2 channels duty-cycle (can be updated in any-time)
	pwm.dutycycle(PWM_CH_1, 0.8f);	// CH1 duty-cycle = 80%
	pwm.dutycycle(PWM_CH_2, 0.6f);	// CH2 duty-cycle = 60%
	pwm.dutycycle(PWM_CH_3, 0.2f);	// CH3 duty-cycle = 20%

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
    	// FireFly loop
    	//
    	if ( tmLED.isExpired(500) ) {
    		tmLED.reset();
    		led.toggle();
    	}

    }
}
