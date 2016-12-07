/*
 ===============================================================================
 Name        : bleSwiftIO.cpp
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

#include <string.h>
#include <SwiftIO.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif



//
//
//
swiftIO::swiftIO(CStream &s) {
	m_stream = &s;
}

swiftIO::~swiftIO() {
}

bool swiftIO::send(opcode_t code, uint8_t length, const void* value) {
	swiftIO_packet_t packet;

	packet.data = new uint8_t[length];
	if ( packet.data != NULL ) {
		packet.head[0] = 0x02;
		packet.head[1] = 0x1B;
		packet.opcode  = code;
		packet.length	 = length;
		memcpy(packet.data, value, length);

		m_stream->write(&packet, length);
		delete packet.data;
		return true;
	}
	return false;
}

swiftIO_packet* swiftIO::read() {
	if ( m_list.count()>0 ) {
		return (swiftIO_packet_t *) m_list.removeHead();
	}
	return NULL;
}

bool swiftIO::writeable() {
	return m_stream->writeable();
}

bool swiftIO::readable() {
	return (m_list.count() > 0) ? true : false;
}

void swiftIO::runloop() {
	uint8_t step = 0;
	swiftIO_packet_t *packet;
	while (m_stream->readable()) {
		uint8_t ch = m_stream->read();
		switch(step) {
		case 0: // check head 0
			if ( ch == 0x02 ) step++;
			break;
		case 1:	// check head 1
			if ( ch == 0x1B ) {
				packet = new swiftIO_packet_t;
				step = (packet != NULL) ? step+1 : 0;
			}
			break;
		case 2: // check opcode
			packet->head[0] = 0x02;
			packet->head[1] = 0x1B;
			packet->opcode = ch;
			step++;
			break;
		case 3:	// check length
			packet->length = ch;
			if (packet->length > 0) {
				packet->data = new uint8_t[packet->length];
				step++;
			} else {
				delete packet;
				step = 0;
			}
			break;
		case 4:
			if ( m_stream->read(packet->data, packet->length) == packet->length ) {
				m_list.addTail(packet);
			} else {
				delete packet;
			}
			step = 0;
			break;
		}
	}
}
