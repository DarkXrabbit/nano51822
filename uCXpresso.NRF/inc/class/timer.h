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
 	 	 	 	 	Add TIMER_1 and TIMER_2.
 ===============================================================================
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

/**
 * @brief TIMER Source
 * @ingroup Enumerations
 */
typedef enum {
	TIMER_1,	///< Timer 1, a 16 bits time count
	TIMER_2		///< Timer 2, a 16 bits time count
}TIMER_T;

/**
 * @brief Tiemr class provides timer service
 * @class CTimer timer.h "class/timer.h
 * @ingroup Peripherals
 */
class CTimer: public CPeripheral {
public:

	/**
	 * @brief CTimer constructor
	 *
	 * @param t	Select TIMER_1 or TIMER_2 @ref TIMER_T.
	 * @param prescaler	A 4-bit prescaler to source clock frequency (Max. prescaler value = 9).
	 * default Scaler 6 = 4us （Max timer period= 4us x 65536 = ~240ms)
	 */
	CTimer(TIMER_T t, uint8_t prescaler=6);

	/**
	 * @brief Call the second to set the period time by second.
	 * @param sec is floating value to indicate the time period (unit: second).
	 * @note The timer can be defined in the range 4us to 200ms.
	 */
	virtual void second(float sec);

	/**
	 * @brief Call the millsecond to set the time period by millisecond.
	 * @param ms is uint32_t value to indicate the tie period (unit: millisecond).
	 */
	inline void millisecond(uint32_t ms) {
		second((float) (ms/1000.0f));
	}

	/**
	 * @brief Enable the timer.
	 * @warning To set the period time before to enable the timer !!
	 */
	virtual void enable();	// start

	/**
	 * @brief Disable the timer.
	 */
	virtual void disable();	// stop

	/**
	 * @brief Waiting for timer interrupt.
	 */
	virtual bool wait(uint32_t timeout=MAX_DELAY_TIME);

	//
	///@cond PRIVATE
	//
	virtual ~CTimer();
	virtual void onTimer();
protected:
	xHandle		m_handle;
	CSemaphore	m_semIrq;
	uint8_t		m_prescaler;
	double		m_period;
	///@endcond
};

/**\example /peripherals/timer/src/main.cpp
 * This is an example of how to use the CTimer class.
 * More details about this example.
 */

/**\example /peripherals/hw_pwm/src/main.cpp
 * This is an example of how to use the CTimer class.
 * More details about this example.
 */

#endif /* TIMER_H_ */
