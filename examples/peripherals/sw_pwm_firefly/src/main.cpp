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
#include <class/sw_pwm.h>
#include <math.h>

// TODO: insert other definitions and declarations here
#define LED0	18		// LED0 on P0.18
#define LED1	19		// LED1 on P0.19
#define LED2	20		// LED2 on P0.20
#define LED3	21		// LED3 on P0.21
#define LED4	22		// LED4 on P0.22

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
	// Your setup code here
	//
	swPWM pwm;
	pwm.period(0.025);		// set the period time of PWM to 25ms.
	pwm.add_channel(LED0);	// add PWM channel with LED0
	pwm.add_channel(LED1);	// add PWM channel with LED1
	pwm.add_channel(LED2);	// add PWM channel with LED2
	pwm.add_channel(LED3);	// add PWM channel with LED3
	pwm.add_channel(LED4);	// add PWM channel with LED4
	pwm.start();			// start the pwm

	float y;
	int x[5] = { 0, 9, 18, 27, 36 };        // initialize all channels x degree

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// FireFly loop
    	//
		for (int ch = 0; ch < 5; ch++) {
			x[ch] = (x[ch] + 2) % 360;                  		// degree 0~360, step by 2
			y = sin((x[ch] * M_PI) / 180.0);                 // y = sine @x
			pwm.update(ch, map(y, -1.0f, 1.0f, 0.0f, 1.0f)); // update the duty-cycle of channel
		}
		sleep(20);    // speed
    }
}
