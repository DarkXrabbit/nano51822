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

#include "class/object.h"
#include "class/semaphore.h"
#include "class/pin.h"

#define MAX_GPIO_INT	4	///< Maximum number of interrupt source

/**Interrupt Trigger Enumerations
 * \ingroup Enumerations
 */
typedef enum {
	RISING = 1,			///< Low to High
	FALLING = 2,		///< High to Low
	TOGGLE = 3			///< Toggle
}TRIGGER_T;

/**@brief GPIO interrupt service
 * @class gpioINT gpio_int.h "class/gpio_int.h"
 * @ingroup Peripherals
 */
class gpioINT: public CPin {
public:
	/**@brief construct for EDGE mode
	 * \param pin to specify a PIN_NAME_T for IRQ.
	 * \param mode to set the PIN_INPUT_MODE_T.
	 */
	gpioINT(uint8_t pin, PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP);

	/**@brief Enable the GPIO interrupt
	 * @param sense to specify the EDGE_STATE_T to trigger the interrupt.
	 */
	virtual void enable(TRIGGER_T trigger);

	/**@brief Disable the GPIO interrupt
	 */
	virtual void disable();

	/**@brief Waiting for interrupt active
	 * \param tm is a waiting timeout and unit in millisecond.
	 * \return trun if an interrupt occurred.
	 */
	virtual bool wait(uint32_t tm=MAX_DELAY_TIME);

	/**@brief Trigger by software
	 */
	virtual void release();

	/**@brief Check interrupt valid
	 * @return true if the gpio interrupt is valid, false otherwise.
	 */
	inline bool isValid() {
		return (m_ch>=0 ? true : false);
	}

	//
	///@cond PRIVATE
	//
	virtual ~gpioINT();
	CSemaphore		 m_semIrq;
protected:
	int				 m_ch;
	/// @endcond
};

#endif /* PININT_H_ */
