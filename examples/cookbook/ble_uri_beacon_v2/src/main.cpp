/*
 ===============================================================================
 Name        : uri beacon
 Author      : uCXpresso
 Version     : v1.0.1
 Copyright   : www.ucxpresso.net
 License	 : Free
 Description : Implement Google URI Beacon V2
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/2/14	v1.0.0	First Edition.									Jason
 2015/3/30	v1.0.1	Update flash data on foreground task.			Jason
 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif

// TODO: insert other include files here
//#include <class/ble/ble_device_manager.h>
#include <class/ble/ble_device.h>
#include <class/ble/ble_service.h>
#include <class/ble/ble_conn_params.h>
#include <class/power.h>
#include <class/pin.h>

#include <ble_uri_v2.h>
#include <string.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                        	"URI Beacon CFG (V2)"  /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                  	"uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_COMPANY_IDENTIFIER          	0x0059                 /**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

#define APP_ADV_INTERVAL                  	1000                   /**< The advertising interval (in ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS      	30                     /**< The advertising timeout (in units of seconds). */


#define MIN_CONN_INTERVAL					500
#define MAX_CONN_INTERVAL					1000

#define APP_ADV_DATA_MAX_LEN				28
#define ADV_FLAGS_LEN                 		3
static uint8_t adv_flags[ADV_FLAGS_LEN] = {0x02, 0x01, 0x04};

// Normal: send configured ADV packet
// Config: enable GATT characteristic configuration
typedef enum {
	beacon_mode_config,
	beacon_mode_normal
} beacon_mode_t;

//
// Adv. Data
//
uint8_t adv_data_update(uint8_t *p_data) {

	if ( gpUriBeacon->get().uri_data_len<=APP_URI_DATA_MAX_LEN ) {
		p_data[0] = 0x03;	// AD Length
		p_data[1] = 0x03;	// Complete List of 16-Bit Service
		p_data[2] = 0xD8;	// URI Beacon ID (LOW)
		p_data[3] = 0xFE;	// URI Beacon ID (HIGH)

		p_data[4] = 0x05 + gpUriBeacon->get().uri_data_len;
		p_data[5] = 0x16;	// Service Data
		p_data[6] = 0xD8;	// Service ID (LOW)
		p_data[7] = 0xFE;	// Service ID (HIGH)
		p_data[8] = gpUriBeacon->get().uri_flags;
		p_data[9] = gpUriBeacon->get().adv_tx_power_level[gpUriBeacon->get().tx_power_mode];
		memcpy(p_data+10, gpUriBeacon->get().uri_data, gpUriBeacon->get().uri_data_len);

		return (gpUriBeacon->get().uri_data_len+10);
	}
	return 0;
}

/**@brief Function for initializing the Advertising functionality.
 *
 * @details Encodes the required advertising data and passes it to the stack.
 *          Also builds a structure to be passed to the stack when starting advertising.
 */
static void advertising_init(beacon_mode_t mode) {
	if (mode == beacon_mode_normal) {
		uint8_t adv_data[ADV_FLAGS_LEN+APP_ADV_DATA_MAX_LEN];
		uint8_t adv_data_len;

		memcpy(adv_data, adv_flags, ADV_FLAGS_LEN);
		adv_data_len = adv_data_update(adv_data+ADV_FLAGS_LEN);

		if ( adv_data_len > 0 ) {
			gpBLE->m_advertising.update(adv_data, adv_data_len + ADV_FLAGS_LEN, NULL, 0); // adv. raw data updated
			gpBLE->m_advertising.type(ADV_TYPE_ADV_NONCONN_IND);
			gpBLE->m_advertising.interval(gpUriBeacon->get().beacon_period);
			gpBLE->m_advertising.timeout(0); // never end
		}

		if ( gpUriBeacon->get().beacon_period>0 ) gpBLE->m_advertising.start();

	} else 	if (mode == beacon_mode_config) {
		ble_uuid_t adv_uuids[] = {{URI_UUID_BEACON_SERVICE, gpUriBeacon->uuid_type()}};
		ble_advdata_t advdata;
		ble_advdata_t scanrsp;
		uint8_t       flags = BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE;

	    memset(&advdata, 0, sizeof(advdata));
	    advdata.include_appearance      = true;
	    advdata.name_type				= BLE_ADVDATA_FULL_NAME;
	    advdata.flags.size              = sizeof(flags);
	    advdata.flags.p_data            = &flags;

	    memset(&scanrsp, 0, sizeof(scanrsp));
	    scanrsp.uuids_complete.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
	    scanrsp.uuids_complete.p_uuids  = adv_uuids;
		gpBLE->m_advertising.update(&advdata, &scanrsp);

		gpBLE->m_advertising.type(ADV_TYPE_ADV_IND);
		gpBLE->m_advertising.interval(APP_ADV_INTERVAL);
		gpBLE->m_advertising.timeout(APP_ADV_TIMEOUT_IN_SECONDS);

		gpBLE->m_advertising.start();
	}
}

beacon_mode_t beacon_mode = beacon_mode_normal;

//
// parse BLE events
//
void onBleEvent(bleDevice * p_ble, BLE_EVENT_T evt) {
	switch(evt) {
	case BLE_ON_CONNECTED:
		p_ble->onConnected();
		break;

	case BLE_ON_DISCONNECTED:
		p_ble->onDisconnected();
		beacon_mode = beacon_mode_normal;
		advertising_init(beacon_mode);
		break;

	case BLE_ON_TIMEOUT:
		system_reset();
		break;
	}
}

//
// Hardware
//
//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

//
// Main Routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif

	//
	// SoftDevice
	//
	bleDevice ble;
	ble.attachEvent(onBleEvent);
	ble.enable();	// enable BLE SoftDevice task

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP

	bleServiceUriBeacon beacon(ble);	// add uri beacon service

	switch ( beacon.get().tx_power_mode ) {
	case TX_POWER_MODE_LOWSET:
		ble.m_gap.tx_power(BLE_TX_m8dBm);
		break;
	case TX_POWER_MODE_LOW:
		ble.m_gap.tx_power(BLE_TX_m4dBm);
		break;
	case TX_POWER_MODE_MEDIUM:
		ble.m_gap.tx_power(BLE_TX_0dBm);
		break;
	case TX_POWER_MODE_HIGH:
		ble.m_gap.tx_power(BLE_TX_4dBm);
		break;
	}

	bleConnParams conn(ble);

	advertising_init(beacon_mode);

	//
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	//
	//
	CPin led0(LED_PIN_0);
	led0.output();

	CPin led1(LED_PIN_1);
	led1.output();

	CPin btn(BUTTON_PIN_0);
	btn.input();

	//
	// Enter main loop.
	//
	while (1) {
		//
		// check button
		//
		if ( btn==LOW ) {

			led1 = LED_ON;

			// stop advertising
			ble.m_advertising.stop();

			// change beacon mode
			if ( beacon_mode==beacon_mode_config ) {
				beacon_mode = beacon_mode_normal;
			} else {
				beacon_mode = beacon_mode_config;
			}

			// update mode and re-start the advertising
			advertising_init(beacon_mode);

			// waiting for btn released
			while(btn==LOW);

			led1 = LED_OFF;
		}

		//
		// LED Status
		//
		if ( beacon_mode==beacon_mode_config  ) {
			//
			// Negotiate the "connection parameters update" in main-loop
			//
			conn.negotiate();

			led0 = LED_ON;
			sleep(50);
			led0 = LED_OFF;
			sleep(150);

		} else {
			led0 = LED_ON;
			sleep(5);
			led0 = LED_OFF;
			sleep(beacon.get().beacon_period-5);
		}
	}
}
