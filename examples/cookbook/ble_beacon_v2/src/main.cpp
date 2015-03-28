/*
===============================================================================
 Name        : iBeacon Demo V2
 Author      : uCXpresso
 Version     : v1.0.0
 Description : Loads/Saves the beacon settings from/to Storage (flash memory)
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/22	v1.0.0	First Edition for nano51822						Leo
 ===============================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG dbg_printf
#else
#define DBG(...)
#endif

// TODO: insert other include files here
#include <class/ble/ble_device.h>
#include <class/ble/ble_service_dfu.h>
#include <class/ble/ble_service_uart.h>
#include <class/ble/ble_conn_params.h>
#include <class/pin.h>
#include <class/timeout.h>
#include <class/power.h>
#include <class/storage.h>
#include "at_command.h"

// TODO: insert other definitions and declarations here
#define APP_ADV_INTERVAL				 1000							///< the advertising interval in millisecond.
//#define APP_COMPANY_IDENTIFIER         0x004C                         ///< Company identifier for Apple Inc. as per www.bluetooth.org.
#define APP_COMPANY_IDENTIFIER           0x0059                       	///< Company identifier for Nordic Semi. as per www.bluetooth.org.
#define APP_ADV_DATA_LENGTH              0x15                           /**< Length of manufacturer specific data in the advertisement. */
#define APP_DEVICE_TYPE                  0x02                           /**< 0x02 refers to Beacon. */
#define APP_BEACON_INFO_LENGTH			 0x17

//
// Default UUID for nRF-Beacon
//
const static ble_uuid128_t DEF_BEACON_UUID = {
		0x01, 0x12, 0x23, 0x34,
		0x45, 0x56, 0x67, 0x78,
		0x89, 0x9a, 0xab, 0xbc,
		0xcd, 0xde, 0xef, 0xf0
};

void msb_value_set(uint8_t *field, uint16_t value) {
	field[0] = MSB(value);
	field[1] = LSB(value);
}

uint16_t msb_value_get(uint8_t *field) {
	return (field[0]<<8 | field[1]);
}

//
// Beacon Data & Configuration
//
typedef struct __attribute__ ((__packed__)) {
	uint8_t 		device_type;
	uint8_t 		data_length;
	ble_uuid128_t 	uuid;
	uint8_t			major[2];
	uint8_t			minor[2];
	int8_t			meas_rssi;
	int8_t			reserve;	// Importance, to keep the structure be a multiple of word size in the 32bits system!!
}BEACON_DAT_T;

typedef struct _beacon_cfg_ {
	uint32_t		size;			// size of the structure
	uint16_t		interval;
	uint16_t		company_id;
	BLE_TX_POWER_T	tx_power;
	BEACON_DAT_T	data;
}BEACON_CFG_T;

BEACON_CFG_T	m_beacon;

//
// global pointer to Beacon Data Storage
//
CStorage  *m_p_sgBeacon;

//
// Initialize the beacon configuration data
//
void beacon_data_init() {
	if ( m_beacon.size!=sizeof(m_beacon) ) {	// check beacon data valid
		m_beacon.interval 	= APP_ADV_INTERVAL;
		m_beacon.company_id = APP_COMPANY_IDENTIFIER;
		m_beacon.tx_power = BLE_TX_0dBm;	// 0 dBm
		m_beacon.data.device_type = APP_DEVICE_TYPE;
		m_beacon.data.data_length = APP_ADV_DATA_LENGTH;
		memcpy(m_beacon.data.uuid.uuid128, DEF_BEACON_UUID.uuid128, 16);
		msb_value_set(m_beacon.data.major, bleDevice::address()[1]);
		msb_value_set(m_beacon.data.minor, bleDevice::address()[0]);
		m_beacon.data.meas_rssi = -59;
		m_beacon.size = sizeof(m_beacon);		// update beacon data valid
		m_p_sgBeacon->write(&m_beacon, sizeof(m_beacon));
	}
}

//
// AT command list
//
static LPCTSTR const at_cmd_list[] {
	"&INTERVAL=",	///< 0,		AT&INTERVAL=xxxx
	"&INTERVAL?",	///< 1, 	AT&INTERVAL?
	"&TXPOWER=",	///< 2, 	AT&TXPOWER=xx
	"&TXPOWER?",	///< 3, 	AT&TXPOWER?
	"&COID=",		///< 4, 	AT&COID=xxxx
	"&COID?",		///< 5, 	AT&COID?
	"&MAJOR=",		///< 6, 	AT&MAJOR=xxxx
	"&MAJOR?",		///< 7, 	AT&MAJOR?
	"&MINOR=",		///< 8, 	AT&MINOR=xxxx
	"&MINOR?",		///< 9, 	AT&MINOR?
	"&RSSI=",		///< 10,	AT&RSSI=xxx
	"&RSSI?",		///< 11,	AT&RSSI?
	"+SAVE",		///< 12,	AT+SAVE
	"+RESET",		///< 13,	AT+RESET
	"+DFU",			///< 14,	AT+DFU
};

#define ATCMD_COUNT	(sizeof(at_cmd_list)/sizeof(LPCTSTR))

//
// AT command handle
//
void at_command_handle(CStream *p_serial, CString &str) {
	str.makeUpper();

	// finds command with command list. and return the index of the command list, if found.
	switch( str.find(at_cmd_list, ATCMD_COUNT) ) {
	case 0: // set interval in millisecond.
		m_beacon.interval = str.parseInt(10);
		str = "OK\n";
		break;

	case 1: // get interval
		str.printf("%dms\n", m_beacon.interval);
		break;

	case 2: // set tx power
		m_beacon.tx_power =(BLE_TX_POWER_T) str.parseInt(9);
		str = "OK\n";
		break;

	case 3: // get tx power
		str.printf("%ddBm\n", m_beacon.tx_power);
		break;

	case 4:	// set company id
		m_beacon.company_id = str.parseHex(6);
		str = "OK\n";
		break;

	case 5:	// get company id
		str.printf("0x%04X\n", m_beacon.company_id);
		break;

	case 6:	// set major value
		msb_value_set(m_beacon.data.major, str.parseInt(7));
		str = "OK\n";
		break;

	case 7: // get major value
		str.printf("%d\n", msb_value_get(m_beacon.data.major));
		break;

	case 8: // set minor value
		msb_value_set(m_beacon.data.minor, str.parseInt(7));
		str = "OK\n";
		break;

	case 9:	// get minor value
		str.printf("%d\n", msb_value_get(m_beacon.data.minor));
		break;

	case 10:// set measure rssi
		m_beacon.data.meas_rssi = str.parseInt(6);
		str = "OK\n";
		break;

	case 11:// get measure rssi
		str.printf("%d\n", m_beacon.data.meas_rssi);
		break;

	case 12:// save
		m_p_sgBeacon->write(&m_beacon, sizeof(m_beacon));
		str = "OK\n";
		break;

	case 13:// reset
		system_reset();
		break;

	case 14:// goto DFU
		gotoDFU();
		break;

	default:// command not found
		str = "ERROR\n";
		break;
	}

	// response to stream
	p_serial->write(str.getBuffer(), str.length());
}

//
// Board LED define
//
#ifdef DEBUG
#define BOARD_PCA10001
#else
#define BOARD_LILYPAD
#endif
#include <config/board.h>

int main(void)
{
#ifdef DEBUG
	CSerial ser;
	ser.enable();
	CDebug dbg(ser);
	dbg.start();
#endif
	//
	// SoftDevice Driver
	//
	bleDevice ble;
	ble.enable();						// enable BLE stack

	//
	// Load from Storage (Flash memory)
	//
	CStorage sgBeacon(sizeof(m_beacon));
	m_p_sgBeacon = &sgBeacon;

	// load beacon data from storage and initialize.
	sgBeacon.read(&m_beacon, sizeof(m_beacon));
	beacon_data_init();

	//
	// GAP
	//
	ble.m_gap.tx_power(m_beacon.tx_power);	// set TX radio power

	//
	// BLE to UART service
	//
	bleServiceUART nus(ble);

	//
	// Connection Parameters Update Negotiation
	//
	bleConnParams conn(ble);

	//
	// Advertisement
	//
//	ble.m_advertising.type(ADV_TYPE_ADV_NONCONN_IND);
	ble.m_advertising.name_type(BLE_ADVDATA_NO_NAME);	// set beacon name type (No Name)
	ble.m_advertising.commpany_identifier(m_beacon.company_id);
	ble.m_advertising.manuf_specific_data((uint8_t *)&m_beacon.data, APP_BEACON_INFO_LENGTH); // set beacon data
	ble.m_advertising.update(BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED);							// update advertising data

	ble.m_advertising.interval(m_beacon.interval);		// set advertising interval
	ble.m_advertising.start();

	//
	// LED pin declared
	//
	CPin led(LED_PIN_0);
	led.output();

	//
	// AT Command Parse
	//
	atCommand at(nus);					// set the nus stream to atCommand object.
	at.attachHandle(at_command_handle);	// set the AT command handle function.

	//
	// Enable Tickless Technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// AT Command parse
    	//
    	at.parse();

    	//
    	// blink led
    	//
		led = LED_ON;
		sleep(10);			// turn on with a short time (10ms)
		led = LED_OFF;
		if ( ble.isConnected() ) {
			sleep(190);
		} else {
			sleep(2990);	// sleep with a long time (2990ms)
		}

		// Negotiate "CP"
		conn.negotiate();
    }
}
