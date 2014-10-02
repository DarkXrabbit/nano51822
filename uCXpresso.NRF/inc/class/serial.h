/*
 ===============================================================================
 Name        : serial.h
 Author      : uCXpresso
 Version     : v1.0.2
 Date		 : 2014/3/18
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : serial stream class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/1/1	v1.0.0	First Edition for nano11Uxx						Jason
 2014/2/28	v1.0.1	Add parameter in onLineStatus() member.			Jason
 	 	 	 	 	Rename settings() to enable()
 	 	 	 	 	Add "pull up" function on TXD, RXD pins.
 2014/3/18	v1.0.2	Add semaphore for TX/RX fifo control.			Jason
 ===============================================================================
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <class/stream.h>
#include <class/pin.h>
#include <class/semaphore.h>


/**Use the CSerial class to transceiver the serial stream.
 * \class CSerial serial.h "class/serial.h"
 * \ingroup Peripherals
 */
class CSerial: public CStream {
public:
	/**
	 * @brief UART Parity type definitions
	 */
	typedef enum {
		UART_PARITY_NONE 	= false,			/*!< No parity */
		UART_PARITY_EVEN	= true, 			/*!< Even parity */
	} UART_PARITY_T;

	/**
	 * @brief UART Stop bit type definitions
	 */
	typedef enum {
	    UART_FLOW_CONTROL_DISABLED, /**< UART Hw Flow Control is disabled. */
	    UART_FLOW_CONTROL_ENABLED,  /**< Standard UART Hw Flow Control is enabled. */
	    UART_FLOW_CONTROL_LOW_POWER /**< Specialized UART Hw Flow Control is used. The Low Power setting allows the nRF51 to Power Off the UART module when CTS is in-active, and re-enabling the UART when the CTS signal becomes active. This allows the nRF51 to safe power by only using the UART module when it is needed by the remote site. */
	} UART_FLOW_CONTROL_T;

	/**
	 * @brief UART baud-rate
	 */
	typedef enum {
		UART_BAUDRATE_2400 		=	(0x0009D000UL), /*!< 2400 baud. */
		UART_BAUDRATE_4800 		=	(0x0013B000UL), /*!< 4800 baud. */
		UART_BAUDRATE_9600 		=	(0x00275000UL), /*!< 9600 baud. */
		UART_BAUDRATE_14400 	=	(0x003B0000UL), /*!< 14400 baud. */
		UART_BAUDRATE_19200 	=	(0x004EA000UL), /*!< 19200 baud. */
		UART_BAUDRATE_28800 	=	(0x0075F000UL), /*!< 28800 baud. */
		UART_BAUDRATE_38400 	=	(0x009D5000UL), /*!< 38400 baud. */
		UART_BAUDRATE_57600 	=	(0x00EBF000UL), /*!< 57600 baud. */
		UART_BAUDRATE_76800 	=	(0x013A9000UL), /*!< 76800 baud. */
		UART_BAUDRATE_115200	=	(0x01D7E000UL), /*!< 115200 baud. */
		UART_BAUDRATE_230400	=	(0x03AFB000UL), /*!< 230400 baud. */
		UART_BAUDRATE_250000	=	(0x04000000UL), /*!< 250000 baud. */
		UART_BAUDRATE_460800	=	(0x075F7000UL), /*!< 460800 baud. */
		UART_BAUDRATE_921600	=	(0x0EBEDFA4UL), /*!< 921600 baud. */
		UART_BAUDRATE_1M 		=	(0x10000000UL), /*!< 1M baud. */
	}UAET_BAUD_RATE_T;

public:
	/**Constructs a CSerial object.
	 * \param fifo_size
	 */
	CSerial(size_t tx_fifo_size = 64, size_t rx_fifo_size = 64);

	/**Call the member function to enable the serial port.
	 * \param baudrate is a unsigned long integer to specified the data baud-rate.
	 * \param parity is an UART_PARITY_T enumerations.
	 */
	virtual uint32_t enable(UAET_BAUD_RATE_T baudrate = UART_BAUDRATE_115200,
							UART_PARITY_T parity = UART_PARITY_NONE,
							UART_FLOW_CONTROL_T flow_control = UART_FLOW_CONTROL_DISABLED,
							int tx=9,
							int rx=11,
							int rts=8,
							int cts=10);

	virtual uint32_t disable();

	/**Call the member function to check that receive buffer is ready.
	 * \note The 'available' is an inline code to call the exist readable() member function.
	 */
	inline virtual int available() {
		return readable();
	}

	/**Call the member function to check that serial port is ready.
	 */
	virtual bool isConnected();

	virtual void flush();

	/*! \cond PRIVATE */
public:
	virtual ~CSerial();
	virtual void onSend(bool fromISR);
	virtual void onRecv(bool fromISR, uint8_t data);
private:
	uint16_t	m_handle;
	uint32_t 	m_flag;
	/*! \endcond */
};

//
// UART Line Status Define (bit position)
// for CSerial::onLineStatus()
// Refer to : Page 236 of UM10462
//
#define UART_LSR_RDR	(1<<0)		// Receiver Data Ready:
#define UART_LSR_OE		(1<<1)		// Overrun Error
#define UART_LSR_PE		(1<<2)		// Parity Error
#define UART_LSR_FE		(1<<3)		// Framing Error
#define UART_LSR_BI		(1<<4)		// Break Interrupt
#define UART_LSR_THRE	(1<<5)		// Transmitter Holding
#define UART_LSR_TEMT	(1<<6)		// Transmitter Empty
#define UART_LSR_RXFE	(1<<7)		// Error in RX FIFO
#define UART_LSR_TXERR	(1<<8)		// Tx Error

/**\example /peripheral/uart/src/main.cpp
 * This is an example of how to use the CSerial class.
 * More details about this example.
 */

#endif /* STREAM_H_ */
