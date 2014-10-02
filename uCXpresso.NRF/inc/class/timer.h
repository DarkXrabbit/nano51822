/*
 ===============================================================================
 Name        : timer.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/8/4
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Timer class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2012/8/4	v1.0.0	First Edition									Jason
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
	 * \note The timer can be defined between the 32us to the 2.09sec
	 */
	void second(float sec);

	/**Call the millsecond to set the time period by millisecond.
	 * \param ms is uint32_t value to indicate the tie period (unit: millisecond).
	 */
	inline void millisecond(uint32_t ms) {
		second((float) (ms/1000.0f));
	}

	/**Enable the timer.
	 */
	void enable();	// start

	/**Disable the timer.
	 */
	void disable();	// stop

	/**Waiting for timer interrupt.
	 */
	bool wait(uint32_t timeout=MAX_DELAY_TIME);


	/**Get current time count
	 *
	 */
	inline uint32_t count() {
		return m_count;
	}

	//
	// PRIVATE
	/// @cond

	// for arduino user
	inline void begin() { enable(); }
	inline void end() { disable(); }

	virtual ~CTimer();
	uint32_t 	m_count;
	CSemaphore	m_semIrq;
	/// @endcond
};

#endif /* TIMER_H_ */
