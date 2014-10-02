/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : Watchdog Test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/5	v1.0.0	First Edition for nano51822						Leo
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
#include <class/watchdog.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here

int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif

	CWatchdog wdt;
	wdt.timeout(5);		// set watchdog timeout in 5 seconds
	wdt.enable();

	CPin led(18);
	led.output();

	CTimeout tm;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// LED blink demo
    	//
    	if ( tm.isExpired(500) ) {
    		tm.reset();
    		led.invert();
    	}

    	//
    	// Watchdog feed
    	//
    	CWatchdog::feed();	// if mask, will cause the system reset.

    	//
    	// BLE event manager (keep in main loop)
    	//
    	bleDevice::waitForEvent();
    }
}
