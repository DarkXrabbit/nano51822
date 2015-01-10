/*
 * buzzer.h
 *
 *  Created on: Aug 13, 2014
 *      Author: LEO
 */

#ifndef NRF51_VLOCK_BLE_SRC_BUZZER_H_
#define NRF51_VLOCK_BLE_SRC_BUZZER_H_

#include <class/thread.h>
#include <class/mailbox.h>
#include <class/timer.h>
#include <class/hw_pwm.h>

class CBuzzer: public CThread {
public:
	CBuzzer(uint8_t pin, uint16_t freq=2730, TIMER_T t=TIMER_1);
	bool enable();
	void post(int count);
protected:
	hwPWM m_pwm;
	CMailBox m_mail;
	virtual void run();
};

extern CBuzzer	*gp_buzzer;

#endif /* NRF51_VLOCK_BLE_SRC_BUZZER_H_ */
