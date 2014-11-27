/*
 ===============================================================================
 Name        : ble_service_hid.h
 Author      : Jason
 Version     : v1.0.0
 Date		 : 2014/11/24
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE human interface device services.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/24	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef CLASS_BLE_BLE_SERVICE_HID_H_
#define CLASS_BLE_BLE_SERVICE_HID_H_

#include <class/ble/ble_device.h>
#include <class/ble/nrf51/ble_hids.h>
#include <class/pin.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// BLE HID Service Base
//

/**
 * @brief BLE human interface device service base class.
 *
 * @class bleServiceHID ble_service_hid.h "class/ble/ble_service_hid.h"
 *
 * @ingroup Bluetooth
 */
class bleServiceHID: public bleService {
public:
	bleServiceHID(bleDevice &ble);

	/** @brief Check the service available.
	 * @return true if service is available, false otherwise.
	 */
	virtual bool isAvailable();


	/**@brief Get the UUID of service
	 * @return an uint16_t value.
	 */
	virtual inline uint16_t uuid() {
		return BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE;
	}

	//
	///@cond PRIVATE
	//
	virtual void on_hid_event(ble_hids_evt_t *p_evt) = PURE_VIRTUAL_FUNC;
protected:
	uint32_t	m_flag;
	ble_hids_t	m_hids;
	virtual void on_ble_event(ble_evt_t * p_ble_evt);
	///@endcond
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// BLE HID Keyboard Service
//

#define INPUT_REPORT_KEYS_MAX_LEN		8	/**< Maximum length of the Input Report characteristic. */
#define MAX_KEYS_IN_ONE_REPORT			6	/**< Maximum number of key presses that can be sent in one Input Report. */

/** @defgroup HID_MODIFIER_KEYS HID Keyboard modifier key bits
 * @{ */
#define MK_BIT_L_CTRL					0
#define MK_BIT_L_SHIFT					1
#define MK_BIT_L_ALT					2
#define MK_BIT_L_GUI					3
#define MK_BIT_R_CTRL					4
#define MK_BIT_R_SHIFT					5
#define MK_BIT_R_ALT					6
#define MK_BIT_R_GUI					7
/** @} */

/**
 * @brief HID Key Action.
 * @ingroup Enumerations
 */
enum KEY_ACTION_T {
	KEY_PRESSED,	///< key pressed
	KEY_RELEASED	///< key released
};

/** @defgroup HID_KB_LEDS HID Keyboard LEDs bits
 * @{ */
#define KB_LED_NUM_LOCK					0
#define KB_LED_CAPS_LOCK 				1
#define KB_LED_SCROLL_LOCK				2
#define KB_LED_COMPOSE					3
#define KB_LED_KANA						4
/** @} */

/**
 * @brief BLE human interface device class for keyboard service.
 *
 * @class bleServiceKB ble_service_hid.h "class/ble/ble_service_hid.h"
 *
 * @ingroup Bluetooth
 */
class bleServiceKB: public bleServiceHID {
	/**
	 * @brief keyboard LED handler type.
	 * @param p_hids	Pointer to the @ref bleServiceKB object
	 * @param leds		Indicate the @ref HID_KB_LEDS of KB. (bitwise)
	 * */
	typedef void (*hid_kb_leds_t) (bleServiceKB * p_hids, uint8_t leds);

public:
	/**
	 * @brief bleServiceKB constructor.
	 * @param[in] ble 			Pointer to bleDevice object.
	 * @param[in] report_desc	Pointer to HID report descriptor. If null, will use the internal default descriptor.
	 * @param[in] desc_length	Indicate the descriptor length.
	 */
	bleServiceKB(bleDevice &ble,
				 const uint8_t *report_desc = NULL,
				 uint16_t desc_length=0 );

	/**
	 * @brief Send the key pressed/released.
	 * @param[in] code			Key Scan Code.
	 * @param[in] action		Indicate the key action to @ref KEY_ACTION_T.
	 * @param[in] modifier_keys	Indicate the @ref HID_MODIFIER_KEYS. (bitwise)
	 *
	 * @return
	 * @retval NRF_SUCCESS				Send scan code successful.
	 * @retval NRF_ERROR_BUSY			Report buffer is full. (Max scan code report buffer = 6 bytes)
	 * @retval NRF_ERROR_INVALID_PARAM	Invalid action code.
	 */
	virtual uint32_t send(uint8_t code, KEY_ACTION_T action, uint8_t modifier_keys=0);

	/**
	 * @brief Attach the @ref hid_kb_leds_t handle
	 * @param[in] handle Pointer to the @ref hid_kb_leds_t function.
	 */
	inline void attach_kb_leds_handle(hid_kb_leds_t handle) {
		m_h_kb_leds = handle;
	}

	/**
	 * @brief Detach the kb leds handle
	 */
	inline void detach_kb_leds_handle() {
		m_h_kb_leds = NULL;
	}

	//
	///@cond PRIVATE
	//
protected:
	hid_kb_leds_t m_h_kb_leds;
	uint8_t m_key_report[INPUT_REPORT_KEYS_MAX_LEN];

	virtual uint32_t on_data_transmit();
	virtual void on_hid_event(ble_hids_evt_t *p_evt);
	virtual void on_hid_report_write(ble_hids_evt_t *p_evt);
	virtual void on_hid_notify_enabled(ble_hids_evt_t *p_evt);
	///@endcond
};

extern bleServiceHID *gpHID;
#define gpKB	((bleServiceKB *) gpHID)


#endif /* CLASS_BLE_BLE_SERVICE_HID_H_ */
