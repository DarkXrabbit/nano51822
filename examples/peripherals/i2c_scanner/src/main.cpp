/*
===============================================================================
 Name        : I2C Scanner
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : To discovery the I2C peripherals
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/15 v1.0.0	First Edition.									LEO
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
#include <class/i2cdev.h>
#include <class/timeout.h>
#include <class/ble/ble_device.h>
// TODO: insert other definitions and declarations here


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

	bleDevice ble;
	ble.enable();

	//
	// Your setup code here
	//
	CPin led0(18);	// declare led0 on P0.18
	CPin led1(19);	// declare led1 on P0.19
	led0.output();
	led1.output();

	I2Cdev i2c(28, 29);	// declare the i2c on the P0.09 (dat) and P0.10 (clk)
	i2c.enable();		// enable the i2c

	CTimeout tm;

	uint8_t data,addr = 0;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	if ( dbg.available() ) {
    		dbg.read();
    		addr = 1;	// any key on console to start the I2C scan
    		DBG("Start I2C Scanner:\n");
    	}

    	if ( addr ) {
			if ( i2c.readByte(addr, 0, &data) ) {
				dbg.printf(" 0x%02X ", addr);
			} else {
				dbg.putc('.');
			}
			addr = (addr+1) & 0x7F;	// to next address
			if (addr==0 ) {
				DBG("\nStop I2C Scanner.\n");
			}
    	}

    	// blink led
    	if ( tm.isExpired(500) ) {
    		tm.reset();
    		led0.invert();
    	}
    }
}
