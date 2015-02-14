/*
 ===============================================================================
 Name        : ble_uri_v2.h
 Author      : Jason
 Version     : v1.0.0
 Date		 : 2015/2/14
 Description : Uri Beacon Configure Service V2
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/2/14	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef BLE_URI_V2_H_
#define BLE_URI_V2_H_

#include <class/ble/ble_service_customer.h>
#include <class/storage.h>

#define URI_UUID_BEACON_SERVICE		0x2080

#define APP_LOCK_KEY_MAX_LEN		8
#define APP_URI_DATA_MAX_LEN		18

typedef enum {
	TX_POWER_MODE_LOWSET = 0,
	TX_POWER_MODE_LOW,
	TX_POWER_MODE_MEDIUM,
	TX_POWER_MODE_HIGH
}TX_POWER_MODE_T;

typedef enum {
	BEACON_CFG_UNLOCK = 0,
	BEACON_CFG_LOCK
}BEACON_LOCK_T;

// layout for persistent storage
typedef struct
{
	uint8_t  		size;                      // indicates new or onfigured tags
	BEACON_LOCK_T	lock_state;							// 1=lock, 0=unlock
	uint8_t  		lock[APP_LOCK_KEY_MAX_LEN];			// Lock Data
	uint8_t  		uri_data[APP_URI_DATA_MAX_LEN];  	//
	uint8_t  		uri_data_len;
	uint8_t  		uri_flags;
	int8_t   		adv_tx_power_level[4];
	TX_POWER_MODE_T	tx_power_mode;
	uint16_t 		beacon_period;
}beacon_cfg_v2_t;

// byte aligned for persisten storage
typedef union
{
  beacon_cfg_v2_t 	data;
  uint32_t 			padding[CEIL_DIV(sizeof(beacon_cfg_v2_t), 4)];
}flash_db_t;

class bleServiceUriBeacon: public bleServiceCustomer {
public:
	bleServiceUriBeacon(bleDevice &ble);

	inline beacon_cfg_v2_t& get() {
		return m_beacon_db.data;
	}

	void reset();

	void flash_update();

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceUriBeacon();
protected:
	ble_gatts_char_handles_t	m_lock_state_char_handles;
	ble_gatts_char_handles_t	m_lock_char_handles;
	ble_gatts_char_handles_t	m_unlock_char_handles;
	ble_gatts_char_handles_t	m_uri_data_char_handles;
	ble_gatts_char_handles_t	m_uri_flags_char_handles;
	ble_gatts_char_handles_t	m_adv_tx_power_char_handles;
	ble_gatts_char_handles_t	m_tx_power_mode_char_handles;
	ble_gatts_char_handles_t	m_beacon_period_char_handles;
	ble_gatts_char_handles_t	m_reset_char_handles;

	flash_db_t	m_beacon_db;
	CStorage	m_flash;

	uint32_t lock_state_char_add();
	uint32_t lock_char_add();
	uint32_t unlock_char_add();
	uint32_t uri_data_char_add();
	uint32_t uri_flags_char_add();
	uint32_t adv_tx_power_char_add();
	uint32_t tx_power_mode_char_add();
	uint32_t beacon_period_char_add();
	uint32_t reset_char_add();

	// Implement the virtual functions of bleServiceCustomer.
	virtual void on_disconnected(ble_evt_t * p_ble_evt);
	virtual void on_write(ble_evt_t * p_ble_evt);			// on write event
	///@endcond
};

extern bleServiceUriBeacon	*gpUriBeacon;

#endif /* BLE_URI_V2_H_ */
