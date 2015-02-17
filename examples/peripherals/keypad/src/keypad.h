/*
 ===============================================================================
 Name        : keypad.h
 Author      : uCXpresso
 Version     : 0.0.1
 Date		 : 2014/6/17
 Copyright   : Copyright (C) www.embeda.com.tw
 License	 : MIT
 Description :
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/6/17	v0.0.1	First Edition.									Arik
 ===============================================================================
 */

#ifndef CKEYPAD_H_
#define CKEYPAD_H_

#include <class/thread.h>
#include <class/timeout.h>
#include <class/bus.h>
#include <class/semaphore.h>

#define MAX_PIN_CODE	8

class CKeypad: public CThread {
public:
	CKeypad(CBus &rows, CBus &cols, const char *table);
	virtual ~CKeypad();

	virtual void enable();		// start to scan
	virtual void disable();		// stop
	//
	// wait for pincode string
	//
	LPCTSTR wait(uint8_t waitForLength=0, uint32_t timeout=0);

	void reset();
	bool isActive();
	bool isTimeout();

	//
	// Event
	//
	virtual void onKeyDown(char ch) {}
	virtual void onKeyUp() {}

protected:
	CSemaphore	m_keydown_event;

	CBus		*m_rows;
	CBus		*m_cols;

	int			m_numRows;
	int			m_numCols;
	uint32_t	m_colMask;

	int			m_key_code;

	const char	*m_p_table;

	uint8_t		m_index;
	char		m_result[MAX_PIN_CODE+1];
	int			m_waitForLength;

	CTimeout	m_tmInput;	// input timeout count

	//
	// thread override function
	//
	virtual void run();
};

extern CKeypad *gp_key;

#endif /* CKEYPAD_H_ */
