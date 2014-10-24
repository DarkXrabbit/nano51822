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

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

/**
 * @brief Watch-Dog static class
 * @class WDT watchdog.h "class/watchdog.h
 * @ingroup Peripherals
 */
class WDT: public CPeripheral {
public:
	/**
	 * @beief Set the timeout of watchdog, unit in second
	 */
	static void timeout(float sec);

	/**
	 * @brief Enable the watchdog
	 */
	static void enable();

	/**
	 * @brief Disable the watchdog
	 */
	static void disable();

	/**
	 * @brief Reload the time count to avoid the timeout of watchdog
	 */
	static void feed();

	/**
	 * @brief Indicates if the watchdog is running.
	 */
	static bool running();

};

/**\example /peripherals/watchdog/src/main.cpp
 * This is an example of how to use the WDT class.
 * More details about this example.
 */

#endif /* WATCHDOG_H_ */
