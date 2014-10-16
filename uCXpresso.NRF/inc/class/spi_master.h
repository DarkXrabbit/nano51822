/*
 ===============================================================================
 Name        : spi_master.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/16
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : SPI master class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/16	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

#include <class/peripheral.h>
#include <class/semaphore.h>

#define DEF_SPI_MASTER_PIN_MOSI		21
#define DEF_SPI_MASTER_PIN_MISO		22
#define DEF_SPI_MASTER_PIN_SSL		23
#define DEF_SPI_MASTER_PIN_SCK		24

/**
 * @brief Serial bit order
 *
 * @ingroup Enumerations
 */
typedef enum {
	MSB_FIRST = 0, 	///< Most significant bit transmitted out first.
	LSB_FIRST = 1		///< Least significant bit transmitted out first.
}BIT_ORDER_T;

/**
 * @brief SPI Data To Clock Phase Relationship
 *
 * @ingroup Enumerations
 */
typedef enum {
	SPI_MODE0 = 0,	///< Mode 0: CPOL=0 / CPHA=0
	SPI_MODE1,		///< Mode 1: CPOL=0 / CPHA=1
	SPI_MODE2,		///< Mode 2: CPOL=1 / CPHA=0
	SPI_MODE3		///< Mode 3: CPOL=1 / CPHA=1
}SPI_MODE_T;

/**
 * @brief SPI master frequency
 *
 * @ingroup Enumerations
 */
typedef enum {
	SPI_FREQ_125KHZ = 0x02000000UL,
	SPI_FREQ_250KHZ = 0x04000000UL,
	SPI_FREQ_500KHZ = 0x08000000UL,
	SPI_FREQ_1MHZ	= 0x10000000UL,
	SPI_FREQ_4MHZ	= 0x40000000UL,
	SPI_FREQ_8MHZ	= 0x80000000UL
}SPI_FREQ_T;


/**
 * @brief spiMaster class provides the Serial Peripheral Interface.
 *
 * @class spiMaster spi_master.h "class/spi_master.h"
 *
 * @ingroup Peripherals
 */
class spiMaster: public CPeripheral {
public:
	/**
	 * @brief spiMaster constructor
	 *
	 * @param mosi_pin	Specify the MOSI pin of SPI.
	 * @param miso_pin	Specify the MISO pin of SPI.
	 * @param ssl_pin	Specify the Slave selected pin.
	 * @param sck_pin	Specify the Clock pin of SPI.
	 */
	spiMaster(int mosi_pin = DEF_SPI_MASTER_PIN_MOSI,
			  int miso_pin = DEF_SPI_MASTER_PIN_MISO,
			  int ssl_pin  = DEF_SPI_MASTER_PIN_SSL,
			  int sck_pin  = DEF_SPI_MASTER_PIN_SCK );

	/**
	 * @brief Set the SPI Frequency
	 * @param freq	Set the frequency @ref SPI_FREQ_T of SPI.
	 */
	void frequency(SPI_FREQ_T freq);

	/**
	 * @brief Set the SPI Data To Clock Phase Relationship
	 * @param mode	Specify the mode @ref SPI_MODE_T of SPI.
	 */
	void mode(SPI_MODE_T mode);

	/**
	 * @brief Specify the bit order of SPI.
	 * @param order Specify the bit order @ref BIT_ORDER_T of SPI.
	 */
	void bitOrder(BIT_ORDER_T order);

	/**
	 * @brief Enable the SPI bus.
	 */
	uint32_t enable();

	/**
	 * @brief Disable the SPI bus.
	 */
	void disable();

	/**
	 * @brief Transmit and receive the data block on SPI bus.
	 *
	 * @param p_tx_buf	Point to the transmitted buffer
	 * @param tx_len	The transmitted buffer size
	 * @param p_rx_buf	Point to the received buffer.
	 * @param rx_len	The received buffer size.
	 *
	 * @return
	 * @retval NRF_SUCCESS	if transfer successful.
	 * @retval NRF_TIMEOUT	if transfer timeout.
	 */
	virtual uint32_t transfer(uint8_t *p_tx_buf, uint16_t tx_len, uint8_t *p_rx_buf, uint16_t rx_len, uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief Transmit and receive the data block on SPI interface.
	 *
	 * @param p_tx_buf	Point to the transmitted buffer
	 * @param p_rx_buf	Point to the received buffer.
	 * @param length	The transmitted and received buffer size.
	 *
	 * @return
	 * @retval NRF_SUCCESS	if transfer successful.
	 * @retval NRF_TIMEOUT	if transfer timeout.
	 */
	inline uint32_t transfer(uint8_t *p_tx_buf, uint8_t *p_rx_buf, uint16_t length) {
		return transfer(p_tx_buf, length, p_rx_buf, length);
	}

	//
	///@cond PRIVATE
	//
	virtual ~spiMaster();
	CSemaphore m_semCompleted;
protected:
	xHandle		m_p_config;
	///@endcond
};

#endif /* SPI_MASTER_H_ */
