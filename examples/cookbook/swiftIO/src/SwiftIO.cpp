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

#if defined(DEBUG)
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
	m_step = 0;
}

swiftIO::~swiftIO() {
}

bool swiftIO::send(opcode_t code, uint8_t length, const void* value) {
	uint8_t *data = new uint8_t[length+4];
	if ( data != NULL ) {
		data[0] = 0x02;
		data[1] = 0x1B;
		data[2] = code;
		data[3]	= length;
		memcpy(data+4, value, length);
		m_stream->write(data, length+4);
		delete data;
		return true;
	}
	return false;
}

swiftIO_packet* swiftIO::read() {
	if ( m_list.count()>0 ) {
		return (swiftIO_packet_t *) m_list.removeTail();
	}
	return NULL;
}

bool swiftIO::writeable() {
	return m_stream->writeable();
}

bool swiftIO::readable() {
	return (m_list.count() > 0) ? true : false;
}

bool swiftIO::isConnected() {
	uint8_t i, len, ch, buf[20];
	if (m_stream->isConnected() ) {
		len = m_stream->read(buf, sizeof(buf), 0);
		i = 0;
		while( len>0 && i<len) {
			ch = buf[i++];
			switch(m_step) {
			case 0: // check head 0
				DBG("step%d:%02x\n", m_step, ch);
				if ( ch == 0x02 ) m_step++;
				break;
			case 1:	// check head 1
				DBG("step%d:%02x\n", m_step, ch);
				if ( ch == 0x1B ) {
					m_packet = new swiftIO_packet_t;
					m_step = (m_packet != NULL) ? m_step+1 : 0;
				}
				break;
			case 2: // check opcode
				DBG("step%d:%02x\n", m_step, ch);
				m_packet->head[0] = 0x02;
				m_packet->head[1] = 0x1B;
				m_packet->opcode = ch;
				m_step++;
				break;
			case 3:	// check length
				DBG("step%d:%02x\n", m_step, ch);
				m_packet->length = ch;
				if (m_packet->length > 0) {
					m_packet->data = new uint8_t[m_packet->length];
					m_step++;
					m_index = 0;
				} else {
					delete m_packet;
					m_step = 0;
				}
				break;
			case 4:
				DBG("step%d:%02x l=%d i=%d\n", m_step, ch, m_packet->length, m_index);
				m_packet->data[m_index++] = ch;
				if ( m_index >= m_packet->length ) {
					m_list.addHead(m_packet);
					m_step = 0;
				}
				break;
			}
		}
		return true;
	}
	return false;
}
