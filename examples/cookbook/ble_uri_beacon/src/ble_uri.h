/*
 ===============================================================================
 Name        : ble_uri.h
 Author      : Jason
 Version     : v1.0.0
 Date		 : 2015/2/7
 Description : Uri Beacon Service
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2015/2/7	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef BLE_URI_H_
#define BLE_URI_H_

#include <class/ble/ble_service_customer.h>
#include <class/storage.h>

#define URI_UUID_BEACON_SERVICE		0x7da6
#define APP_ADV_DATA_1_LEN			20
#define APP_ADV_DATA_2_LEN			8
#define APP_ADV_DATA_MAX_LEN		APP_ADV_DATA_1_LEN + APP_ADV_DATA_2_LEN

// layout for persistent storage
typedef struct
{
  uint8_t  magic_byte;                      // indicates new or onfigured tags
  uint8_t  adv_data[APP_ADV_DATA_MAX_LEN];  // adv data, not available for newly configured tags
  uint8_t  adv_data_len;                    // length of adv data, 0 on initial start up
}flash_db_layout_t;

// byte aligned for persisten storage
typedef union
{
  flash_db_layout_t data;
  uint32_t padding[CEIL_DIV(sizeof(flash_db_layout_t), 4)];
}flash_db_t;

class bleServiceUriBeacon: public bleServiceCustomer {
public:
	bleServiceUriBeacon(bleDevice &ble);

	uint8_t get_adv_data(uint8_t* app_adv_data);

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceUriBeacon();
protected:
	ble_gatts_char_handles_t	m_beacon_data_1_char_handles;
	ble_gatts_char_handles_t	m_beacon_data_2_char_handles;
	ble_gatts_char_handles_t	m_beacon_data_size_char_handles;

	flash_db_t	m_adv_flash;
	CStorage	m_flash;

	uint32_t data_1_char_add();
	uint32_t data_2_char_add();
	uint32_t size_char_add();

	void update_adv_len();
	void flash_adv_data();

	// Implement the virtual functions of bleServiceCustomer.
	virtual void on_disconnected(ble_evt_t * p_ble_evt);
	virtual void on_write(ble_evt_t * p_ble_evt);			// on write event
	///@endcond
};

extern bleServiceUriBeacon	*gpUriBeacon;

#endif /* BLE_URI_H_ */
