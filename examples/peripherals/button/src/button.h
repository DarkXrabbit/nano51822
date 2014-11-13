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

#ifndef BUTTON_H_
#define BUTTON_H_

#include <class/pin.h>
#include <class/timeout.h>

enum BTN_ACTION_T {
	BTN_ACT_LOW = LOW,
	BTN_ACT_HIGH = HIGH
};

class CButton: public CPin {
public:
	CButton(uint8_t pin, BTN_ACTION_T action=BTN_ACT_LOW, PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP);

	virtual bool isPress();
protected:
	CTimeout 	m_tmBounce;
	PIN_LEVEL_T m_action;
	PIN_LEVEL_T m_lastState;
};

#endif /* BUTTON_H_ */
