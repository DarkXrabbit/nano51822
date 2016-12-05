/*
 ===============================================================================
 Name        : SStream
 Author      : Jason
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Secure Stream (AES 128 CFB)
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/2/1	v1.0.0	First Edition									Jason
 2015/3/11	v1.0.1	Add event handle.								Jason
 2016/12/2  v1.1.0	Improve performance 							Jason
 ===============================================================================
 */

#ifndef CLASS_SSTREAM_H_
#define CLASS_SSTREAM_H_

#include <class/stream.h>
#include <class/thread.h>
#include <class/aes.h>

/**
 * @brief SStream events
 * @ingroup Enumerations
*/
typedef enum {
	SS_TIMEOUT,			///< IV block timeout
	SS_CONNECTED,		///< SStream ready for communication.
	SS_DISCONNECTED		///< SStream disconnected
}SS_EVENT_T;

/**
 * @brief A secure stream provides the 128bits AES encryption/descryption for the tx stream and rx stream.
 * @class SStream sstream.h "class/sstream.h"
 * @ingroup Peripherals
 */
class SStream:public CStream {
public:
	/**
	 * @brief SStream constructor
	 * @param tx_key		Pointer to the 128bits key of the AES for the TX stream.
	 * @param rx_key		Pointer to the 128bits key of the AES for the RX stream.
	 * @param s				Pointer to the CStream object. (Ex. bleServiceUART or CSerial..)
	 * @param tx_fifo_size	Indicate the fifo size for TX buffer.
	 * @param rx_fifo_size	Indicate the fifo size for RX buffer.
	 */
	SStream(const uint8_t *tx_key, const uint8_t *rx_key,CStream &s);

	/**
	 * @brief Check the stream connection.
	 */

	// Need to run in Main-Loop
	virtual bool isConnected();

	virtual int	 readable();

	virtual int	 writeable();

	virtual int  read(void *plaintext, int len, uint32_t block=MAX_DELAY_TIME);

	virtual int  write(const void *plaintext, int len, uint32_t block=MAX_DELAY_TIME);

	virtual void flush();
	//
	///@cond PRIVATE
	//
	virtual ~SStream();
	virtual void onSend(bool fromISR);
	virtual bool isTxBusy();
protected:
	aesCFB		m_txCFB;
	aesCFB		m_rxCFB;
	CStream 	*m_stream;
	uint8_t		m_flag;
	///@endcond
};

#endif /* CLASS_SSTREAM_H_ */
