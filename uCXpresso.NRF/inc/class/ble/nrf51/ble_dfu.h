/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/**@file
 *
 * @defgroup ble_sdk_srv_dfu Device Firmware Update Service
 * @{
 * @ingroup  ble_sdk_srv
 * @brief    Device Firmware Update Service
 *
 * @details  The Device Firmware Update (DFU) service is a GATT based service that can be used for
 *           performing firmware updates over BLE. Note that this implementation uses vendor
 *           specific UUIDs for service and characteristics and is intended to demonstrate the
 *           firmware updates over BLE. Refer @ref dfu_ble_service_spec and @ref
 *           dfu_ble_profile_spec for more information on the service and profile respectively.
 */

#ifndef _BLE_DFU_H__
#define _BLE_DFU_H__

#include <stdint.h>
#include "ble_gatts.h"
#include "ble.h"
#include "ble_srv_common.h"

#define BLE_DFU_SERVICE_UUID     0x1530                                 /**< The UUID of the DFU Service. */
#define BLE_DFU_PKT_CHAR_UUID    0x1532                                 /**< The UUID of the DFU Packet Characteristic. */
#define BLE_DFU_CTRL_PT_UUID     0x1531                                 /**< The UUID of the DFU Control Point. */
#define BLE_DFU_STATUS_REP_UUID  0x1533                                 /**< The UUID of the DFU Status Report Characteristic. */


/**@brief   DFU Event type.
 *
 * @details This enumeration contains the types of events that will be received from the DFU Service.
 */
typedef enum
{
    BLE_DFU_START,                                                      /**< The event indicating that the peer wants the application to prepare for a new firmware update. */
    BLE_DFU_RECEIVE_INIT_DATA,                                          /**< The event indicating that the peer wants the application to prepare to receive init parameters. */
    BLE_DFU_RECEIVE_APP_DATA,                                           /**< The event indicating that the peer wants the application to prepare to receive the new firmware image. */
    BLE_DFU_VALIDATE,                                                   /**< The event indicating that the peer wants the application to validate the newly received firmware image. */
    BLE_DFU_ACTIVATE_N_RESET,                                           /**< The event indicating that the peer wants the application to undergo activate new firmware and restart with new valid application */
    BLE_DFU_SYS_RESET,                                                  /**< The event indicating that the peer wants the application to undergo a reset and start the currently valid application image.*/
    BLE_DFU_PKT_RCPT_NOTIF_ENABLED,                                     /**< The event indicating that the peer has enabled packet receipt notifications. It is the responsibility of the application to call @ref ble_dfu_pkts_rcpt_notify each time the number of packets indicated by num_of_pkts field in @ref ble_dfu_evt_t is received.*/
    BLE_DFU_PKT_RCPT_NOTIF_DISABLED,                                    /**< The event indicating that the peer has disabled the packet receipt notifications.*/
    BLE_DFU_PACKET_WRITE,                                               /**< The event indicating that the peer has written a value to the 'DFU Packet' characteristic. The data received from the peer will be present in the @ref ble_dfu_pkt_write element contained within @ref ble_dfu_evt_t.*/
    BLE_DFU_BYTES_RECEIVED_SEND                                         /**< The event indicating that the peer is requesting for the number of bytes of firmware data last received by the application. It is the responsibility of the application to call @ref ble_dfu_pkts_rcpt_notify in response to this event. */
} ble_dfu_evt_type_t;

/**@brief   DFU Procedure type.
 *
 * @details This enumeration contains the types of DFU procedures.
 */
typedef enum
{
    BLE_DFU_START_PROCEDURE        = 1,                                 /**< DFU Start procedure.*/
    BLE_DFU_INIT_PROCEDURE         = 2,                                 /**< DFU Initialization procedure.*/
    BLE_DFU_RECEIVE_APP_PROCEDURE  = 3,                                 /**< Firmware receiving procedure.*/
    BLE_DFU_VALIDATE_PROCEDURE     = 4,                                 /**< Firmware image validation procedure .*/
    BLE_DFU_PKT_RCPT_REQ_PROCEDURE = 8                                  /**< Packet receipt notification request procedure. */
} ble_dfu_procedure_t;

/**@brief   DFU Response value type.
 */
typedef enum
{
    BLE_DFU_RESP_VAL_SUCCESS = 1,                                       /**< Success.*/
    BLE_DFU_RESP_VAL_INVALID_STATE,                                     /**< Invalid state.*/
    BLE_DFU_RESP_VAL_NOT_SUPPORTED,                                     /**< Operation not supported.*/
    BLE_DFU_RESP_VAL_DATA_SIZE,                                         /**< Data size exceeds limit.*/
    BLE_DFU_RESP_VAL_CRC_ERROR,                                         /**< CRC Error.*/
    BLE_DFU_RESP_VAL_OPER_FAILED                                        /**< Operation failed.*/
} ble_dfu_resp_val_t;

/**@brief   DFU Packet structure.
 *
 * @details This structure contains the value of the DFU Packet characteristic as written by the
 *          peer and the length of the value written. It will be filled by the DFU Service when the
 *          peer writes to the DFU Packet characteristic.
 */
typedef struct
{
    uint8_t                      len;                                   /**< Length of the packet received. */
    uint8_t *                    p_data;                                /**< Pointer to the received packet. This will point to a word aligned memory location.*/
} ble_dfu_pkt_write_t;

/**@brief   Packet receipt notification request structure.
 *
 * @details This structure contains the contents of the packet receipt notification request
 *          sent by the DFU Controller.
 */
typedef struct
{
    uint16_t                     num_of_pkts;                           /**< The number of packets of firmware data to be received by application before sending the next Packet Receipt Notification to the peer. */
} ble_pkt_rcpt_notif_req_t;

/**@brief   DFU Event structure.
 *
 * @details This structure contains the event generated by the DFU Service based on the data
 *          received from the peer.
 */
typedef struct
{
    ble_dfu_evt_type_t           ble_dfu_evt_type;                      /**< Type of the event.*/
    union
    {
        ble_dfu_pkt_write_t      ble_dfu_pkt_write;                     /**< The DFU packet received. This field is when the @ref ble_dfu_evt_type field is set to @ref BLE_DFU_PACKET_WRITE.*/
        ble_pkt_rcpt_notif_req_t pkt_rcpt_notif_req;                    /**< Packet receipt notification request. This field is when the @ref ble_dfu_evt_type field is set to @ref BLE_DFU_PKT_RCPT_NOTIF_ENABLED.*/
    } evt;
} ble_dfu_evt_t;

// Forward declaration of the ble_dfu_t type.
typedef struct ble_dfu_s ble_dfu_t;

/**@brief DFU Service event handler type. */
typedef void (*ble_dfu_evt_handler_t) (ble_dfu_t * p_dfu, ble_dfu_evt_t * p_evt);

/**@brief   DFU service structure.
 *
 * @details This structure contains status information related to the service.
 */
typedef struct ble_dfu_s
{
    uint16_t                     conn_handle;                           /**< Handle of the current connection (as provided by the S110 SoftDevice). This will be BLE_CONN_HANDLE_INVALID when not in a connection. */
    uint16_t                     service_handle;                        /**< Handle of DFU Service (as provided by the S110 SoftDevice). */
    uint8_t                      uuid_type;                             /**< UUID type assigned for DFU Service by the S110 SoftDevice. */
    ble_gatts_char_handles_t     dfu_pkt_handles;                       /**< Handles related to the DFU Packet characteristic. */
    ble_gatts_char_handles_t     dfu_ctrl_pt_handles;                   /**< Handles related to the DFU Control Point characteristic. */
    ble_gatts_char_handles_t     dfu_status_rep_handles;                /**< Handles related to the DFU Status Report characteristic. */
    ble_dfu_evt_handler_t        evt_handler;                           /**< The event handler to be called when an event is to be sent to the application.*/
    ble_srv_error_handler_t      error_handler;                         /**< Function to be called in case of an error. */
} ble_dfu_t;

/**@brief      DFU service initialization structure.
 *
 * @details    This structure contains the initialization information for the DFU Service. The
 *             application needs to fill this structure and pass it to the DFU Service using the
 *             @ref ble_dfu_init function.
 */
typedef struct
{
    ble_dfu_evt_handler_t        evt_handler;                           /**< Event handler to be called for handling events in the Device Firmware Update Service. */
    ble_srv_error_handler_t      error_handler;                         /**< Function to be called in case of an error. */
} ble_dfu_init_t;

#endif // BLE_DFU_H__

/** @} */
