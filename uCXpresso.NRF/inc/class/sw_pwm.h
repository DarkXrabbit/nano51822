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

/**CTimer class
 * \class swPWM sw_pwm.h "class/sw_pwm.h
 * \ingroup Peripherals
 */
class swPWM: public CThread {
public:
	/**
	 * @brief swPWM constructor.
	 * @param m_accuracy Set the sample level of PWM.
	 *
	 */
	swPWM(float m_accuracy=100);	// default m_accuracy (sample level) 100

	/**
	 * @brief Set the period time of PWM.
	 * @param sec The period time, for example: 0.1=100ms, 0.02=20ms
	 */
	void period(float sec);			// Remark: minimum 0.02 (20ms) / 50Hz

	/**
	 * @brief Start the software PWM
	 */
	virtual bool start();			// start PWM

	/**
	 * @brief Stop the software PWM
	 */
	void stop();

	/**
	 * @brief add a PWM channel
	 * @param pin To connect the pin to the PWM channel.
	 * @retval channel number.
	 */
	int  add_channel(int pin, float dutyCycle=0.0f);

	/**
	 * @brief update the channel duty-cycle of PWM.
	 *
	 * @prarm channel	Specified the PWM channel which created by "add_channel".
	 * @param dutyCycle Update he new duty cycle value.
	 *
	 * @return
	 * @retval	true	If update the duty cycle of channel successful.
	 */
	bool update(int channel, float dutyCycle);

	//
	///@cond PRIVATE
	//
	virtual ~swPWM();

protected:
	CTimer	 m_timer;
	CList	 m_lstCH;
	int		 m_cycle;
	float 	 m_accuracy;
	virtual void run();
	///@endcond
};

#endif /* swPWM_H_ */
