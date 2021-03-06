/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @addtogroup BLE_L2CAP Logical Link Control and Adaptation Protocol (L2CAP)
  @{
  @brief Definitions and prototypes for the L2CAP interface.
 */

#ifndef _BLE_L2CAP_H__
#define _BLE_L2CAP_H__

#include "ble_types.h"
#include "ble_ranges.h"
#include "ble_err.h"

/**@addtogroup BLE_L2CAP_ENUMERATIONS Enumerations
 * @{ */

/**@brief L2CAP API SVC numbers. */
enum BLE_L2CAP_SVCS 
{
  SD_BLE_L2CAP_CID_REGISTER = BLE_L2CAP_SVC_BASE,  /**< Register a CID. */
  SD_BLE_L2CAP_CID_UNREGISTER,                     /**< Unregister a CID. */
  SD_BLE_L2CAP_TX                                  /**< Transmit a packet. */
};

/** @} */

/**@addtogroup BLE_L2CAP_DEFINES Defines
 * @{ */

/**@defgroup BLE_ERRORS_L2CAP SVC return values specific to L2CAP
 * @{ */
#define BLE_ERROR_L2CAP_CID_IN_USE            (NRF_L2CAP_ERR_BASE + 0x000)  /**< CID already in use. */
/** @} */

/**@brief Default L2CAP MTU. */
#define BLE_L2CAP_MTU_DEF           (23)    

/**@brief Invalid Channel Identifier. */
#define BLE_L2CAP_CID_INVALID       (0x0000) 

/**@brief Dynamic Channel Identifier base. */
#define BLE_L2CAP_CID_DYN_BASE      (0x0040) 

/**@brief Maximum amount of dynamic CIDs. */
#define BLE_L2CAP_CID_DYN_MAX       (8) 

/** @} */

/**@addtogroup BLE_L2CAP_STRUCTURES Structures
 * @{ */

/**@brief Packet header format for L2CAP transmission. */
typedef struct
{
  uint16_t   len;                                 /**< Length of valid info in data member. */
  uint16_t   cid;                                 /**< Channel ID on which packet is transmitted. */
} ble_l2cap_header_t;

/**@brief L2CAP Event IDs. */
enum BLE_L2CAP_EVTS 
{
  BLE_L2CAP_EVT_RX  = BLE_L2CAP_EVT_BASE          /**< L2CAP packet received. */
};


/**@brief L2CAP Received packet event report. */
typedef struct
{
  ble_l2cap_header_t header;                      /** L2CAP packet header. */
  uint8_t    data[1];                             /**< Packet data, variable length. */
} ble_l2cap_evt_rx_t;


/**@brief L2CAP event callback event structure. */
typedef struct
{
  uint16_t conn_handle;                           /**< Connection Handle on which event occured. */
  union
  {
    ble_l2cap_evt_rx_t rx;                        /**< RX Event parameters. */
  } params;
} ble_l2cap_evt_t;


#endif // BLE_L2CAP_H__

/**
  @}
*/
