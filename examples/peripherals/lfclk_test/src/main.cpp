/*
===============================================================================
 Name        : Low Frequency CLOCK Test
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 Description : LFCLK Test with GPIO,
 	 	 	   Use the lfclk_test to calibrate your 32.768KHz crystal.
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/28 v1.0.0	First Edition.									Jason
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


// TODO: insert other definitions and declarations here
//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

//
// LFCLK probe Pin
//
CPin pinProbe(1);	// declare the LFCLK probe pin on P0.01

//
// On System Tick Event
// The system tick frequency will be 1024Hz.
// So, probe pin toggle frequency could be 512Hz.
//
extern "C" void on_sys_tick(uint32_t count) {
	pinProbe.toggle();
}

//
// Main Routine
//
int main(void) {
	//
	// Your setup code here
	//
	CPin led(LED_PIN_0);
	led.output();

	pinProbe.output();

	led = LED_ON;

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Don't enter Tickless mode to measure the tick
    	//
//		led = LED_ON;
//		sleep(10);
//		led = LED_OFF;
//    	sleep(100);
    }
}
