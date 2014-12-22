/*
 ===============================================================================
 Name        : timer.cpp
 Author      : USER
 Version     :
 Date		 : 2012/5/16
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : 

 History     :
 ===============================================================================
 */

#include <class/ostimer.h>

osTimer::osTimer(uint32_t period, timer_handle_t handle, xHandle param) {
	m_handle = handle;
	m_param = param;
	m_period = period;
}

osTimer::~osTimer() {
}

bool osTimer::start(LPCTSTR name, uint32_t stack) {
	return CThread::start(name, stack, PRI_MEDIUM);
}

void osTimer::reset() {
	m_timer.reset();
}

void osTimer::stop() {
	suspend();
}

bool osTimer::isActive() {
	if ( isAlive() && isSuspend()==false ) {
		return true;
	} else {
		return false;
	}
}

void osTimer::run() {
	while( isAlive() ) {
		m_timer.wait(m_period);
		if ( m_handle ) {
			 m_handle(this, m_param);
		} else {
			onTimer();
		}
		m_timer.reset();
	}
}
