/*
 ===============================================================================
 Name        : Analog Convert Module
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/18
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : analog convert class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef ADC_H_
#define ADC_H_

#include <class/peripheral.h>

/**
 * @brief Analog reference source.
 * @ingroup Enumerations
 */
typedef enum {
	AREF_VBG = 0,			///< Use internal 1.2V band gap reference.
	AREF_1					///< Use AREF1 (P0.6) as analog reference input.
}AREF_T;

/**
 * @brief Analog input selection
 * @ingroup Enumerations
 */
typedef enum {
	AIN 	= 0,			///< External analog input with no prescaling used as input for the conversion.
	AIN_2_3 = 1,			///< External analog input with 2/3 prescaling used as input for the conversion.
	AIN_1_3 = 2,			///< External analog with 1/3 prescaling used as input for the conversion.
	VDD_2_3 = 5,			///< Internal supply voltage with 2/3 prescaling used as input for the conversion.
	VDD_1_3 = 6				///< Internal supply voltage with 1/3 prescaling used as input for the conversion.
}ADC_SOURCE_T;

/**
 * @brief External analog input.
 * @ingroup Enumerations
 */
typedef enum {
	AD0	= 4,			///< Use AD0 input on P0.1
	AD1	= 8,			///< Use AD1 input on P0.2
	AD2	= 16,			///< Use AD2 input on P0.3
	AD3	= 32,			///< Use AD3 input on P0.4
	AD4	= 64,			///< Use AD4 input on P0.5
	AD5	= 128,			///< Use AD5 input on P0.6
	AD_NONE= 0
}AIN_T;

// int pin to analog pin
const AIN_T analog_pin[] = {AD_NONE, AD0, AD1, AD2, AD3, AD4, AD5};

/**
 * @brief Analog resolution.
 * @ingroup Enumerations
 */
typedef enum {
	ADC_8_BITS = 0,			///< 8 bits
	ADC_9_BITS = 1,			///< 9 bits
	ADC_10_BITS = 2			///< 10 bits
}ADC_RESOLUTION_T;

/**
 * @brief Analog Converter module class
 * @class CAdc adc.h "class/adc.h"
 * @note The CAdc is a static class.
 * @ingroup Peripherals
 */
class CAdc: public CPeripheral {
public:

	/**
	 * @brief Set ADC module to default.
	 * @note The init member use the internal 1.2V bandgap voltge as reference for conversion with
	 * 1/3 prescaling analog input, so the inputcan be in the 3.6V (1.2Vx3) max.
	 */
	static inline void init() {
		CAdc::reset();					// disable & reset the all configuration of analog.
		CAdc::reference(AREF_VBG);		// Use internal 1.2V bandgap voltage as reference for conversion.
		CAdc::source(AIN_1_3);			// External analog input with 1/3 prescaling used as input for the conversion.
	}

	/**
	 * @brief Analog input selection.
	 * @param input	To select the analog input. @ref ADC_INPUT_T
	 */
	static void source(ADC_SOURCE_T input);

	/**
	 * @brief Analog reference source.
	 * @param ref The analog reference source. @ref AREF_T.
	 *
	 * @note The AREF_1 will use the P0.6 (ADC5) for the analog reference source.
	 */
	static void reference(AREF_T ref);

	/**
	 * @brief Enable the analog module.
	 * @param res The analog resolutions. @ref ADC_RESOLUTION_T
	 */
	static void enable(ADC_RESOLUTION_T res=ADC_10_BITS);

	/**
	 * @brief Disable the analog module.
	 */
	static void disable();

	/**
	 * @brief Specified an analog input pin when analog source are AINxx.
	 *
	 * @param pin An analog input pin on AD0~AD5. @ref AIN_T
	 *
	 * @see CAdc::source
	 */
	static void pin(AIN_T ain);

	/**
	 * @brief Read analog convert value.
	 *
	 * @param value 	The analog convert result.
	 *
	 * @return
	 * @retval true If analog convert completed within timeout.
	 */
	static bool read(uint16_t &value, uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief Inline function to read an analog value from an AIN (AD0~AD5) pin.
	 *
	 * @param pin 	An AIN (AD0~AD5) pin.
	 * @param value	Result analog value.
	 *
	 * @return
	 * @retval true If analog convert completed within timeout.
	 */
	inline static bool read(AIN_T ain, uint16_t &value, uint32_t timeout=MAX_DELAY_TIME) {
		CAdc::pin(ain);
		return CAdc::read(value, timeout);
	}

	/**
	 * @brief Check analog module busy
	 * @return
	 * @retval true If analog conversion in progress.
	 */
	static bool isBusy();

	/**
	 * @brief Reset the analog module and all configurations.
	 */
	static void reset();

};

/**\example /peripherals/adc_test/src/main.cpp
 * This is an example of how to use the CAdc class.
 * More details about this example.
 */

#endif /* ADC_H_ */
