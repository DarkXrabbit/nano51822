/*
 ===============================================================================
 Name        : gpio_int.h
 Author      : uCXpresso
 Version     : v1.0.1
 Date		 : 2015/5/16
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : GPIO Interrupt class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/5	v1.0.0	First Edition for nano51822						Jason
 2015/5/16	v1.0.1	Change the enable,disable and wait to 			Jason
 	 	 	 	 	static member functions.
 ===============================================================================
 */

#ifndef GPIO_SENSE_H_
#define GPIO_SENSE_H_

#include <class/pin.h>
#include <class/semaphore.h>

/**
 * @brief Interrupt sense Enumerations
 * @ingroup Enumerations
 */
typedef enum {
	RISING = 1,			///< Low to High
	FALLING = 2,		///< High to Low
	TOGGLE = 3			///< Toggle
}SENSE_T;

/**
 * @brief GPIO interrupt service
 * @class gpioSense gpio_sense.h "class/gpio_sense.h"
 *
 * @ingroup Peripherals
 */
class gpioSense: public CPin {
public:
	/**@brief construct for EDGE mode
	 * \param pin to specify a PIN_NAME_T for IRQ.
	 * @param sense to specify the @ref SENSE_T to trigger the interrupt.
	 * \param mode to set the PIN_INPUT_MODE_T.
	 */
	gpioSense(uint8_t pin, SENSE_T sense=FALLING, PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP);

	/**
	 * @brief Waiting for interrupt active
	 * @param timeout is a waiting timeout and unit in millisecond.
	 * @return true if the pin is triggered.
	 */
	virtual bool isActived();

	/**
	 * @brief check the sense pin enabled or not.
	 */
	virtual bool isValid();

	/**
	 * @brief Enable the GPIO interrupt
	 *
	 * @note When enable the gpioSense, the 16MHz clock will stay running,
	 * and this will cause >1mA extra current consumption.
	 */
	static void enable();

	/**
	 * @brief Disable the GPIO interrupt
	 */
	static void disable();

 	/**
	 * @brief Waitting for interrupt active for all pins.
	 * @param timeout is a waiting timeout and unit in millisecond.
	 * @return true if the pin is triggered.
	 */
	static bool wait(uint32_t timeout=MAX_DELAY_TIME);

	//
	///@cond PRIVATE
	//
	virtual ~gpioSense();
protected:
	uint8_t	m_sense;
	uint8_t m_mode;
	uint8_t m_laststate;
	/// @endcond
};

/**
 * @example /peripherals/gpio_sense/src/main.cpp
 * This is an example of how to use the CThread class.
 * More details about this example.
 */

#endif /* PININT_H_ */
