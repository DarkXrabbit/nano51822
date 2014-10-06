/*
===============================================================================
 Name        : main.c
 Author      : uCXpresso
 Version     : v1.0.0
 License	 : MIT
 Description : GPIO Interrupt Demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/5	v1.0.0	First for nano51822								Jason
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
#include <class/timeout.h>
#include <class/pin.h>
#include <class/thread.h>
#include <class/gpio_int.h>

// TODO: insert other definitions and declarations here

//
// GPIO Interrupt Demo Task
//
class tskGPIO : public CThread {
public:
	tskGPIO(int btn_pin, int led_pin) {
		m_btn_pin = btn_pin;
		m_led_pin = led_pin;
	}
protected:
	int m_btn_pin;
	int m_led_pin;

	//
	// Implement the CThread::run() member function.
	//
	virtual void run() {
		gpioINT	btn(m_btn_pin, INTERNAL_PULL_UP);	// declare a INT object with internal pull up.
		btn.enable(FALLING);						// Interrupt trigger on Falling.

		CPin led(m_led_pin);						// declare a LED pin.
		led.output();								// set the led as an output pin
		while(1) {
			if ( btn.wait() ) {						// block and waiting for an interrupt
				led.invert();						// blink led1
			}
		}
	}
};

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
	tskGPIO t1(16, 19);	// set button pin on P0.16 and LED on P0.19
	t1.start("gpio1", 56, PRI_HIGH);

	tskGPIO t2(17, 20);	// set button pin on 0.17 and LED on P0.20
	t2.start("gpio2", 56, PRI_HIGH);

	CPin led0(18);	// declare the led0 on P0.18
	led0.output();	// set led0 as an output pin

	CTimeout tm;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//
    	if ( tm.isExpired(500) ) {	// simple blink led demo (interval 500ms)
    		tm.reset();
    		led0.invert();
    	}
    }
}
