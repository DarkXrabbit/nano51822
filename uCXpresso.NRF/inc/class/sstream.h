/*
 ===============================================================================
 Name        : SStream
 Author      : Jason
 Version     : v1.0.0
 Date		 : 2015/2/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Secure Stream
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/2/1	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef CLASS_SSTREAM_H_
#define CLASS_SSTREAM_H_

#include <class/stream.h>
#include <class/thread.h>
#include <class/aes.h>

/**
 * @brief A secure stream provides the 128bits AES encryption/descryption for the tx stream and rx stream.
 * @class SStream sstream.h "class/sstream.h"
 * @ingroup Peripherals
 */
class SStream: public CThread, public CStream {
public:
	/**
	 * @brief SStream constructor
	 * @param tx_key		Pointer to the 128bits key of the AES for the TX stream.
	 * @param rx_key		Pointer to the 128bits key of the AES for the RX stream.
	 * @param s				Pointer to the CStream object. (Ex. bleServiceUART or CSerial..)
	 * @param tx_fifo_size	Indicate the fifo size for TX buffer.
	 * @param rx_fifo_size	Indicate the fifo size for RX buffer.
	 */
	SStream(const uint8_t *tx_key, const uint8_t *rx_key,CStream &s, size_t tx_fifo_size=32, size_t rx_fifo_size=32);

	/**
	 * @brief Check the stream connection.
	 */
	virtual inline bool isConnected() {
		return m_stream->isConnected();
	}

	/**
	 * @brief Override the @ref CStream::wait member function.
	 */
	virtual bool wait(uint32_t timeout=MAX_DELAY_TIME);

	/**
	 * @brief Start the Secure Stream component.
	 */
	virtual bool start(int stack=132);

	//
	///@cond PRIVATE
	//
	virtual ~SStream();
	virtual void onSend(bool fromISR);
protected:
	CSemaphore 	m_semWaitForConnected;
	aesCFB		m_txCFB;
	aesCFB		m_rxCFB;
	CStream 	*m_stream;
	virtual void run();
	///@endcond
};

#endif /* CLASS_SSTREAM_H_ */
