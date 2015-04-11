/*
 ===============================================================================
 Name        : gpio_int.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : GPIO Interrupt class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/5	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef PININT_H_
#define PININT_H_

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
	gpioSense(uint8_t pin, SENSE_T sense=FALLING, PIN_INPUT_MODE_T pull=INTERNAL_PULL_UP);

	/**
	 * @brief Enable the GPIO interrupt
	 *
	 * @note When enable the gpioSense, the 16MHz clock will stay running,
	 * and this will cause >1mA extra current consumption.
	 */
	virtual void enable();

	/**
	 * @brief Disable the GPIO interrupt
	 */
	virtual void disable();

	/**
	 * @brief Waiting for interrupt active
	 * @param timeout is a waiting timeout and unit in millisecond.
	 * @return true if the pin is triggered.
	 */
	virtual bool wait(uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief check the sense pin enabled or not.
	 */
	virtual bool isValid();

	//
	///@cond PRIVATE
	//
	virtual ~gpioSense();
protected:
	uint8_t	m_sense;
	uint8_t m_pull;
	/// @endcond
};

/**
 * @example /peripherals/gpio_sense/src/main.cpp
 * This is an example of how to use the CThread class.
 * More details about this example.
 */

#endif /* PININT_H_ */
