/*
 ===============================================================================
 Name        : power.h
 Author      : Jason
 Version     : v1.0.0
 Date		 : 2014/10/26
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO for tickless feature.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/26	v1.0.0	First Edition								Leo
 ===============================================================================
 */

#ifndef POWER_H_
#define POWER_H_

#include <class/peripheral.h>

/**
 * @brief CPowerSave stack class
 * @class CPowerSave power.h "class/power.h
 * @ingroup Peripherals
 */
class CPowerSave: public CPeripheral {
public:

	/**
	 * @brief Enter system OFF.
	 * @param wakeup_pin A wakeup source pin, and weak-up with active low level.
	 * @note After wakeup the chip will be reset, and the MCU will run from the main entry.
	 */
	static void system_off(int wakeup_pin);
};

#endif /* POWER_H_ */
