/*
 ===============================================================================
 Name        : dust_density.cpp
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月22日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Sensors
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月22日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#include "dust_density.h"
#include <class/adc.h>
#include <class/pin.h>
#include <class/middle_filter.h>

#define SENSOR_DEBUG	0

#if SENSOR_DEBUG
#include <debug.h>
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif


GP2Y1010::GP2Y1010(uint8_t ana_pin, uint8_t led_pin) {
	m_analog_pin = analog_pin[ana_pin];
	m_led_pin = led_pin;
	m_value = 0;
}

GP2Y1010::~GP2Y1010() {
}

void GP2Y1010::enable() {
	if ( isSuspend() ) {
		resume();
	} else {
#if SENSOR_DEBUG
		start("gp2y1010", 128);
#else
		start("gp2y1010");
#endif
	}
}

void GP2Y1010::disable() {
	suspend();
}

void GP2Y1010::run() {
	CPin led(m_led_pin);
	uint16_t raw_value;
	float voltage;
	CMiddleFilter filter(15);
	led.output(HIGH);
	while(isAlive()) {
		led = LOW;		// LED_ON
		delay_us(280);	// Sample Time
		CAdc::read(m_analog_pin, raw_value);
		delay_us(40);	// Delta Time
		led = HIGH;		// LED_OFF

		// VCC = 5V
		//voltage = map(raw_value, 0, 1023, 0, 5.0);

		// VCC = 3V, map to 5V. 852 = (3v x 1024 /3.6) - 1
		voltage = map(raw_value, 0, 852, 0, 5.0);

		// Voc = no dust = 0.1v
		if (  voltage >= 0.1) {
			// map Voc ~ Vmax to 0 ~ 0.5 mg/m3
			m_value = filter.update(map(voltage, 0.1, 3.75, 0, 0.5));
		}
		DBG("raw:%d voltage:%0.2f value:%0.4f\n", raw_value, voltage, m_value);
		sleep(100);
	}
}
