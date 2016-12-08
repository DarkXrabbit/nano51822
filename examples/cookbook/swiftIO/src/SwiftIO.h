/*
 ===============================================================================
 Name        : bleSwiftIO.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月6日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月6日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef SWIFTIO_H_
#define SWIFTIO_H_

#include <class/stream.h>
#include <class/list.h>

//
// BLE 通訊封包
//
typedef struct swiftIO_packet {
	uint8_t head[2];
	uint8_t opcode;
	uint8_t length;		// data length without opcode byte
	uint8_t *data;
}swiftIO_packet_t;

typedef enum opcode_e {
	OP_DO_SET = 0,
	OP_DI_GET
}opcode_t;

//
//
//
class swiftIO: public CObject {
public:
	swiftIO(CStream &s);

	bool send(opcode_t code, uint8_t len, const void* value);
	swiftIO_packet_t* read();

	bool writeable();
	bool readable();

	bool isConnected();

	virtual ~swiftIO();
protected:
	CStream 			*m_stream;
	CList				m_list;
	swiftIO_packet_t 	*m_packet;
	uint8_t 			m_step;
	uint8_t 			m_index;
};

#endif /* SWIFTIO_H_ */