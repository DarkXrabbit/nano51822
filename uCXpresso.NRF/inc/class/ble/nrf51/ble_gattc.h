/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @addtogroup BLE_GATTC Generic Attribute Profile (GATT) Client
  @{
  @brief  Definitions and prototypes for the GATT Client interface.
 */

#ifndef _BLE_GATTC_H__
#define _BLE_GATTC_H__

#include "ble_gatt.h"
#include "ble_types.h"
#include "ble_ranges.h"

/** @addtogroup BLE_GATTC_ENUMERATIONS Enumerations
 * @{ */

/**@brief GATTC API SVC numbers. */
enum BLE_GATTC_SVCS
{
  SD_BLE_GATTC_PRIMARY_SERVICES_DISCOVER = BLE_GATTC_SVC_BASE, /**< Primary Service Discovery. */
  SD_BLE_GATTC_RELATIONSHIPS_DISCOVER,                         /**< Relationship Discovery. */
  SD_BLE_GATTC_CHARACTERISTICS_DISCOVER,                       /**< Characteristic Discovery. */
  SD_BLE_GATTC_DESCRIPTORS_DISCOVER,                           /**< Characteristic Descriptor Discovery. */
  SD_BLE_GATTC_CHAR_VALUE_BY_UUID_READ,                        /**< Read Characteristic Value by UUID. */
  SD_BLE_GATTC_READ,                                           /**< Generic read. */
  SD_BLE_GATTC_CHAR_VALUES_READ,                               /**< Read multiple Characteristic Values. */
  SD_BLE_GATTC_WRITE,                                          /**< Generic write. */
  SD_BLE_GATTC_HV_CONFIRM                                      /**< Handle Value Confirmation. */
};

/** @} */

/** @addtogroup BLE_GATTC_DEFINES Defines
 * @{ */

/** @defgroup BLE_ERRORS_GATTC SVC return values specific to GATTC
 * @{ */
#define BLE_ERROR_GATTC_PROC_NOT_PERMITTED    (NRF_GATTC_ERR_BASE + 0x000)
/** @} */

/**@brief Last Attribute Handle. */
#define BLE_GATTC_HANDLE_END                0xFFFF

/** @} */

/** @addtogroup BLE_GATTC_STRUCTURES Structures
 * @{ */

/**@brief Operation Handle Range. */
typedef struct
{
  uint16_t          start_handle; /**< Start Handle. */
  uint16_t          end_handle;   /**< End Handle. */
} ble_gattc_handle_range_t;


/**@brief GATT service. */
typedef struct
{
  ble_uuid_t               uuid;          /**< Service UUID. */
  ble_gattc_handle_range_t handle_range;  /**< Service Handle Range. */
} ble_gattc_service_t;


/**@brief  GATT include. */
typedef struct
{
  uint16_t            handle;           /**< Include Handle. */
  ble_gattc_service_t included_srvc;    /**< Handle of the included service. */
} ble_gattc_include_t;


/**@brief GATT characteristic. */
typedef struct
{
  ble_uuid_t              uuid;                 /**< Characteristic UUID. */
  ble_gatt_char_props_t   char_props;           /**< Characteristic Properties. */
  uint8_t                 char_ext_props : 1;   /**< Extended properties present. */
  uint16_t                handle_decl;          /**< Handle of the Characteristic Declaration. */
  uint16_t                handle_value;         /**< Handle of the Characteristic Value. */
} ble_gattc_char_t;


/**@brief GATT descriptor. */
typedef struct
{
  uint16_t          handle;         /**< Descriptor Handle. */
  ble_uuid_t        uuid;           /**< Descriptor UUID. */
} ble_gattc_desc_t;


/**@brief Write Parameters. */
typedef struct
{
  uint8_t    write_op;                 /**< Write Operation to be performed, see @ref BLE_GATT_WRITE_OPS. */
  uint16_t   handle;                   /**< Handle to the attribute to be written. */
  uint16_t   offset;                   /**< Offset in bytes. @note For WRITE_CMD and WRITE_REQ, offset must be 0. */
  uint16_t   len;                      /**< Length of data in bytes. */
  uint8_t*   p_value;                  /**< Pointer to the value data. */
  uint8_t    flags;                    /**< Flags, see @ref BLE_GATT_EXEC_WRITE_FLAGS. */
} ble_gattc_write_params_t;


/**
 * @brief GATT Client Event IDs.
 */
enum BLE_GATTC_EVTS
{
  BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP = BLE_GATTC_EVT_BASE,  /**< Primary Service Discovery Response event.  */
  BLE_GATTC_EVT_REL_DISC_RSP,                             /**< Relationship Discovery Response event. */
  BLE_GATTC_EVT_CHAR_DISC_RSP,                            /**< Characteristic Discovery Response event. */
  BLE_GATTC_EVT_DESC_DISC_RSP,                            /**< Descriptor Discovery Response event. */
  BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP,                /**< Read By UUID Response event. */
  BLE_GATTC_EVT_READ_RSP,                                 /**< Read Response event. */
  BLE_GATTC_EVT_CHAR_VALS_READ_RSP,                       /**< Read multiple Response event. */
  BLE_GATTC_EVT_WRITE_RSP,                                /**< Write Response event. */
  BLE_GATTC_EVT_HVX,                                      /**< Handle Value Notification or Indication event. */
  BLE_GATTC_EVT_TIMEOUT                                   /**< Timeout event. */
};

/**@brief Event structure for BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP. */
typedef struct
{
  uint16_t             count;           /**< Service count. */
  ble_gattc_service_t services[1];      /**< Service data, variable length. */
} ble_gattc_evt_prim_srvc_disc_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_REL_DISC_RSP. */
typedef struct
{
  uint16_t             count;           /**< Include count. */
  ble_gattc_include_t includes[1];      /**< Include data, variable length. */
} ble_gattc_evt_rel_disc_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_CHAR_DISC_RSP. */
typedef struct
{
  uint16_t            count;          /**< Characteristic count. */
  ble_gattc_char_t    chars[1];       /**< Characteristic data, variable length. */
} ble_gattc_evt_char_disc_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_DESC_DISC_RSP. */
typedef struct
{
  uint16_t            count;          /**< Descriptor count. */
  ble_gattc_desc_t    descs[1];       /**< Descriptor data, variable length. */
} ble_gattc_evt_desc_disc_rsp_t;

/**@brief GATT read by UUID handle value pair. */
typedef struct 
{
  uint16_t            handle;          /**< Attribute Handle. */
  uint8_t             *p_value;        /**< Pointer to value, variable length (length available as value_len in ble_gattc_evt_read_by_uuid_rsp_t). 
                                            Please note that this pointer is absolute to the memory provided by the user when retrieving the event,
                                            so it will effectively point to a location inside the handle_value array. */
} ble_gattc_handle_value_t;

/**@brief Event structure for BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP. */
typedef struct
{
  uint16_t                  count;            /**< Handle-Value Pair Count. */
  uint16_t                  value_len;        /**< Length of the value in Handle-Value(s) list. */
  ble_gattc_handle_value_t  handle_value[1];  /**< Handle-Value(s) list, variable length. */
} ble_gattc_evt_char_val_by_uuid_read_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_READ_RSP. */
typedef struct
{
  uint16_t            handle;         /**< Attribute Handle. */
  uint16_t            offset;         /**< Offset of the attribute data. */
  uint16_t            len;            /**< Attribute data length. */
  uint8_t             data[1];        /**< Attribute data, variable length. */
} ble_gattc_evt_read_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_CHAR_VALS_READ_RSP. */
typedef struct
{
  uint16_t            len;            /**< Concatenated Attribute values length. */
  uint8_t             values[1];      /**< Attribute values, variable length. */
} ble_gattc_evt_char_vals_read_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_WRITE_RSP. */
typedef struct
{
  uint16_t            handle;           /**< Attribute Handle. */
  uint8_t             write_op;         /**< Type of write operation, see @ref BLE_GATT_WRITE_OPS. */
  uint16_t            offset;           /**< Data Offset. */
  uint16_t            len;              /**< Data length. */
  uint8_t             data[1];          /**< Data, variable length. */
} ble_gattc_evt_write_rsp_t;

/**@brief Event structure for BLE_GATTC_EVT_HVX. */
typedef struct
{
  uint16_t            handle;         /**< Handle to which the HVx operation applies. */
  uint8_t             type;           /**< Indication or Notification, see @ref BLE_GATT_HVX_TYPES. */
  uint16_t            len;            /**< Attribute data length. */
  uint8_t             data[1];        /**< Attribute data, variable length. */
} ble_gattc_evt_hvx_t;

/**@brief Event structure for BLE_GATTC_EVT_TIMEOUT. */
typedef struct
{
  uint8_t          src;                       /**< Timeout source, see @ref BLE_GATT_TIMEOUT_SOURCES. */
} ble_gattc_evt_timeout_t;

/**@brief GATTC event type. */
typedef struct
{
  uint16_t            conn_handle;                /**< Connection Handle on which event occured. */
  uint16_t            gatt_status;                /**< GATT status code for the operation, see @ref BLE_GATT_STATUS_CODES. */
  uint16_t            error_handle;               /**< In case of error: The handle causing the error. In all other cases BLE_GATT_HANDLE_INVALID. */
  union
  {
    ble_gattc_evt_prim_srvc_disc_rsp_t          prim_srvc_disc_rsp;         /**< Primary Service Discovery Response Event Parameters. */
    ble_gattc_evt_rel_disc_rsp_t                rel_disc_rsp;               /**< Relationship Discovery Response Event Parameters. */
    ble_gattc_evt_char_disc_rsp_t               char_disc_rsp;              /**< Characteristic Discovery Response Event Parameters. */
    ble_gattc_evt_desc_disc_rsp_t               desc_disc_rsp;              /**< Descriptor Discovery Response Event Parameters. */
    ble_gattc_evt_char_val_by_uuid_read_rsp_t   char_val_by_uuid_read_rsp;  /**< Characteristic Value Read by UUID Response Event Parameters. */
    ble_gattc_evt_read_rsp_t                    read_rsp;                   /**< Read Response Event Parameters. */
    ble_gattc_evt_char_vals_read_rsp_t          char_vals_read_rsp;         /**< Characteristic Values Read Response Event Parameters. */
    ble_gattc_evt_write_rsp_t                   write_rsp;                  /**< Write Response Event Parameters. */
    ble_gattc_evt_hvx_t                         hvx;                        /**< Handle Value Notification/Indication Event Parameters. */
    ble_gattc_evt_timeout_t                     timeout;                    /**< Timeout Event Parameters. */
  } params;                                                                 /**< Event Parameters. @note Only valid if @ref gatt_status == BLE_GATT_STATUS_SUCCESS. */
} ble_gattc_evt_t;
/** @} */

#endif /* BLE_GATTC_H__ */

/**
  @}
  @}
*/
