/*
 ===============================================================================
 Name        : rtc.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月20日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月20日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef _RTC_H_
#define _RTC_H_

#include <time.h>
#include <class/peripheral.h>

class CRtc {
public:
	/**
	 * @brief Initialize
	 */
	static void init();

	/*
	 * @brief Static Functions, synchronize the timeInterval since Jan. 1, 1970 UTC.
	 */
	static void sync(double timeInterval);

	/*
	 * @brief Static Functions, retrieve calibrate value.
	 * @param[in] Set the calibrate value
	 */
	static double calibrateValue();

	/**
	 * @brief Static Functions, get current time interval.
	 */
	static time_t now();

	static uint32_t debug();
};

#endif /* CLASS_RTC_H_ */
