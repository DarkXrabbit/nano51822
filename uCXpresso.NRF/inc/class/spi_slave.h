/*
 ===============================================================================
 Name        : spi_slave.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/16
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : SPI slave class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/16	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_

#include <class/peripheral.h>
#include <class/spi_master.h>
#include <class/semaphore.h>

#define DEF_SPI_SLAVE_PIN_MOSI		21
#define DEF_SPI_SLAVE_PIN_MISO		22
#define DEF_SPI_SLAVE_PIN_SSL		23
#define DEF_SPI_SLAVE_PIN_SCK		24

#define DEF_CHARACTER 0xAAu             /**< SPI default character. Character clocked out in case of an ignored transaction. */
#define ORC_CHARACTER 0x55u             /**< SPI over-read character. Character clocked out after an over-read of the transmit buffer. */

class spiSlave: public CPeripheral {
public:
	spiSlave(int mosi_pin = DEF_SPI_SLAVE_PIN_MOSI,
			 int miso_pin = DEF_SPI_SLAVE_PIN_MISO,
			 int ssl_pin  = DEF_SPI_SLAVE_PIN_SSL,
			 int sck_pin  = DEF_SPI_SLAVE_PIN_SCK);

	/**
	 * @brief SPI mode.
	 * @param mode Specify the SPI mode. @ref SPI_MODE_T.
	 */
	void mode(SPI_MODE_T mode);

	/**
	 * @brief SPI transaction bit order.
	 * @param order Specify the bit order @ref BIT_ORDER.
	 */
	void bitOrder(BIT_ORDER_T order);

	/**
	 * @brief Device configuration mode default character (DEF).
	 * @param def  Character clocked out in case of an ignored transaction.
	 */
	void def_tx_character(uint8_t def);

	/**
	 * @brief Device configuration mode over-read character.
	 * @param orc	Character clocked out after an over-read of the transmit buffer.
	 */
	void orc_tx_character(uint8_t orc);

	/**
	 * @brief Function for preparing the SPI slave device ready for a single SPI transaction.
	 *
	 * Function prepares the SPI slave device to be ready for a single SPI transaction. It configures
	 * the SPI slave device to use the memory, supplied with the function call, in SPI transactions.
	 *
	 * The @ref onTransactionCompleted will be called when either the memory buffer configuration or
	 * SPI transaction has been completed.
	 *
	 * @note The callback function @ref onTransactionCompleted can be called before returning from
	 * this function, since it is called from the SPI slave interrupt context.
	 *
	 * @note Client application must call this function after every transaction completed event if it
	 * wants the SPI slave driver to be ready for possible new SPI transaction.
	 *
	 * @param[in] p_tx_buf              Pointer to the TX buffer.
	 * @param[in] p_rx_buf              Pointer to the RX buffer.
	 * @param[in] tx_buf_len         	Length of the TX buffer in bytes.
	 * @param[in] rx_buf_len         	Length of the RX buffer in bytes.
	 *
	 * @retval NRF_SUCCESS              Operation success.
	 * @retval NRF_ERROR_NULL           Operation failure. NULL pointer supplied.
	 * @retval NRF_ERROR_INVALID_STATE  Operation failure. SPI slave device in incorrect state.
	 * @retval NRF_ERROR_INTERNAL       Operation failure. Internal error ocurred.
	 */
	virtual uint32_t transact(uint8_t *p_tx_buf, uint16_t tx_buf_len, uint8_t *p_rx_buf, uint16_t rx_buf_len);

	/**
	 * @brief Wait for a transaction completed event
	 *
	 * @node The wait member will block the task in waiting state which task call the 'wait' member.
	 *
	 * @param timeout	Set waiting time in millisecond.
	 *
	 * @retval true		if receive a trancation completed event within timeout.
	 * @retval false	if timeout.
	 */
	virtual bool wait(uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief Transaction Completed Event.
	 */
	virtual void onTransactionCompleted();

	//
	///@cond PRIVATE
	//
	virtual ~spiSlave();
	CSemaphore m_semTransaction;
protected:
	xHandle m_config;
	///@endcond
};

#endif /* SPI_SLAVE_H_ */
