/*
 ===============================================================================
 Name        : timer.h
 Author      : uCXpresso
 Version     : v1.0.1
 Date		 : 2014/10/24
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Timer class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2012/10/6	v1.0.0	First Edition									Jason
 2014/10/24 v1.0.1	Add prescaler option in constructor.			Jason
 ===============================================================================
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

/**
 * @brief A 16 bits core timer class
 * @class CTimer timer.h "class/timer.h
 * @ingroup Peripherals
 */
class CTimer: public CPeripheral {
public:

	/**
	 * @brief CTimer constructor
	 *
	 * @param prescaler	A 4-bit prescaler to source clock frequency (max value 9).
	 * default Scaler 5 = 2us （Max timer period= 2us x 65536 = ~130ms)
	 *
	 * @note The timer frequency = 16MHz / (2^prescaler).
	 */
	CTimer(uint8_t prescaler=5);

	/**Call the second to set the period time by second.
	 * \param sec is floating value to indicate the time period (unit: second).
	 */
	virtual void second(float sec);

	/**Call the millsecond to set the time period by millisecond.
	 * \param ms is uint32_t value to indicate the tie period (unit: millisecond).
	 */
	inline void millisecond(uint32_t ms) {
		second((float) (ms/1000.0f));
	}

	/**Enable the timer.
	 */
	virtual void enable();	// start

	/**Disable the timer.
	 */
	virtual void disable();	// stop

	/**Waiting for timer interrupt.
	 */
	virtual bool wait(uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief On Timer IRQ Event.
	 * @warning The member function will be called by Timer IRQ.
	 */
	virtual void onTimer();

	//
	///@cond PRIVATE
	//
	virtual ~CTimer();
protected:
	CSemaphore	m_semIrq;
	uint8_t		m_prescaler;
	double		m_period;
	///@endcond
};

extern CTimer *gp_Timer;	///< Globel point to the timer object.

/**\example /peripherals/timer/src/main.cpp
 * This is an example of how to use the CTimer class.
 * More details about this example.
 */

#endif /* TIMER_H_ */
