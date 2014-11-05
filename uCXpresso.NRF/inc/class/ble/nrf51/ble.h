/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @addtogroup BLE_COMMON BLE SoftDevice Common
  @{
  @defgroup ble_api Events, type definitions and API calls
  @{

  @brief Module independent events, type definitions and API calls for the S110 SoftDevice.

 */

#ifndef BLE_H__
#define BLE_H__

#include "ble_ranges.h"
#include "ble_types.h"
#include "ble_gap.h"
#include "ble_l2cap.h"
#include "ble_gatt.h"
#include "ble_gattc.h"
#include "ble_gatts.h"

/**@brief User Memory Block. */
typedef struct
{
  uint8_t*          p_mem;      /**< Pointer to the start of the user memory block. */
  uint16_t          len;        /**< Length in bytes of the user memory block. */
} ble_user_mem_block_t;

/**
 * @brief TX complete event.
 */
typedef struct
{
  uint8_t count;                        /**< Number of packets transmitted. */
} ble_evt_tx_complete_t;

/**@brief Event structure for BLE_EVT_USER_MEM_REQUEST. */
typedef struct
{
  uint8_t                     type;     /**< User memory type, see @ref BLE_USER_MEM_TYPES. */
} ble_evt_user_mem_request_t;

/**@brief Event structure for BLE_EVT_USER_MEM_RELEASE. */
typedef struct
{
  uint8_t                     type;       /**< User memory type, see @ref BLE_USER_MEM_TYPES. */
  ble_user_mem_block_t        mem_block;  /**< User memory block */
} ble_evt_user_mem_release_t;


/**@brief Event structure for events not associated with a specific function module. */
typedef struct
{
  uint16_t conn_handle;                 /**< Connection Handle on which this event occured. */
  union
  {
    ble_evt_tx_complete_t           tx_complete;        /**< Transmission Complete. */
    ble_evt_user_mem_request_t      user_mem_request;   /**< User Memory Request Event Parameters. */
    ble_evt_user_mem_release_t      user_mem_release;   /**< User Memory Release Event Parameters. */
  } params;
} ble_common_evt_t;

/**@brief BLE Event header. */
typedef struct
{
  uint16_t evt_id;                      /**< Value from a BLE_<module>_EVT series. */
  uint16_t evt_len;                     /**< Length in octets excluding this header. */
} ble_evt_hdr_t;

/**@brief Common BLE Event type, wrapping the module specific event reports. */
typedef struct
{
  ble_evt_hdr_t header;                 /**< Event header. */
  union
  {
    ble_common_evt_t  common_evt;         /**< Common Event, evt_id in BLE_EVT_* series. */
    ble_gap_evt_t     gap_evt;            /**< GAP originated event, evt_id in BLE_GAP_EVT_* series. */
    ble_l2cap_evt_t   l2cap_evt;          /**< L2CAP originated event, evt_id in BLE_L2CAP_EVT* series. */
    ble_gattc_evt_t   gattc_evt;          /**< GATT client originated event, evt_id in BLE_GATTC_EVT* series. */
    ble_gatts_evt_t   gatts_evt;          /**< GATT server originated event, evt_id in BLE_GATTS_EVT* series. */
  } evt;
} ble_evt_t;


/**
 * @brief Version Information.
 */
typedef struct
{
  uint8_t   version_number;             /**< Link Layer Version number for BT 4.1 spec is 7 (https://www.bluetooth.org/en-us/specification/assigned-numbers/link-layer). */
  uint16_t  company_id;                 /**< Company ID, Nordic Semiconductor's company ID is 89 (0x0059) (https://www.bluetooth.org/apps/content/Default.aspx?doc_id=49708). */
  uint16_t  subversion_number;          /**< Link Layer Sub Version number, corresponds to the SoftDevice Config ID or Firmware ID (FWID). */
} ble_version_t;

/**@brief Mutual exclusion of radio activity and CPU execution.
 *
 *        This option configures the application's access to the CPU when the radio is active. The
 *        application can configure itself to have access to the CPU while the radio is active.
 *        By default, the application will be not able to share CPU time with the SoftDevice
 *        during radio activity. This parameter structure is used together with @ref sd_ble_opt_set
 *        to configure the @ref BLE_COMMON_OPT_RADIO_CPU_MUTEX option.
 *
 * @note  Note that the mutual exclusion of radio activity and CPU execution should remain enabled
 *        when running the SoftDevice on hardware affected by PAN #44 "CCM may exceed real time 
 *        requirements"and PAN #45 "AAR may exceed real time requirements".
 *
 * @note  @ref sd_ble_opt_get is not supported for this option.
 *
 */
typedef struct
{
  uint8_t enable : 1;                          /**< Enable mutual exclusion of radio activity and the CPU execution. */
} ble_common_opt_radio_cpu_mutex_t;

/**@brief Option structure for common options. */
typedef union
{
  ble_common_opt_radio_cpu_mutex_t  radio_cpu_mutex;        /**< Parameters for the option for the mutual exclusion of radio activity and CPU execution. */
} ble_common_opt_t;

/**@brief Common BLE Option type, wrapping the module specific options. */
typedef union
{
  ble_common_opt_t  common_opt;         /**< Common option, opt_id in BLE_COMMON_OPT_* series. */
  ble_gap_opt_t     gap;                /**< GAP option, opt_id in BLE_GAP_OPT_* series. */
} ble_opt_t;

/**
 * @brief BLE GATTS init options
 */
typedef struct
{
  ble_gatts_enable_params_t  gatts_enable_params; /**< GATTS init options @ref ble_gatts_enable_params_t. */  
} ble_enable_params_t;

/** @} */

#endif /* BLE_H__ */

/**
  @}
  @}
*/
