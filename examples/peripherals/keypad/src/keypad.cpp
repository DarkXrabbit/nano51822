/*
 ===============================================================================
 Name        : keypad.cpp
 Author      : Arik
 Version     : 0.0.1
 Date		 : 2014/7/16
 Copyright   : Copyright (C) www.embeda.com.tw
 License	 : MIT
 Description :
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/6/16	v0.0.1	First Edition.									Arik
 ===============================================================================
 */

#include "keypad.h"

CKeypad *gp_key;

#if 0
#include "debug.h"
#define DBG			dbg_printf
#define STACK_SIZE	128
#else
#define DBG(...)
#define STACK_SIZE	64
#endif

#define KEYPAD_FLAG_TIMEOUT_BIT	0
#define KEYPAD_INPUT_TIMEOUT	5000	// keypad input timeout in 5 seconds.

CKeypad::CKeypad(CBus &rows, CBus &cols, const char *table) {
	gp_key = this;

	m_rows = &rows;
	m_cols = &cols;

	m_rows->output();
	m_cols->input(INTERNAL_PULL_UP);	// active Low

	m_key_code = 0;
	m_keydown_event.binary();

	m_p_table = table;

	m_index = 0;
}

CKeypad::~CKeypad() {
	disable();
}

void CKeypad::enable() {
	if (isSuspend()) {
		resume();
	} else {
		start("keypad", STACK_SIZE);
	}
}

void CKeypad::disable() {
	suspend();
	m_index = 0;
}

void CKeypad::run() {
	CTimeout tmBounce;		// time count for scanning keypad
	uint8_t input, row, col;
	uint32_t colMask = bit(m_cols->count()) - 1;

	char ch;
	row = 0;
	m_index = 0;
	m_result[MAX_PIN_CODE] = 0x00;
	while (isAlive()) {	// check thread alive

		*m_rows = bitmask(row);							// scan a low bit to row
		input = (m_cols->read() & colMask);
		if (input != colMask) {
			m_tmInput.reset();							// reset input timeout time count
			if (tmBounce.isExpired(10)) {				// key bounce check (10ms)
				for (col = 0; col < m_cols->count(); col++) {
					if ( bit_chk(input, col) == 0) {	// keypad is active low
						//
						// key down
						//
						m_key_code = (row * m_cols->count()) + col;
						ch = m_p_table[m_key_code];

						onKeyDown(ch);	// Key Down Event

						switch(ch){
						case '*': 	// CANCEL
							m_index = 0;
							break;
						case '#':	// ENTER
							if ( m_index ) {
								m_result[m_index] = 0x00;
								m_keydown_event.release();
								m_index = 0;
								m_waitForLength = 0;
							}
							break;
						default:
							m_result[m_index++] = ch;
							m_result[m_index] = 0x00;
							if ( m_index>=MAX_PIN_CODE || (m_waitForLength>0 && m_index>=m_waitForLength) ) {
								m_keydown_event.release();
								m_index = 0;
								m_waitForLength = 0;
							}
							break;
						}

						DBG("index=%d ch=%c, tm=%d\n", m_index, ch, gp_cfg->m_vlock_config.input_timeout_sec);
					}
				}

				// wait key release
				while ((m_cols->read() & colMask) != colMask) {
					sleep(10);
				}
				onKeyUp();
			}
		} else {
			tmBounce.reset();
			row = (row + 1) < m_rows->count() ? row + 1 : 0;	// scan for next row

			// check input timeout
			if ( m_tmInput.isExpired(KEYPAD_INPUT_TIMEOUT) ) {
				m_tmInput.reset();
				m_index = 0;
				bit_set(m_flag, KEYPAD_FLAG_TIMEOUT_BIT);
			}
		}
	}
}

void CKeypad::reset() {
	m_index = 0;
//	m_keydown_event.release();
	m_tmInput.reset();
}

LPCTSTR CKeypad::wait(uint8_t waitForLength, uint32_t timeout) {
	m_waitForLength = waitForLength;
	if ( m_keydown_event.wait(timeout) ) {
		return m_result;
	}
	return NULL;
}

bool CKeypad::isActive() {
	if ( m_index || m_waitForLength>0) {
		return true;
	}
	return false;
}

bool CKeypad::isTimeout() {
	if ( bit_chk(m_flag, KEYPAD_FLAG_TIMEOUT_BIT) ) {
		bit_clr(m_flag, KEYPAD_FLAG_TIMEOUT_BIT);
		return true;
	}
	return false;
}
