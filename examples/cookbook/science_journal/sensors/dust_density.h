/*
 ===============================================================================
 Name        : dust_density.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月22日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Dust Density Sensor
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月22日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef DUST_DENSITY_H_
#define DUST_DENSITY_H_

#include <class/thread.h>
#include <class/adc.h>

class GP2Y1010: public CThread {
public:
	/**
	 * @brief construct, to assign an analog pin to read the sensor data.
	 */
	GP2Y1010(uint8_t analog_pin, uint8_t led_pin);

	/**
	 * @brief start the thread, to run the sensor procedure.
	 */
	void enable();

	/**
	 * @brief stop the thread.
	 */
	void disable();

	/**
	 * @brief the sensor value
	 */
	float inline value() {
		return m_value;
	}

	virtual ~GP2Y1010();
protected:
	AIN_T 	m_analog_pin;
	uint8_t m_led_pin;
	float   m_value;
	virtual void run();
};

#endif /* DUST_DENSITY_H_ */
