/*
 ===============================================================================
 Name        : pin.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Pin (GPIO) class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/1	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef PIN_H_
#define PIN_H_

#include "class/peripheral.h"

/**When PIN as an input, the PIN_MODE control the input mode of all ports.
 * This includes the use of the on-chip pull-up/pull-down resistor feature
 * and a special open drain operating mode.
 * \ingroup Enumerations
*/
typedef enum {
	NEITHER	= 0,			///< Pin has neither pull-up nor pull-down resistor enabled
	INTERNAL_PULL_DOWN = 1,	///< Pin has an on-chip pull-down resistor enabled
	INTERNAL_PULL_UP = 3,	///< Pin has an on-chip pull-up resistor enabled
}PIN_INPUT_MODE_T;

/**Pin level defined
 * \ingroup Enumerations
 */
typedef enum {
	LOW = 0,		///< LOW level
	HIGH = 1,		///< HIGH level
	LED_OFF = LOW,	///< LED_OFF
	LED_ON = HIGH	///< LED_ON
}PIN_LEVEL_T;

/**Pin out drive mode
 * \ingroup Enumerations
 */
typedef enum {
	OUT_DRIVE_DISCONNECT,	///< 1 = Disconnect (floating)
	OUT_DRIVE_STANDARD,		///< 1 = 0.5mA drive output (Default)
	OUT_DRIVE_HIGH			///< 1 = 5mA drive output
}PIN_OUT_DRIVE_T;

/**Pin define class
 * 	\class CPin pin.h "class/pin.h"
 *	\ingroup Peripherals
 */
class CPin: public CPeripheral {
public:
	/**Constructs a CPin object to connect to the specified pin.
	 * \param p is a PIN_NAME_T enumeration to a pin of peripheral.
	 *
	 * \code
	 * Example:
	 * 		CPin key(21);		// Create a key object to connect to P0.21.
	 * 		key.input();		// set the key object as a input.
	 *
	 * 		if ( key==LOW ) {	// check the pin level
	 *			...
	 * 		}
	 * \endcode
	 */
	CPin(uint8_t p);

	/**
	 * @brief Set the pin as an output pin.
	 * @code
	 * CPin myPin(19);
	 * myPin.output();		// set the P0.19 as an output pin. (use the default NOT_OPEN and LOW level output)
	 * myPin = HIGH;		// set P0.19 to HIGH (use the operator '=')
	 * myPin.write(LOW);	// set P0.19 to LOW  (use the write() member)
	 * @endcode
	 * @param defValue is a PIN_LEVEL_T enumeration to set the default level for the output pin.
	 * @param mode is a PIN_OUT_MODE_T enumeration to indicate the output mode.
	 */
	virtual void output(PIN_LEVEL_T defValue=LOW, PIN_OUT_DRIVE_T mode=OUT_DRIVE_STANDARD);

	/**
	 * @brief Set as an input pin
	 * @code
	 * PIN_LEVEL_T level;
	 * CPin myPin(19);
	 * myPin.input(); 		// Set the P0.19 as an input pin. (with default INTERNAL_PULL_UP feature)
	 * if ( myPin==HIGH ) {	// Read a pin level from myPin. (use the operator '==')
	 * 		...
	 * }
	 * level = myPin;		// Read a pin level from myPin. (use the operator '=')
	 * level = myPin.read();// Read a pin level from myPin. (use the read() member)
	 * @endcode
	 * @param mode 		Indicate pin mode to @ref PIN_INPUT_MODE_T.
	 * @param forWeakup	Set the pin can weakup the system from power off mode.
	 */
	virtual void input(PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP, bool forWeakup=false);

	/**Write a Pin Level to the output pin.
	 * \param val is a PIN_LEVEL_T enumeration to write to the output pin.
	 * \see output
	 */
	virtual void write(PIN_LEVEL_T val);	// write new pin value (for output)

	/**Read a Pin Level from the input pin.
	 * \return PIN_LEVEL_T is HIGH (or LOW) enumeration.
	 * \see input
	 */
	virtual PIN_LEVEL_T  read();			// read current pin value (for input)

	/**Invert an output pin.
	 * \code
	 * CPin myPin(19);
	 * myPin.output();
	 *
	 * while(1) {
	 * 		myPin.invert();	// Invert the output pin level. (use the invert() member)
	 * //   myPin = !myPin; // Invert the output pin level. (use the '!' operator)
	 * 		sleep(100);
	 * }
	 * \endcode
	 */
	virtual void invert();					// invert current pin output value (for output)

	virtual inline bool isValid() {
		return (m_pin!=NONE ? true : false);
	}

	// Shorthand operators
	inline void operator =(PIN_LEVEL_T val) { this->write(val); }
	inline void operator =(CPin &pin) { this->write(pin.read());}
	inline operator PIN_LEVEL_T() { return read(); }
	inline PIN_LEVEL_T  operator !() { return (read()==HIGH? LOW : HIGH); }
	inline bool operator ==(PIN_LEVEL_T val) { return (this->read()==val ? true : false); }
	inline bool operator !=(PIN_LEVEL_T val) { return (this->read()!=val ? true : false); }
	inline int pin() { return m_pin; }
	inline void toggle() { invert(); }

	/*! \cond PRIVATE */
	CPin();
	virtual ~CPin();
	void assign(uint8_t pin);
protected:
	uint8_t m_pin;
	/*! \endcond */
};

#endif /* PIN_H_ */
