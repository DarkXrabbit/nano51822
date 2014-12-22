/*
 ===============================================================================
 Name        : button
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/14
 License   	 : MIT
 Description : Implement a button input with bounce detected.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/14	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#include <class/button.h>

CButton::CButton(uint8_t pin, BTN_ACTION_T action, PIN_INPUT_MODE_T mode, bool forWeakup) : CPin(pin)
{
	input(mode, forWeakup);
	m_action = (PIN_LEVEL_T) action;
	m_bounce_timeout = 10;
	m_lastState = read();
	m_tmBounce.reset();
}

BTN_EVENT_T CButton::isPressed() {

	BTN_EVENT_T status = BTN_NOTHING;
	PIN_LEVEL_T state = read();

	if ( state==m_action ) {

		// debounce with 10ms
		if ( m_lastState!=state && m_tmBounce.isExpired(m_bounce_timeout) ) {
			m_lastState = state;
			status = BTN_PRESSED;
		}

	} else {
		// reset bounce time tick.
		m_tmBounce.reset();
		if ( m_lastState!=state ) {
			status = BTN_RELEASED;
		}
		m_lastState = state;
	}
	return status;
}

