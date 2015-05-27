/*
 ===============================================================================
 Name        : power.h
 Author      : Jason
 Version     : v1.0.2
 Date		 : 2015/4/24
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO for tickless feature.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/26	v1.0.0	First Edition									Leo
 2014/10/30 v1.0.0	Add tickless enable/disable member.				Jason
 2014/11/19 v1.0.1  Add weakup pin pull mode.						Jason
 2015/04/24	v1.0.2	Add reset_reason static member function.		Jason
 ===============================================================================
 */

#ifndef POWER_H_
#define POWER_H_

#include <class/peripheral.h>

#define RESET_REASON_BIT_RESET_PIN	0	///< Reset from pin-reset detected
#define RESET_REASON_BIT_WATCHDOG	1	///< Reset from watchdog detected
#define RESET_REASON_BIT_SYS_RESET	2	///< Reset from AIRCR.SYSRESETREQ detected
#define RESET_REASON_BIT_LOOKUP		3	///< Reset from CPU look-up detected
#define RESET_REASON_BIT_OFF		16	///< Reset due to weak up from system off mode when wakeup is triggered from DETECT signal from GPIO
#define RESET_REASON_BIT_LPCOMP		17	///< Reset due to wake up from system OFF mode when wakeup is triggered from ANADETECTED signal from LPCOMP
#define RESET_REASON_BIT_DIF		18	///< Reset due to wake up from system OFF mode when wakepu is triggered from entering into debug interface mode

/**
 * @brief CPowerSave stack class
 * @class CPowerSave power.h "class/power.h
 * @ingroup Peripherals
 */
class CPowerSave: public CPeripheral {
public:
	/**
	 * @brief Enable (or disable) the tickless technology.
	 *
	 * @param enable true to enable the tickless technology, false otherwise.
	 *
	 * @note The uCXpresso.NRF Tickless Technology stops the periodic main clock (Enter to Deep-Sleep mode)
	 * during idle periods (periods when there are no application tasks to be executed),
	 * then makes a correcting adjustment to the RTOS tick count value when the main clock is restarted.
	 *
	 * @warning The tickless feature have to use the external 32.768KHz crystal within 20ppm.
	 * @see bleDevice::Init()
	 */
	static void tickless(bool enable);

	/**
	 * @brief Enter system OFF.
	 * @warning It is necessary to declare a @ref gpioSense pin to weakup the system from the power off mode.
	 * @note After wakeup the chip will be reset, and the MCU will run from the main entry.
	 */
	static void system_off();

	/**
	 * @brief Selected devices have a Buck type DC/DC converter that steps down the supply voltage VDD.
	 * The resulting voltage is then used by an internal LDO that supplies the radio with power.
	 * @param enable true to use the internal DC/DC convertor, false otherwise.
	 */
	static void dcdc(bool enable);

	/**
	 * @brief Gets the reset reason register.
	 * @return  uint32_t  Contents of the NRF_POWER->RESETREAS register (bit wide).
	 */
	static uint32_t reset_reason();
};

/*
 * @example /rtos/tickless_test/src/setup.cpp
 * This is an example of how to use the CPowerSave::tickless(),
 * More details about this example.
 */

#endif /* POWER_H_ */
