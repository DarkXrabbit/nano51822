/*
 ===============================================================================
 Name        : CPinPulse.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月15日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月15日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef CPINPULSE_H_
#define CPINPULSE_H_

#include <class/pin.h>
#include <class/timer.h>

class CPinPulse: public CTimer {
public:
	CPinPulse(TIMER_T timer = TIMER_2);

	void width(float second);

	void toggle(uint8_t pin, PIN_LEVEL_T init, bool repeat = true);

	virtual ~CPinPulse();
	virtual void onTimer();
protected:
	uint8_t m_pin;
	bool    m_repeat;
};

#endif /* CPINPULSE_H_ */
