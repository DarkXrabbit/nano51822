/*
 * rtc.h
 *
 *  Created on: 2014/9/26
 *      Author: Jason
 */

#ifndef RTC_H_
#define RTC_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

typedef enum {
	LF_INTERNAL	= 0,
	LF_EXTERNAL
}rtc_source_t;

#define MAX_RTC_COUNTER_VAL     0x00FFFFFF                                  /**< Maximum value of the RTC counter. */

class CRTC: public CPeripheral {
public:
	CRTC();

	void interval(float sec);
	void enable();
	void disable();
	bool wait(uint32_t timeout=MAX_DELAY_TIME);

	void	 clear();
	uint32_t count();

	static void clockSource(rtc_source_t type=LF_INTERNAL);

	//
	/// @cond PRIVATE
	//
	virtual ~CRTC();
	CSemaphore m_semIRQ;
protected:
	///@endcond
};

extern CRTC *gpRTC;

/**\example /peripherals/timer_rtc/src/main.cpp
 * This is an example of how to use the CRTC class.
 * More details about this example.
 */

#endif /* RTC_H_ */
