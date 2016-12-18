/*
 ===============================================================================
 Name        : wiegand.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月14日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月14日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef WIEGAND_H_
#define WIEGAND_H_

#include <class/pinpulse.h>

/**
 * @brief Wiegand Output
 */
class CWiegand {
public:
	/**@brief Construct
	 * @param D0 assign D0 pin
	 * @param D1 assign D1 pin
	 */
	void assign(int D0, int D1);

	/**@brief wiegand bit pulse-width
	 */
	void settings(float pulse, float interval);

	/**@brief output wiegand bits
	 * @param bits 			Wiegand raw data bits, order by LSB first
	 * @param bit_length 	Wiegand number of bit in bits
	 */
	void output(uint8_t *bits, uint8_t bit_length);

	/*! \cond PRIVATE */
	CWiegand(TIMER_T timer=TIMER_2);
	virtual ~CWiegand();
protected:
	CPin		m_D0;
	CPin		m_D1;
	CPinPulse	m_pulse;
	uint32_t	m_interval;
	/*! \endcond */
};

#endif /* WIEGAND_H_ */
