/*
 ===============================================================================
 Name        : gpio_int.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2015/6/11
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : gpioINT class provides 4 interrupts service.
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/6/11	v1.0.0	First Edition.									Jason
 ===============================================================================
 */

#ifndef GPIO_INT_H_
#define GPIO_INT_H_

#include <class/gpio_sense.h>

#define MAX_FAST_INTERRUPT	4

/**
 * @brief Interrupt number Enumerations
 * @ingroup Enumerations
 */
typedef enum {
	INT0	= 0,
	INT1,
	INT2,
	INT3
}INT_T;

/**
 * @brief GPIO fast external interrupt service
 * @class gpioINT gpio_int.h "class/gpio_int.h"
 *
 * @ingroup Peripherals
 */
class gpioINT : public CPin {
	/**@brief interrupt handler type. */
	typedef void (*int_handle_t) (INT_T number);
public:
	/**@brief construct for EDGE mode
	 * \param number Indicate the interrupt number.
	 * \param handle Callback handle function for the interrupt.
	 * \param pin to specify a PIN_NAME_T for IRQ.
	 * @param sense to specify the @ref SENSE_T to trigger the interrupt.
	 * \param mode to set the @ref PIN_INPUT_MODE_T.
	 */
	gpioINT(INT_T number, int_handle_t handle, uint8_t pin, SENSE_T sense=FALLING, PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP);

	/**
	 * @brief Enable the interrupt.
	 */
	void enable();

	/**
	 * @brief Disable the interrupt.
	 */
	void disable();

	/**
	 * @brief Interrupt event, callback when m_handle is null.
	 */
	virtual void onEvent() { NOTHING }

	//
	///@cond PRIVATE
	//
	~gpioINT();
	int_handle_t	m_handle;
protected:
	INT_T			m_int;
	///@endcond
};

#endif /* CLASS_GPIO_INT_H_ */
