/*
 * watchdog.h
 *
 *  Created on: 2014/9/26
 *      Author: Jason
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

class CWatchdog: public CPeripheral {
public:
	CWatchdog();

	void timeout(float sec);

	void enable();
	void disable();
	bool wait(uint32_t timeout=MAX_DELAY_TIME);

	static void feed();

	//
	///@cond PRIVATE
	//
	virtual ~CWatchdog();
	CSemaphore m_semIRQ;
	///@endcond
};

/**\example /peripherals/watchdog/src/main.cpp
 * This is an example of how to use the CWatchdog class.
 * More details about this example.
 */

#endif /* WATCHDOG_H_ */
