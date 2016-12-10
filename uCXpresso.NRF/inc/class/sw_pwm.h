/*
 ===============================================================================
 Name        : Software PWM
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/18
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Use timer to implement the PWM
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2012/10/18	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef _SW_PWM_H_
#define _SW_PWM_H_

#include <class/thread.h>
#include <class/timer.h>
#include <class/list.h>
#include <class/pin.h>

#define SW_PWM_RESOLUTION	(0.000028f)		///< PWM resolution was 64us.

/**
 * @brief Sowftware PWM (slow)
 * @class swPWM sw_pwm.h "class/sw_pwm.h
 * @warning The swPWM will use the CTimer object resource to implement the PWM output.
 * @ingroup Peripherals
 */
class swPWM: public CTimer {
public:
	/**
	 * @brief swPWM constructor.
	 * @param t Specify a @ref TIMER_T for the Software PWM module
	 */
	swPWM(TIMER_T t);						// default sample level is 256

	/**
	 * @brief Set the period time of PWM.
	 * @param sec The period time of PWM, for example: 0.1=100ms, 0.02=20ms
	 * @warning The minimum period time is 2ms.
	 */
	void period(float sec);			// Remark: minimum 0.02 (20ms) / 50Hz

	/**
	 * @brief Enable the software PWM
	 */
	virtual void enable();

	/**
	 * @brief Disable the software PWM
	 */
	virtual void disable();

	/** @brief set duty-cycle output
	 * @param pin To connect the pin to the PWM pin.
	 * @param value To set the duty cycle of PWM pin, the duty cycle is a percentage value. (ex. 0.1=10%, 0.52=52%)
	 */
	virtual void dutyCycle(int pin, float percent);

	/** @brief set pulsewidth output in seconds.
	 *
	 */
	virtual void pulsewidth(int pin, float seconds);

	/**@brief RAW data output to PWM  pin
	 *
	 */
	virtual void output(int pin, uint16_t pulsewidth);

	/**
	 * @brief stop PWM on pin
	 */
	virtual void stop(int pin);

	/**
	 * @brief Get PWM channel count.
	 * @return Number of channel of PWM.
	 */
	inline int count() {
		return m_lstPin.count();
	}

	/**
	 * @brief Get current sample level.
	 */
	inline uint16_t sample_level() {
		return m_sample_level;
	}

	//
	///@cond PRIVATE
	//
	virtual ~swPWM();
	virtual void onTimer();
protected:
	ELEM_PTR find(int pin);

	CList	 m_lstPin;
	float	 m_period;
	uint16_t m_sample_level;
	uint16_t m_cycle;
	///@endcond
};

/**\example /peripherals/sw_pwm_firefly/src/main.cpp
 * This is an example of how to use the swPWM class.
 * More details about this example.
 */

#endif /* swPWM_H_ */
