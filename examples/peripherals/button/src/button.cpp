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

#include <button.h>

CButton::CButton(uint8_t pin, BTN_ACTION_T action, PIN_INPUT_MODE_T mode) : CPin(pin)
{
	input(mode);
	m_action = (PIN_LEVEL_T) action;
	m_lastState = read();
	m_tmBounce.reset();
}

bool CButton::isPress() {
	// read current pin state
	PIN_LEVEL_T state = read();

	if ( state==m_action ) {

		// debounce with 10ms
		if ( m_lastState!=state && m_tmBounce.isExpired(10) ) {
			m_lastState = state;
			return true;
		}

	} else {
		// reset bounce time tick.
		m_tmBounce.reset();
		m_lastState = state;
	}
	return false;
}

