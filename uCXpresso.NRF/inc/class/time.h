/*
 ===============================================================================
 Name        : time.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月20日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Calendar
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月20日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef TIME_H_
#define TIME_H_

#include <time.h>	// standard time library
#include <class/object.h>

typedef struct tm	tm_t;

class CTime: public CObject {
public:
	CTime(time_t t);

	/**
	 * @brief Synchronize time interval
	 */
	void sync(time_t);

	/**
	 * @brief Set time zone with seconds.
	 */
	void timezone(int seconds);

	/**
	 * @brief Get local local time info.
	 */
	void localtime(tm_t& t);
protected:
	time_t	m_time;
	int		m_timezone;
};

#endif /* TIME_H_ */
