/*
 ===============================================================================
 Name        : ble_uri.cpp
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

#include <ble_uri_v2.h>
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

// Beacon service UUID   ee 0c 20 80-87 86-40 ba-ab 96-99 b9 1a c9 81 d8
const ble_uuid128_t URI_UUID_BASE = { 0xd8, 0x81, 0xc9, 0x1a, 0xb9, 0x99, 0x96,	0xab, 0xba, 0x40, 0x86, 0x87, 0x80, 0x20, 0x0c, 0xee };

#define URI_UUID_LOCK_STATE_CHAR		0x2081
#define URI_UUID_LOCK_CHAR				0x2082
#define URI_UUID_UNLOCK_CHAR			0x2083
#define URI_UUID_URI_DATA_CHAR			0x2084
#define URI_UUID_URI_FLAGS_CHAR			0x2085
#define URI_UUID_ADV_TX_POWER_CHAR		0x2086
#define URI_UUID_TX_POWER_MODE_CHAR		0x2087
#define URI_UUID_BEACON_PERIOD_CHAR		0x2088
#define URI_UUID_RESET_CHAR				0x2089
#define URI_UUID_RESERVED_CHAR			0x2090

#define URI_RESULT_SUCCESS				0x00
#define URI_RESULT_WRITE_NOT_PERMITTED	0x03
#define URI_RESULT_INSUFFICIENT			0x08
#define URI_RESULT_INVALID_LENGTH		0x0D


#define DEF_URI_DOMAIN	"ucxpresso"

bleServiceUriBeacon::bleServiceUriBeacon(bleDevice &ble) :
		bleServiceCustomer(ble), 		// constructs the parent class
		m_flash(sizeof(m_beacon_db)) 	// constructs the member variable
{
	uint32_t err_code;

	gpUriBeacon = this;

	//
	// storage init
	//
	flash_db_t *p_flash_db = (flash_db_t *) m_flash.addr();
	if (p_flash_db->data.size != sizeof(beacon_cfg_v2_t)) {
		reset();	// reset to default
		flash_update();
	} else {
		// any further initializations read data from pesistent memory into clbeacon_info
		// copy data from persisten memory into parameter definitions
		memcpy(&m_beacon_db.data, &p_flash_db->data,	sizeof(m_beacon_db.data));
	}

	//
	// ble service init
	//
	err_code = service(&URI_UUID_BASE, URI_UUID_BEACON_SERVICE);
	ASSERT(err_code==NRF_SUCCESS, "add service failed:%02X\n", err_code);

	err_code = lock_state_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add lock_state char failed:%02X\n", err_code);

	err_code = lock_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add lock char failed:%02X\n", err_code);

	err_code = unlock_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add unlock char failed:%02X\n", err_code);

	err_code = uri_data_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add uri_data char failed:%02X\n", err_code);

	err_code = uri_flags_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add uri_flags char failed:%02X\n", err_code);

	err_code = adv_tx_power_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add adv_tx_power char failed:%02X\n", err_code);

	err_code = tx_power_mode_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add tx_power_mode char failed:%02X\n", err_code);

	err_code = beacon_period_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add beacon_period char failed:%02X\n", err_code);

	err_code = reset_char_add();
	ASSERT(err_code==NRF_SUCCESS, "add reset char failed:%02X\n", err_code);

	(void) err_code;
}

bleServiceUriBeacon::~bleServiceUriBeacon() {
	// TODO Auto-generated destructor stub
}

uint32_t bleServiceUriBeacon::lock_state_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
//	attr_md.vlen = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 1;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 1;
	attr_char_value.p_value = (uint8_t *)&m_beacon_db.data.lock_state;

	return characteristic_add(URI_UUID_LOCK_STATE_CHAR, &char_md,
			&attr_char_value, &m_lock_state_char_handles);

}

uint32_t bleServiceUriBeacon::lock_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 1;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = APP_LOCK_KEY_MAX_LEN;

	return characteristic_add(URI_UUID_LOCK_CHAR, &char_md,
			&attr_char_value, &m_lock_char_handles);
}

uint32_t bleServiceUriBeacon::unlock_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 1;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = APP_LOCK_KEY_MAX_LEN;

	return characteristic_add(URI_UUID_UNLOCK_CHAR, &char_md,
			&attr_char_value, &m_unlock_char_handles);
}

uint32_t bleServiceUriBeacon::uri_data_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = m_beacon_db.data.uri_data_len;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = APP_URI_DATA_MAX_LEN;
	attr_char_value.p_value = m_beacon_db.data.uri_data;

	return characteristic_add(URI_UUID_URI_DATA_CHAR, &char_md,
			&attr_char_value, &m_uri_data_char_handles);
}

uint32_t bleServiceUriBeacon::uri_flags_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = sizeof(uint8_t);
	attr_char_value.p_value = &m_beacon_db.data.uri_flags;

	return characteristic_add(URI_UUID_URI_FLAGS_CHAR, &char_md,
			&attr_char_value, &m_uri_flags_char_handles);
}

uint32_t bleServiceUriBeacon::adv_tx_power_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 4;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 4;
	attr_char_value.p_value = (uint8_t *) m_beacon_db.data.adv_tx_power_level;

	return characteristic_add(URI_UUID_ADV_TX_POWER_CHAR, &char_md,
			&attr_char_value, &m_adv_tx_power_char_handles);
}

uint32_t bleServiceUriBeacon::tx_power_mode_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 1;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 1;
	attr_char_value.p_value = (uint8_t *)&m_beacon_db.data.tx_power_mode;

	return characteristic_add(URI_UUID_TX_POWER_MODE_CHAR, &char_md,
			&attr_char_value, &m_tx_power_mode_char_handles);
}

uint32_t bleServiceUriBeacon::beacon_period_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read = 1;
	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 2;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 2;
	attr_char_value.p_value = (uint8_t *)&m_beacon_db.data.beacon_period;

	return characteristic_add(URI_UUID_BEACON_PERIOD_CHAR, &char_md,
			&attr_char_value, &m_beacon_period_char_handles);
}

uint32_t bleServiceUriBeacon::reset_char_add() {
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_t attr_char_value;
	ble_gatts_attr_md_t attr_md;

	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.write = 1;

	memset(&attr_md, 0, sizeof(attr_md));

	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

	attr_md.vloc = BLE_GATTS_VLOC_STACK;
	attr_md.vlen = 1;
	attr_md.wr_auth = 1;

	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len = 0;
	attr_char_value.init_offs = 0;
	attr_char_value.max_len = 1;

	return characteristic_add(URI_UUID_RESET_CHAR, &char_md,
			&attr_char_value, &m_reset_char_handles);
}

void bleServiceUriBeacon::on_disconnected(ble_evt_t * p_ble_evt) {
	bleServiceCustomer::on_disconnected(p_ble_evt);
	system_reset();
}

void bleServiceUriBeacon::on_rw_auth_request(ble_evt_t * p_ble_evt) {
	ble_gatts_evt_rw_authorize_request_t * p_authorize_request;
	p_authorize_request = &(p_ble_evt->evt.gatts_evt.params.authorize_request);
	bool bUpdate = false;

	if ( p_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE ) {
		ble_gatts_evt_write_t * p_evt_write = &p_authorize_request->request.write;
		ble_gatts_rw_authorize_reply_params_t write_authorize_reply;

		memset(&write_authorize_reply, 0, sizeof(ble_gatts_rw_authorize_reply_params_t));
		write_authorize_reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
		write_authorize_reply.params.write.gatt_status = URI_RESULT_SUCCESS;

		//
		// Unlock
		//
		if ( p_evt_write->handle==m_unlock_char_handles.value_handle ) {
			if ( p_evt_write->len == APP_LOCK_KEY_MAX_LEN) {
				if ( memcmp(m_beacon_db.data.key, p_evt_write->data, APP_LOCK_KEY_MAX_LEN)==0 ) {
					m_beacon_db.data.lock_state = BEACON_CFG_UNLOCK;
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INSUFFICIENT;
				}
			} else {
				write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
			}
		}

		if ( m_beacon_db.data.lock_state == BEACON_CFG_UNLOCK) {	// in unlock state
			//
			// Lock
			//
			if ( p_evt_write->handle==m_lock_char_handles.value_handle ) {
				if ( p_evt_write->len==APP_LOCK_KEY_MAX_LEN ) {
					m_beacon_db.data.lock_state = BEACON_CFG_LOCK;						// set lock state
					memcpy(m_beacon_db.data.key, p_evt_write->data, p_evt_write->len);	// update new key
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			} else

			//
			// URI Data
			//
			if ( p_evt_write->handle==m_uri_data_char_handles.value_handle ) {
				if ( p_evt_write->len<=APP_URI_DATA_MAX_LEN ) {
					memcpy(m_beacon_db.data.uri_data,  p_evt_write->data, p_evt_write->len);
					m_beacon_db.data.uri_data_len = p_evt_write->len;
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			} else

			//
			// URI Flags
			//
			if ( p_evt_write->handle==m_uri_flags_char_handles.value_handle ) {
				if ( p_evt_write->len==sizeof(m_beacon_db.data.uri_flags) ) {
					m_beacon_db.data.uri_flags = p_evt_write->data[0];
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			} else

			//
			// ADV. Tx Power Level
			//
			if ( p_evt_write->handle==m_adv_tx_power_char_handles.value_handle ) {
				if ( p_evt_write->len==sizeof(m_beacon_db.data.adv_tx_power_level) ) {
					memcpy(m_beacon_db.data.adv_tx_power_level, p_evt_write->data, 4);
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			} else

			//
			// TX Power Mode
			//
			if ( p_evt_write->handle==m_tx_power_mode_char_handles.value_handle ) {
				if ( p_evt_write->len==sizeof(uint8_t) ) {
					if ( p_evt_write->data[0]>=TX_POWER_MODE_LOWSET && p_evt_write->data[0]<=TX_POWER_MODE_HIGH) {
						m_beacon_db.data.tx_power_mode = (TX_POWER_MODE_T) p_evt_write->data[0];
						bUpdate = true;
					} else {
						write_authorize_reply.params.write.gatt_status = URI_RESULT_WRITE_NOT_PERMITTED;
					}
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			} else

			//
			// Beacon Period
			//
			if ( p_evt_write->handle==m_beacon_period_char_handles.value_handle ) {
				if ( p_evt_write->len==sizeof(m_beacon_db.data.beacon_period) ) {
					m_beacon_db.data.beacon_period = p_evt_write->data[0] + p_evt_write->data[1]*256;
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			} else

			//
			// Reset
			//
			if ( p_evt_write->handle==m_beacon_period_char_handles.value_handle ) {
				if ( p_evt_write->len==1 ) {
					reset();
					bUpdate = true;
				} else {
					write_authorize_reply.params.write.gatt_status = URI_RESULT_INVALID_LENGTH;
				}
			}

		} else { // in lock state
			write_authorize_reply.params.write.gatt_status = URI_RESULT_INSUFFICIENT;
		}

		gatts_rw_authorize_reply(&write_authorize_reply);

		if ( bUpdate ) flash_update();
	}
}

void bleServiceUriBeacon::flash_update() {
	m_beacon_db.data.size = sizeof(beacon_cfg_v2_t);
	m_flash.write(&m_beacon_db, sizeof(m_beacon_db));
}

void bleServiceUriBeacon::reset() {
	memset(&m_beacon_db.data, 0, sizeof(beacon_cfg_v2_t));

	m_beacon_db.data.uri_data[0] = 0x00;							// http://www.
	strcpy((char *)m_beacon_db.data.uri_data+1, DEF_URI_DOMAIN);	// default domain
	m_beacon_db.data.uri_data[strlen(DEF_URI_DOMAIN)+1] = 0x03; 	// .net/
	m_beacon_db.data.uri_data_len = strlen(DEF_URI_DOMAIN)+2;
	m_beacon_db.data.uri_flags = 0;

	m_beacon_db.data.adv_tx_power_level[0] = -38;
	m_beacon_db.data.adv_tx_power_level[1] = -28;
	m_beacon_db.data.adv_tx_power_level[2] = -22;
	m_beacon_db.data.adv_tx_power_level[3] = -19;

	m_beacon_db.data.tx_power_mode = TX_POWER_MODE_MEDIUM;
	m_beacon_db.data.beacon_period = 1000;

	memset(m_beacon_db.data.key, 0, APP_LOCK_KEY_MAX_LEN);
}
