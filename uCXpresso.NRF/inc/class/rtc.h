/*
 ===============================================================================
 Name        : watchdog
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/6
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Implement the system watchdog
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2012/10/6	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef RTC_H_
#define RTC_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

/**
 * @brief LF Clock source
 * @ingroup Enumerations
 */
typedef enum {
	LF_INTERNAL	= 0,	///< Internal 32KiHz RC oscillator.
	LF_EXTERNAL,		///< External 32KiHz crystal.
	LF_SYNTH			///< Internal 32KiHz synthesizer from HFCLK system clock.
}rtc_source_t;

/**
 * @brief A Real Time Clock provides the 1ms tick count
 * @class rtcMS rtc.h "class/rtc.h
 * @ingroup Peripherals
 */
class rtcMS: public CPeripheral {
public:
	/**
	 * @brief rtcMS constructor.
	 */
	rtcMS();

	/**
	 * @brief Optional. To enable the RTC timer interrupt.
	 * @param ms Milliseconds. disable timer interrupt if ms=0.
	 */
	void interval(uint16_t ms);

	/**
	 * @brief Enable RTC tick count.
	 */
	void enable();

	/**
	 * @brief Disable RTC tick count.
	 */
	void disable();

	/**
	 * @brief Reset RTC tick count.
	 */
	void reset();

	/**
	 * @brief Retrieve the tick count.
	 */
	uint32_t tick_count();


	/**
	 * @brief wait for timer interrupt event (set by interval).
	 *
	 * @param timeout To push the task to block state for waiting timer interrupt event within the timeout.
	 *
	 * @return
	 * @retval true if timer interrupt event come.
	 */
	bool wait(uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief Static function, to select the LF clock source.
	 * @param src The clock source @ref rtc_source_t.
	 */
	static void clockSource(rtc_source_t src=LF_INTERNAL);

	//
	/// @cond PRIVATE
	//
	virtual ~rtcMS();
	CSemaphore  m_semIrq;
	uint32_t 	m_tick;
protected:
	///@endcond
};

extern rtcMS *gpRTC;

/**\example /peripherals/rtc/src/main.cpp
 * This is an example of how to use the rtcMS class.
 * More details about this example.
 */

#endif /* RTC_H_ */
