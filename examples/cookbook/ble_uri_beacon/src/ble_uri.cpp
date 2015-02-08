/*
 ===============================================================================
 Name        : ble_uri.cpp
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

#include <ble_uri.h>
#include <string.h>

#if 0
#include <debug.h>
#define DBG		dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif

bleServiceUriBeacon *gpUriBeacon = NULL;

// Beacon service UUID   0xb3 5d 00 00 ee d4 4d 59 8f 89 f6 57 3e de a9 67
const ble_uuid128_t URI_UUID_BASE = { 0x67, 0xa9, 0xde, 0x3e, 0x57, 0xf6, 0x89,
		0x8f, 0x59, 0x4d, 0xd4, 0xee, 0x00, 0x00, 0x5d, 0xb3 };

#define URI_UUID_BEACON_DATA_1_CHAR		0x7da7
#define URI_UUID_BEACON_DATA_2_CHAR		0x7da8
#define URI_UUID_BEACON_DATA_SIZE_CHAR	0x7da9

///< Magic byte used to recognise that flash has been written
#define MAGIC_FLASH_BYTE 				0x42

bleServiceUriBeacon::bleServiceUriBeacon(bleDevice &ble) :
		bleServiceCustomer(ble), 		// constructs the parent class
		m_flash(sizeof(m_adv_flash)) 	// constructs the member variable
{
	uint32_t err_code;

	gpUriBeacon = this;

	//
	// storage init
	//
	flash_db_t *p_flash_db = (flash_db_t *) m_flash.addr();
	if (p_flash_db->data.magic_byte != MAGIC_FLASH_BYTE) {
		// copy info from parameter definitions into persistent memory
		memset(m_adv_flash.data.adv_data, 0, APP_ADV_DATA_MAX_LEN);
		m_adv_flash.data.adv_data_len = 0;
		flash_adv_data();
	} else {
		// any further initializations read data from pesistent memory into clbeacon_info
		// copy data from persisten memory into parameter definitions
		memcpy(m_adv_flash.data.adv_data, p_flash_db->data.adv_data,
				APP_ADV_DATA_MAX_LEN);
		m_adv_flash.data.adv_data_len = p_flash_db->data.adv_data_len;
	}

	//
	// ble service init
	//
	err_code = service(&URI_UUID_BASE, URI_UUID_BEACON_SERVICE);
	ASSERT(err_code==NRF_SUCCESS, "add service failed:%02X\n", err_code);

	err_code = data_1_char_add();
	ASSERT(err_code==NRF_SUCCESS, "data_1_char_add failed:%02X\n", err_code);

	err_code = data_2_char_add();
	ASSERT(err_code==NRF_SUCCESS, "data_2_char_add failed:%02X\n", err_code);

	err_code = size_char_add();
	ASSERT(err_code==NRF_SUCCESS, "size_char_add failed:%02X\n", err_code);

	(void) err_code;
}

bleServiceUriBeacon::~bleServiceUriBeacon() {
	// TODO Auto-generated destructor stub
}

uint32_t bleServiceUriBeacon::data_1_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;
	char_md.char_props.write_wo_resp = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	if (m_adv_flash.data.adv_data_len > APP_ADV_DATA_1_LEN)
		attr_char_value.init_len = APP_ADV_DATA_1_LEN;
	else
		attr_char_value.init_len = m_adv_flash.data.adv_data_len;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = APP_ADV_DATA_1_LEN;
	attr_char_value.p_value = m_adv_flash.data.adv_data;

	return characteristic_add(URI_UUID_BEACON_DATA_1_CHAR, &char_md,
			&attr_char_value, &m_beacon_data_1_char_handles);
}

uint32_t bleServiceUriBeacon::data_2_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;
	char_md.char_props.write_wo_resp = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	if (m_adv_flash.data.adv_data_len > APP_ADV_DATA_1_LEN)
		attr_char_value.init_len = m_adv_flash.data.adv_data_len
				- APP_ADV_DATA_1_LEN;
	else
		attr_char_value.init_len = 0;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = APP_ADV_DATA_2_LEN;
	attr_char_value.p_value = &m_adv_flash.data.adv_data[APP_ADV_DATA_1_LEN];

	return characteristic_add(URI_UUID_BEACON_DATA_2_CHAR, &char_md,
			&attr_char_value, &m_beacon_data_2_char_handles);
}

uint32_t bleServiceUriBeacon::size_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write_wo_resp = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 1;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 1;
	attr_char_value.p_value = &m_adv_flash.data.adv_data_len;

	return characteristic_add(URI_UUID_BEACON_DATA_SIZE_CHAR, &char_md,
			&attr_char_value, &m_beacon_data_size_char_handles);

}

void bleServiceUriBeacon::on_disconnected(ble_evt_t * p_ble_evt) {
	bleServiceCustomer::on_disconnected(p_ble_evt);
	system_reset();
}

void bleServiceUriBeacon::on_write(ble_evt_t * p_ble_evt) {
	ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

	if ((p_evt_write->handle == m_beacon_data_1_char_handles.value_handle) 	&& (p_evt_write->len <= APP_ADV_DATA_1_LEN)) {

		memcpy(m_adv_flash.data.adv_data, p_evt_write->data, p_evt_write->len);
		m_adv_flash.data.adv_data_len = p_evt_write->len;

		update_adv_len();
		flash_adv_data();
	}

	if ((p_evt_write->handle == m_beacon_data_2_char_handles.value_handle)	&& (p_evt_write->len <= APP_ADV_DATA_2_LEN)) {
		memcpy(&m_adv_flash.data.adv_data[APP_ADV_DATA_1_LEN],	p_evt_write->data, p_evt_write->len);
		m_adv_flash.data.adv_data_len = APP_ADV_DATA_1_LEN + p_evt_write->len;

		update_adv_len();
		flash_adv_data();
	}
}

void bleServiceUriBeacon::update_adv_len() {
	uint8_t set_data_value = m_adv_flash.data.adv_data_len;
	gatts_value_set(m_beacon_data_size_char_handles, &set_data_value, 1);
}

void bleServiceUriBeacon::flash_adv_data() {
	m_adv_flash.data.magic_byte = MAGIC_FLASH_BYTE;
	m_flash.write(&m_adv_flash, sizeof(m_adv_flash));
}

uint8_t bleServiceUriBeacon::get_adv_data(uint8_t* app_adv_data) {
	 memcpy(app_adv_data, m_adv_flash.data.adv_data, m_adv_flash.data.adv_data_len);
	 return m_adv_flash.data.adv_data_len;
}
