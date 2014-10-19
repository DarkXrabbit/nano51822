/*
 ===============================================================================
 Name        : timer.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/6
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Timer class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2012/10/6	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

/**CTimer class
 * \class CTimer timer.h "class/timer.h
 * \ingroup Peripherals
 */
class CTimer: public CPeripheral {
public:

	/**CTimer constructor
	 */
	CTimer();


	/**Call the second to set the period time by second.
	 * \param sec is floating value to indicate the time period (unit: second).
	 * \note The timer can be defined in the range 4us to 200ms.
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

	//
	///@cond PRIVATE
	//
	virtual ~CTimer();
	virtual void onTimer() {}
	CSemaphore	m_semIrq;
	///@endcond
};

/**\example /peripherals/timer_rtc/src/main.cpp
 * This is an example of how to use the CTimer class.
 * More details about this example.
 */

#endif /* TIMER_H_ */
