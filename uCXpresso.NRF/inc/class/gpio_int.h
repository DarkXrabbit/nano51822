/*
 ===============================================================================
 Name        : pinint.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Pin Interrupt class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/1	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef PININT_H_
#define PININT_H_

#include "class/object.h"
#include "class/semaphore.h"
#include "class/pin.h"

#define MAX_GPIO_INT	4

/**Interrupt Trigger Enumerations
 * \ingroup Enumerations
 */
typedef enum {
	RISING = 1,			///< Low to High
	FALLING = 2,		///< High to Low
	TOGGLE = 3			///< Toggle
}TRIGGER_T;

/**Pin interrupt service
 * \class gpioINT pinint.h "class/pinint.h"
 * \ingroup Peripherals
 */
class gpioINT: public CPin {
public:
	/**construct for EDGE mode
	 * \param pin to specify a PIN_NAME_T for IRQ.
	 * \param mode to set the PIN_INPUT_MODE_T.
	 */
	gpioINT(int pin, PIN_INPUT_MODE_T mode=NEITHER);

	/**enable the interrupt object
	 * @param sense to specify the EDGE_STATE_T to trigger the interrupt.
	 */
	virtual void enable(TRIGGER_T trigger);

	/**disable the interrupt object
	 */
	virtual void disable();

	/**Waiting for interrupt active
	 * \param tm is a waiting timeout and unit in millisecond.
	 * \return trun if an interrupt occurred.
	 */
	virtual bool wait(uint32_t tm=MAX_DELAY_TIME);

	/**Trigger by software
	 */
	virtual void release();

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
