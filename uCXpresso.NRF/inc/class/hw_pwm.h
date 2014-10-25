/*
 ===============================================================================
 Name        : Hardware PWM
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/24
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Use timer to implement the PWM
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2012/10/24	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef HW_PWM_H_
#define HW_PWM_H_

#include <class/timer.h>
#include <class/pin.h>

#define MAX_HW_PWM_PINS	3

/**
 * @brief PWM Channels
 * @ingroup Enumerations
 */
typedef enum {
	PWM_CH_1  = 1,		///< PWM Channel 1
	PWM_CH_2,			///< PWM Channel 2
	PWM_CH_3,			///< PWM Channel 3
}PWM_CH_T;

/**
 * @brief Use timer to implement the fast PWM
 * @ingroup Peripherals
 */
class hwPWM: public CTimer {
public:
	/**
	 * @brief hwPWM constructor.
	 *
	 * @param ch1_pin Set pin number to connect to the PWM Channel 1
	 * @param ch2_pin Set pin number to connect to the PWM Channel 2
	 * @param ch3_pin Set pin number to connect to the PWM Channel 3
	 *
	 */
	hwPWM(uint8_t ch1_pin, uint8_t ch2_pin=NONE, uint8_t ch3_pin=NONE);

	/**
	 * @brief Set the PWM period time.
	 * @param sec Set the period time in second, ex. 0.1=100ms, 0.0005=500us
	 * @warning To set the period time before to enable the timer and the all duty-cycle of channels setting.
	 */
	inline void period(float sec) {
		CTimer::second(sec);
	}

	/**
	 * @brief Set the PWM frequency.
	 * @param freq The PWM frequency.
	 * @note This inline function is call to the @ref period member function.
	 */
	inline void frequency(uint32_t freq) {
		period( (1.0f/freq) );
	}

	/**
	 * @brief Update channel duty-cycle
	 * @param ch To specify the PWM channel.
	 * @param percentage To set the duty-cycle in percentage (ex. 0.85=85%, 0.23=23%...)
	 * @warning To set the PWM's @ref period time before to update the duty-cycle of channel.
	 */
	void dutycycle(PWM_CH_T ch, float percentage);

	//
	///@cond
	//
	virtual ~hwPWM();
	virtual void onTimer();
protected:
	CPin  	 m_pins[MAX_HW_PWM_PINS];
	///@endcond
};

extern hwPWM *gp_PWM;

/**\example /peripherals/hw_pwm/src/main.cpp
 * This is an example of how to use the hwPWM class.
 * More details about this example.
 */


#endif /* HW_PWM_H_ */
