/*
 ===============================================================================
 Name        : ble_service_customer.h
 Author      : uCXpresso
 Version     : v1.0.1
 Date		 : 2014/11/5
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE Customer Service base class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/12	v1.0.0	First Edition for nano51822						Jason
 2014/11/5	v1.0.1	Add characteristic_add member for customize.	Jason
 ===============================================================================
 */

#ifndef BLE_SERVICE_CUSTOMER_H_
#define BLE_SERVICE_CUSTOMER_H_

#include <class/ble/ble_device.h>
#include <class/ble/nrf51/ble_gatt.h>
#include <class/ble/nrf51/ble_gattc.h>
#include <class/ble/nrf51/ble_gatts.h>

/**@brief 	BLE customer services base class.
 * @class 	bleServiceCustomer ble_service_customer.h "class/ble/ble_service_customer.h"
 *
 * @details This class provides the customize service/characteristics s for customer's BLE service.
 *
 * @ingroup Bluetooth
 */
class bleServiceCustomer: public bleService {
public:
	bleServiceCustomer(bleDevice &ble);

	/**
	 * @brief Check the service available
	 */
	virtual bool isAvailable();

	/**
	 * @brief Add a service declaration to the local server ATT table.
	 *
	 * @param[in] base_uuid 	Pointer to the base of service @ref ble_uuid128_t UUID.
	 * @param[in] service_uuid  Pointer to service UUID.
	 *
	 * @note Secondary Services are only relevant in the context of the entity that references them, it is therefore forbidden to
	 *       add a secondary service declaration that is not referenced by another service later in the ATT table.
	 *
	 * @return @ref NRF_SUCCESS Successfully added a service declaration.
	 * @return @ref NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 * @return @ref NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied, Vendor Specific UUIDs need to be present in the table.
	 * @return @ref NRF_ERROR_FORBIDDEN Forbidden value supplied, certain UUIDs are reserved for the stack.
	 * @return @ref NRF_ERROR_NO_MEM Not enough memory to complete operation.
	 */
	virtual uint32_t service(const ble_uuid128_t *base_uuid, uint16_t service_uuid);

	/**
	 * @brief Add a characteristic declaration, a characteristic value declaration and optional characteristic descriptor declarations to the local server ATT table.
	 *
	 * @note It is currently only possible to add a characteristic to the last added service (i.e. only sequential addition is supported at this time).
	 *
	 * @note Several restrictions apply to the parameters, such as matching permissions between the user description descriptor and the writeable auxiliaries bits,
	 *       readable (no security) and writeable (selectable) CCCDs and SCCDs and valid presentation format values.
	 *
	 * @note If no metadata is provided for the optional descriptors, their permissions will be derived from the characteristic permissions.
	 *
	 * @param[in] p_char_md         Characteristic metadata.
	 * @param[in] p_attr_char_value Pointer to the attribute structure corresponding to the characteristic value.
	 * @param[out] p_handles        Pointer to the structure where the assigned handles will be stored.
	 *
	 * @return @ref NRF_SUCCESS Successfully added a characteristic.
	 * @return @ref NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 * @return @ref NRF_ERROR_INVALID_PARAM Invalid parameter(s) supplied, service handle, Vendor Specific UUIDs, lengths, and permissions need to adhere to the constraints.
	 * @return @ref NRF_ERROR_INVALID_STATE Invalid state to perform operation, a service context is required.
	 * @return @ref NRF_ERROR_FORBIDDEN Forbidden value supplied, certain UUIDs are reserved for the stack.
	 * @return @ref NRF_ERROR_NO_MEM Not enough memory to complete operation.
	 * @return @ref NRF_ERROR_DATA_SIZE Invalid data size(s) supplied, attribute lengths are restricted by @ref BLE_GATTS_ATTR_LENS_MAX.
	 */
	virtual uint32_t characteristic_add(uint16_t char_uuid,
										ble_gatts_char_md_t *p_char_md,
										ble_gatts_attr_t *p_attr_char_value,
										ble_gatts_char_handles_t *p_handles );

	virtual inline uint16_t uuid() {
		return m_service_uuid;
	}

	virtual inline uint8_t uuid_type() {
		return m_uuid_type;
	}


	virtual inline bool isValid() {
		return (m_last_err_code==NRF_SUCCESS ? true : false);
	}

	//
	///@cond PRIVATE
	//
	virtual ~bleServiceCustomer();

protected:
	uint16_t		m_conn_handle;
	ble_uuid128_t	m_p_base_uuid;
	uint16_t		m_service_uuid;
	uint8_t			m_uuid_type;
	uint16_t		m_service_handle;
	uint32_t		m_last_err_code;

	//
	// on ble event and event dispatch
	//
	virtual void on_ble_event(ble_evt_t * p_ble_evt);
	virtual void on_connected(ble_evt_t * p_ble_evt);
	virtual void on_disconnected(ble_evt_t * p_ble_evt);
	virtual void on_write(ble_evt_t * p_ble_evt);
	virtual void on_hvc(ble_evt_t * p_ble_evt);
	virtual void on_send(ble_evt_t * p_ble_evt);
	///@endcond
};

#endif /* BLE_SERVICE_CUSTOMER_H_ */
