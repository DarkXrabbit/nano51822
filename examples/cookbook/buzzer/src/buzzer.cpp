/*
 * buzzer.cpp
 *
 *  Created on: Aug 13, 2014
 *      Author: LEO
 */

#include "buzzer.h"

#define BUZ_STEP_TIME 100
CBuzzer *gp_buzzer;

CBuzzer::CBuzzer(uint8_t pin, uint16_t freq, TIMER_T t) :
		m_pwm(t, pin),
		m_mail("Buzzer")
{
	m_pwm.frequency(freq);
	gp_buzzer = this;
}

bool CBuzzer::enable() {
	return CThread::start("Buzzer", 66, PRI_HIGH);
}

void CBuzzer::post(int count) {
	m_mail.post((MESSAGE_T)count, 0);
}

void CBuzzer::run() {
	m_pwm.enable();

	int	count;
	while( isAlive()) {
		count = (int) m_mail.wait();			// block and waiting for count
		while(count--) {
			m_pwm.dutycycle(PWM_CH_1, 0.5);		// turn on buzzer with 50% duty-cycle
			sleep(BUZ_STEP_TIME);
			m_pwm.dutycycle(PWM_CH_1, 0);		// turn off buzzer
			sleep(BUZ_STEP_TIME);
		}
	}
}
