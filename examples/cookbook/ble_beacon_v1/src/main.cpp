/*
===============================================================================
 Name        : iBeacon Demo V2
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright	 : www.ucxpresso.net
 License   	 : MIT
 Description : beacon test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/4	v1.0.0	First Edition for nano51822						Leo
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
#include <class/pin.h>
#include <class/timeout.h>
#include <class/power.h>

// TODO: insert other definitions and declarations here
#define APP_ADV_INTERVAL				 1000							///< the advertising interval in millisecond.
#define APP_ADV_DATA_LENGTH              0x15                           ///< Length of manufacturer specific data in the advertisement.
#define APP_DEVICE_TYPE                  0x02                           ///< 0x02 refers to Beacon.
#define APP_MEASURED_RSSI                ((uint8_t)-59)                 ///< The Beacon's measured RSSI at 1 meter distance in dBm.
//#define APP_COMPANY_IDENTIFIER           0x004C                         ///< Company identifier for Apple Inc. as per www.bluetooth.org.
#define APP_COMPANY_IDENTIFIER           0x0059                       ///< Company identifier for Nordic Semi. as per www.bluetooth.org.
#define USE_ADDR_FOR_MAJ_MIN_VALUES	 	 1								///< Use BLE address for Major and Minor value.

const ble_uuid128_t  NRF_BEACON_UUID = {
		0x01, 0x12, 0x23, 0x34,
		0x45, 0x56, 0x67, 0x78,
		0x89, 0x9a, 0xab, 0xbc,
		0xcd, 0xde, 0xef, 0xf0
};

struct _beacon_info_ {
	uint8_t 		device_type;
	uint8_t 		data_length;
	ble_uuid128_t 	uuid;
	uint16_t		major;
	uint16_t		minor;
	int8_t			meas_rssi;
}__attribute__ ((__packed__));
typedef struct _beacon_info_ BEACON_INFO_T;

/**
 * @brief Update BEACON information
 */
void beacon_info_update(BEACON_INFO_T *p_beacon_info, uint16_t major, uint16_t minor, int8_t meas_rssi) {

	p_beacon_info->device_type = APP_DEVICE_TYPE;

	// Manufacturer specific information. Specifies the length of the manufacturer specific data in this implementation.
	p_beacon_info->data_length = APP_ADV_DATA_LENGTH;

	// beacon 128bits UUID
	memcpy(&p_beacon_info->uuid, &NRF_BEACON_UUID, sizeof(ble_uuid128_t));

	// Major arbitrary value that can be used to distinguish between Beacons.
	major = ((major >> 8) & 0x0FF) | ((major<<8) & 0xFF00);	// MSB first
	p_beacon_info->major = major;

	// Minor arbitrary value that can be used to distinguish between Beacons.
	minor = ((minor >> 8) & 0x0FF) | ((minor<<8) & 0xFF00);	// MSB first
	p_beacon_info->minor = minor;

	// Manufacturer specific information. The Beacon's measured TX power in this implementation.
	p_beacon_info->meas_rssi = meas_rssi;
}

//
// Board LED define
//
//#define BOARD_PCA10001
#define BOARD_LILYPAD
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

	// GAP
//	ble.m_gap.settings("nanoBeacon");	// set ble device name
	ble.m_gap.tx_power(BLE_TX_0dBm);	// set TX radio power

	//
	// Add BLE DFU Service
	//
#ifndef DEBUG
	bleServiceDFU dfu(ble);
	dfu.enable();
#endif

	//
	// update beacon info
	//
	BEACON_INFO_T m_beacon_info;

#if USE_ADDR_FOR_MAJ_MIN_VALUES
	beacon_info_update(&m_beacon_info, bleDevice::address()[1], bleDevice::address()[0], APP_MEASURED_RSSI);
#else
	beacon_info_update(&m_beacon_info, 0x0102, 0x0304, APP_MEASURED_RSSI);
#endif

	//
	// Advertisement
	//
	ble.m_advertising.type(ADV_TYPE_ADV_NONCONN_IND);
	ble.m_advertising.name_type(BLE_ADVDATA_NO_NAME);	// set beacon name type (No Name)
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);
	ble.m_advertising.manuf_specific_data((uint8_t *)&m_beacon_info, sizeof(m_beacon_info)); // set beacon data
	ble.m_advertising.flag(BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED);		// set flags
	ble.m_advertising.update();							// update advertising data

	ble.m_advertising.interval(APP_ADV_INTERVAL);		// set advertising interval
	ble.m_advertising.start();

	//
	// LED pin declared
	//
	CPin led(LED_PIN_0);
	led.output();

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
    	// blink led
    	//
		led = LED_ON;
		sleep(10);		// turn on with a short time (10ms)
		led = LED_OFF;
    	sleep(2990);	// sleep with a long time (2990ms)
    }
}
