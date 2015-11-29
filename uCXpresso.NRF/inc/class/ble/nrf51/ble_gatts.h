/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @addtogroup BLE_GATTS Generic Attribute Profile (GATT) Server
  @{
  @brief  Definitions and prototypes for the GATTS interface.
 */

#ifndef _BLE_GATTS_H__
#define _BLE_GATTS_H__

#include "ble_types.h"
#include "ble_ranges.h"
#include "ble_l2cap.h"
#include "ble_gap.h"
#include "ble_gatt.h"

/** @addtogroup BLE_GATTS_ENUMERATIONS Enumerations
 * @{ */

/**
 * @brief GATTS API SVC numbers.
 */
enum BLE_GATTS_SVCS
{
  SD_BLE_GATTS_SERVICE_ADD = BLE_GATTS_SVC_BASE, /**< Add a service. */
  SD_BLE_GATTS_INCLUDE_ADD,                      /**< Add an included service. */
  SD_BLE_GATTS_CHARACTERISTIC_ADD,               /**< Add a characteristic. */
  SD_BLE_GATTS_DESCRIPTOR_ADD,                   /**< Add a generic attribute. */
  SD_BLE_GATTS_VALUE_SET,                        /**< Set an attribute value. */
  SD_BLE_GATTS_VALUE_GET,                        /**< Get an attribute value. */
  SD_BLE_GATTS_HVX,                              /**< Handle Value Notification or Indication. */
  SD_BLE_GATTS_SERVICE_CHANGED,                  /**< Perform a Service Changed Indication to one or more peers. */
  SD_BLE_GATTS_RW_AUTHORIZE_REPLY,               /**< Reply to an authorization request for a read or write operation on one or more attributes. */ 
  SD_BLE_GATTS_SYS_ATTR_SET,                     /**< Set the persistent system attributes for a connection. */  
  SD_BLE_GATTS_SYS_ATTR_GET,                     /**< Get updated persistent system attributes after terminating a connection. */
};

/** @} */

/** @addtogroup BLE_GATTS_DEFINES Defines
 * @{ */

/** @brief Only the default MTU size of 23 is currently supported. */
#define GATT_RX_MTU 23

/** @defgroup BLE_ERRORS_GATTS SVC return values specific to GATTS
 * @{ */
#define BLE_ERROR_GATTS_INVALID_ATTR_TYPE   (NRF_GATTS_ERR_BASE + 0x000) /**< Invalid attribute type. */
#define BLE_ERROR_GATTS_SYS_ATTR_MISSING    (NRF_GATTS_ERR_BASE + 0x001) /**< System Attributes missing. */
/** @} */

/** @defgroup BLE_GATTS_ATTR_LENS_MAX Maximum attribute lengths
 * @{ */
#define BLE_GATTS_FIX_ATTR_LEN_MAX (510)  /**< Maximum length for fixed length Attribute Values. */
#define BLE_GATTS_VAR_ATTR_LEN_MAX (512)  /**< Maximum length for variable length Attribute Values. */ 
/** @} */

/** @defgroup BLE_GATTS_SRVC_TYPES GATT Server Service Types
 * @{ */
#define BLE_GATTS_SRVC_TYPE_INVALID          0x00  /**< Invalid Service Type. */
#define BLE_GATTS_SRVC_TYPE_PRIMARY          0x01  /**< Primary Service. */
#define BLE_GATTS_SRVC_TYPE_SECONDARY        0x02  /**< Secondary Type. */
/** @} */


/** @defgroup BLE_GATTS_ATTR_TYPES GATT Server Attribute Types
 * @{ */
#define BLE_GATTS_ATTR_TYPE_INVALID         0x00  /**< Invalid Attribute Type. */
#define BLE_GATTS_ATTR_TYPE_PRIM_SRVC_DECL  0x01  /**< Primary Service Declaration. */
#define BLE_GATTS_ATTR_TYPE_SEC_SRVC_DECL   0x02  /**< Secondary Service Declaration. */
#define BLE_GATTS_ATTR_TYPE_INC_DECL        0x03  /**< Include Declaration. */
#define BLE_GATTS_ATTR_TYPE_CHAR_DECL       0x04  /**< Characteristic Declaration. */
#define BLE_GATTS_ATTR_TYPE_CHAR_VAL        0x05  /**< Characteristic Value. */
#define BLE_GATTS_ATTR_TYPE_DESC            0x06  /**< Descriptor. */
#define BLE_GATTS_ATTR_TYPE_OTHER           0x07  /**< Other, non-GATT specific type. */
/** @} */


/** @defgroup BLE_GATTS_OPS GATT Server Operations
 * @{ */
#define BLE_GATTS_OP_INVALID                0x00  /**< Invalid Operation. */
#define BLE_GATTS_OP_WRITE_REQ              0x01  /**< Write Request. */
#define BLE_GATTS_OP_WRITE_CMD              0x02  /**< Write Command. */
#define BLE_GATTS_OP_SIGN_WRITE_CMD         0x03  /**< Signed Write Command. */
#define BLE_GATTS_OP_PREP_WRITE_REQ         0x04  /**< Prepare Write Request. */
#define BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL  0x05  /**< Execute Write Request: Cancel all prepared writes. */
#define BLE_GATTS_OP_EXEC_WRITE_REQ_NOW     0x06  /**< Execute Write Request: Immediately execute all prepared writes. */
/** @} */

/** @defgroup BLE_GATTS_VLOCS GATT Value Locations
 * @{ */
#define BLE_GATTS_VLOC_INVALID       0x00  /**< Invalid Location. */
#define BLE_GATTS_VLOC_STACK         0x01  /**< Attribute Value is located in stack memory, no user memory is required. */
#define BLE_GATTS_VLOC_USER          0x02  /**< Attribute Value is located in user memory. This requires the user to maintain a valid buffer through the lifetime of the attribute, since the stack
                                                will read and write directly to the memory using the pointer provided in the APIs. There are no alignment requirements for the buffer. */
/** @} */

/** @defgroup BLE_GATTS_AUTHORIZE_TYPES GATT Server Authorization Types
 * @{ */
#define BLE_GATTS_AUTHORIZE_TYPE_INVALID    0x00  /**< Invalid Type. */
#define BLE_GATTS_AUTHORIZE_TYPE_READ       0x01  /**< Authorize a Read Operation. */
#define BLE_GATTS_AUTHORIZE_TYPE_WRITE      0x02  /**< Authorize a Write Request Operation. */
/** @} */


/** @} */

/** @addtogroup BLE_GATTS_STRUCTURES Structures
 * @{ */

/**
 * @brief BLE GATTS init options
 */
typedef struct
{
  uint8_t   service_changed:1;             /**< Include the Service Changed characteristic in the local attributes. */
} ble_gatts_enable_params_t;

/**@brief Attribute metadata. */
typedef struct
{
  ble_gap_conn_sec_mode_t read_perm;       /**< Read permissions. */
  ble_gap_conn_sec_mode_t write_perm;      /**< Write permissions. */
  uint8_t                 vlen       :1;   /**< Variable length attribute. */
  uint8_t                 vloc       :2;   /**< Value location, see @ref BLE_GATTS_VLOCS.*/
  uint8_t                 rd_auth    :1;   /**< Read Authorization and value will be requested from the application on every read operation. */ 
  uint8_t                 wr_auth    :1;   /**< Write Authorization will be requested from the application on every Write Request operation (but not Write Command). */
} ble_gatts_attr_md_t;


/**@brief GATT Attribute. */
typedef struct
{
  ble_uuid_t*          p_uuid;          /**< Pointer to the attribute UUID. */
  ble_gatts_attr_md_t* p_attr_md;       /**< Pointer to the attribute metadata structure. */
  uint16_t             init_len;        /**< Initial attribute value length in bytes. */
  uint16_t             init_offs;       /**< Initial attribute value offset in bytes. If different from zero, the first init_offs bytes of the attribute value will be left uninitialized. */
  uint16_t             max_len;         /**< Maximum attribute value length in bytes, see @ref BLE_GATTS_ATTR_LENS_MAX for maximum values. */
  uint8_t*             p_value;         /**< Pointer to the attribute data. Please note that if the @ref BLE_GATTS_VLOC_USER value location is selected in the attribute metadata, this will have to point to a buffer
                                             that remains valid through the lifetime of the attribute. This excludes usage of automatic variables that may go out of scope or any other temporary location. 
                                             The stack may access that memory directly without the application's knowledge. */
} ble_gatts_attr_t;


/**@brief GATT Attribute Context. */
typedef struct
{
  ble_uuid_t           srvc_uuid;       /**< Service UUID. */
  ble_uuid_t           char_uuid;       /**< Characteristic UUID if applicable (BLE_UUID_TYPE_UNKNOWN if N/A). */
  ble_uuid_t           desc_uuid;       /**< Descriptor UUID if applicable (BLE_UUID_TYPE_UNKNOWN if N/A). */
  uint16_t             srvc_handle;     /**< Service Handle. */
  uint16_t             value_handle;    /**< Characteristic Handle if applicable (BLE_GATT_HANDLE_INVALID if N/A). */
  uint8_t              type;            /**< Attribute Type, see @ref BLE_GATTS_ATTR_TYPES. */
} ble_gatts_attr_context_t;


/**@brief GATT Characteristic Presentation Format. */
typedef struct
{
  uint8_t          format;      /**< Format of the value, see @ref BLE_GATT_CPF_FORMATS. */
  int8_t           exponent;    /**< Exponent for integer data types. */
  uint16_t         unit;        /**< UUID from Bluetooth Assigned Numbers. */
  uint8_t          name_space;  /**< Namespace from Bluetooth Assigned Numbers, see @ref BLE_GATT_CPF_NAMESPACES. */
  uint16_t         desc;        /**< Namespace description from Bluetooth Assigned Numbers, see @ref BLE_GATT_CPF_NAMESPACES. */
} ble_gatts_char_pf_t;


/**@brief GATT Characteristic metadata. */
typedef struct
{
  ble_gatt_char_props_t       char_props;               /**< Characteristic Properties. */
  ble_gatt_char_ext_props_t   char_ext_props;           /**< Characteristic Extended Properties. */
  uint8_t*                    p_char_user_desc;         /**< Pointer to a UTF-8, NULL if the descriptor is not required. */
  uint16_t                    char_user_desc_max_size;  /**< The maximum size in bytes of the user description descriptor. */
  uint16_t                    char_user_desc_size;      /**< The size of the user description, must be smaller or equal to char_user_desc_max_size. */ 
  ble_gatts_char_pf_t*        p_char_pf;                /**< Pointer to a presentation format structure or NULL if the descriptor is not required. */
  ble_gatts_attr_md_t*        p_user_desc_md;           /**< Attribute metadata for the User Description descriptor, or NULL for default values. */
  ble_gatts_attr_md_t*        p_cccd_md;                /**< Attribute metadata for the Client Characteristic Configuration Descriptor, or NULL for default values. */
  ble_gatts_attr_md_t*        p_sccd_md;                /**< Attribute metadata for the Server Characteristic Configuration Descriptor, or NULL for default values. */
} ble_gatts_char_md_t;


/**@brief GATT Characteristic Definition Handles. */
typedef struct
{
  uint16_t          value_handle;       /**< Handle to the characteristic value. */
  uint16_t          user_desc_handle;   /**< Handle to the User Description descriptor, or BLE_GATT_HANDLE_INVALID if not present. */
  uint16_t          cccd_handle;        /**< Handle to the Client Characteristic Configuration Descriptor, or BLE_GATT_HANDLE_INVALID if not present. */
  uint16_t          sccd_handle;        /**< Handle to the Server Characteristic Configuration Descriptor, or BLE_GATT_HANDLE_INVALID if not present. */
} ble_gatts_char_handles_t;


/**@brief GATT HVx parameters. */
typedef struct
{
  uint16_t          handle;             /**< Characteristic Value Handle. */
  uint8_t           type;               /**< Indication or Notification, see @ref BLE_GATT_HVX_TYPES. */
  uint16_t          offset;             /**< Offset within the attribute value. */
  uint16_t*         p_len;              /**< Length in bytes to be written, length in bytes written after successful return. */
  uint8_t*          p_data;             /**< Actual data content, use NULL to use the current attribute value. */
} ble_gatts_hvx_params_t;

/**@brief GATT Read Authorization parameters. */
typedef struct
{
  uint16_t          gatt_status;        /**< GATT status code for the operation, see @ref BLE_GATT_STATUS_CODES. */
  uint8_t           update : 1;         /**< If set, data supplied in p_data will be used in the ATT response. */
  uint16_t          offset;             /**< Offset of the attribute value being updated. */
  uint16_t          len;                /**< Length in bytes of the value in p_data pointer, see @ref BLE_GATTS_ATTR_LENS_MAX. */
  uint8_t*          p_data;             /**< Pointer to new value used to update the attribute value. */
} ble_gatts_read_authorize_params_t;

/**@brief GATT Write Authorisation parameters. */
typedef struct
{
  uint16_t          gatt_status;        /**< GATT status code for the operation, see @ref BLE_GATT_STATUS_CODES. */
} ble_gatts_write_authorize_params_t;

/**@brief GATT Read or Write Authorize Reply parameters. */
typedef struct
{
  uint8_t                               type;   /**< Type of authorize operation, see @ref BLE_GATTS_AUTHORIZE_TYPES. */
  union {
    ble_gatts_read_authorize_params_t   read;   /**< Read authorization parameters. */
    ble_gatts_write_authorize_params_t  write;  /**< Write authorization parameters. */
  } params;
} ble_gatts_rw_authorize_reply_params_t;


/**
 * @brief GATT Server Event IDs.
 */
enum BLE_GATTS_EVTS
{
  BLE_GATTS_EVT_WRITE = BLE_GATTS_EVT_BASE,       /**< Write operation performed. */
  BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST,             /**< Read/Write Authorization request. */
  BLE_GATTS_EVT_SYS_ATTR_MISSING,                 /**< A persistent system attribute access is pending, awaiting a sd_ble_gatts_sys_attr_set(). */
  BLE_GATTS_EVT_HVC,                              /**< Handle Value Confirmation. */
  BLE_GATTS_EVT_SC_CONFIRM,                       /**< Service Changed Confirmation. */
  BLE_GATTS_EVT_TIMEOUT                           /**< Timeout. */
};


/**@brief Event structure for BLE_GATTS_EVT_WRITE. */
typedef struct
{
  uint16_t                    handle;             /**< Attribute Handle. */
  uint8_t                     op;                 /**< Type of write operation, see @ref BLE_GATTS_OPS. */
  ble_gatts_attr_context_t    context;            /**< Attribute Context. */
  uint16_t                    offset;             /**< Offset for the write operation. */
  uint16_t                    len;                /**< Length of the incoming data. */
  uint8_t                     data[1];            /**< Incoming data, variable length. */
} ble_gatts_evt_write_t;

/**@brief Event structure for authorize read request. */
typedef struct
{
  uint16_t                    handle;             /**< Attribute Handle. */
  ble_gatts_attr_context_t    context;            /**< Attribute Context. */
  uint16_t                    offset;             /**< Offset for the read operation. */
} ble_gatts_evt_read_t;

/**@brief Event structure for BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST. */
typedef struct
{
  uint8_t                     type;             /**< Type of authorize operation, see @ref BLE_GATTS_AUTHORIZE_TYPES. */
  union {
    ble_gatts_evt_read_t      read;             /**< Attribute Read Parameters. */
    ble_gatts_evt_write_t     write;            /**< Attribute Write Parameters. */
  } request;
} ble_gatts_evt_rw_authorize_request_t;

/**@brief Event structure for BLE_GATTS_EVT_SYS_ATTR_MISSING. */
typedef struct
{
  uint8_t hint;
} ble_gatts_evt_sys_attr_missing_t;


/**@brief Event structure for BLE_GATTS_EVT_HVC. */
typedef struct
{
  uint16_t          handle;                       /**< Attribute Handle. */
} ble_gatts_evt_hvc_t;

/**@brief Event structure for BLE_GATTS_EVT_TIMEOUT. */
typedef struct
{
  uint8_t          src;                       /**< Timeout source, see @ref BLE_GATT_TIMEOUT_SOURCES. */
} ble_gatts_evt_timeout_t;


/**@brief GATT Server event callback event structure. */
typedef struct
{
  uint16_t conn_handle;                                       /**< Connection Handle on which event occurred. */
  union
  {
    ble_gatts_evt_write_t                 write;              /**< Write Event Parameters. */
    ble_gatts_evt_rw_authorize_request_t  authorize_request;  /**< Read or Write Authorize Request Parameters. */
    ble_gatts_evt_sys_attr_missing_t      sys_attr_missing;   /**< System attributes missing. */
    ble_gatts_evt_hvc_t                   hvc;                /**< Handle Value Confirmation Event Parameters. */
    ble_gatts_evt_timeout_t               timeout;            /**< Timeout Event. */
  } params;
} ble_gatts_evt_t;

/** @} */

#endif // BLE_GATTS_H__

/**
  @}
*/
