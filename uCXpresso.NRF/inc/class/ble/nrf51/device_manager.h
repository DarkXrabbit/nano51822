/* Copyright (C) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/**
 * @file device_manager.h
 *
 * @defgroup device_manager Device Manager
 * @ingroup ble_sdk_lib
 * @{
 * @brief Device Manager Application Interface Abstraction.
 *
 * @details The Device Manager module manages Active and Bonded Peers. Management of peer includes
 *          book keeping of contextual information like the Security Keys, GATT
 *          configuration and any application specific information.
 *
 *          Active Peers are devices which are connected, and may or may not be bonded.
 *          Bonded Peers are devices which are bonded, and may or may not be Active (Connected).
 *          Active Bonded Peer refers to a device which is connected and bonded.
 *
 *          Paired Devices refers to peer devices that are connected and have necessary context
 *          establishment/exchange for the current connection session. On disconnect,
 *          all contextual information is flushed. For example, SMP Information Exchanged during
 *          pairing and GATT Configuration is not retained on disconnection.
 *
 *          Note that this module allows management of contextual information but 
 *          does not provide an interface for connection management. Therefore, entering connectible
 *          mode, connection establishment, or disconnection of a link with peer is not in scope
 *          of this module.
 *
 *          For bonded peers, the contextual information is required to be retained on disconnection
 *          and power cycling. Persistent storage of contextual information is handled by the
 *          module. This module categorizes the contextual information into 3 categories:
 *             - <b>Bonding Information</b>
 *               Bond information is the information exchanged between local and peer device to
 *               establish a bond. It also includes peer identification information,
 *               like the peer address or the IRK or both. From here on this category of information
 *               is referred to as Device Context.
 *             - <b>Service/Protocol Information</b>
 *               Service/Protocol information is the information retained for the peer to save on one-time
 *               procedures like the GATT Service Discovery procedures and Service Configurations.
 *               It allows devices to resume data exchange on subsequent reconnection without having
 *               to perform initial set-up procedures each time. From here on this category is
 *               referred to as Service Context.
 *             - <b>Application Information</b>
 *               Application information is the context that the application would like to associate with
 *               each of the bonded device. For example, if the application chooses to rank its peers
 *               in order to manage them better, the rank information could be treated as
 *               Application Information. This storage space is provided to save the application from
 *               maintaining a mapping table with each Device Instance and Application Information.
 *               However, if the application have no use for this, it is possible to not
 *               use or employ this at compile time. From here on this category of information is
 *               referred to as Application Context.
 */


#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_common.h"
#include "ble.h"
#include "ble_gap.h"

/**
 * @defgroup dm_service_cntext_types Service/Protocol Types
 *
 * @brief Describes the possible types of Service/Protocol Contexts for a bonded/peer device.
 *
 * @details Possible Service/Protocol context per peer device. The Device Manager provides the
 *          functionality of persistently storing the Service/Protocol context and can automatically
 *          load them when needed.
 *          For example system attributes for a GATT Server. Based on the nature of the application, 
 *          not all service types may be needed. The application can specify
 *          only the service/protocol context it wants to use at the time of registration.
 * @{
 */
#define DM_PROTOCOL_CNTXT_NONE         0x00  /**< No Service Context, this implies the application does not want to associate any service/protocol context with the peer device */
#define DM_PROTOCOL_CNTXT_GATT_SRVR_ID 0x01  /**< GATT Server Service Context, this implies the application does associate GATT Server with the peer device and this information will be loaded when needed for a bonded device */
#define DM_PROTOCOL_CNTXT_GATT_CLI_ID  0x02  /**< GATT Client Service Context, this implies the application does associate GATT Client with the peer device and this information will be loaded when needed for a bonded device */
#define DM_PROTOCOL_CNTXT_ALL                                                                     \
        (DM_PROTOCOL_CNTXT_GATT_SRVR_ID | DM_PROTOCOL_CNTXT_GATT_CLI_ID) /**< All Service/Protocol Context, this implies that the application wants to associate all Service/Protocol Information with the bonded device. This is configurable based on system requirements. If the application has only one type of service, this define could be altered to reflect the same.  */
/** @} */


/**
 * @defgroup dm_events Device Manager Events
 *
 * @brief This section describes the device manager events that are notified to the application.
 *
 * @details The Device Manager notifies the application of various asynchronous events using the
 *          asynchronous event notification callback. All events has been categorized into:
 *          a. General.
 *          b. Link Status.
 *          c. Context Management.
 *
 *          In the callback, these events are notified along with handle that uniquely identifies:
 *          application instance, active instance (if applicable), device instance
 *          bonding instance, (if applicable) and service instance.
 *          Not all events are pertaining to an active connection, for example a context deletion event could occur even if the peer
 *          is not connected. Also, general category of events may not be pertaining to any specific peer.
 *          See also \ref dm_event_cb_t and \ref dm_register.
 * @{
 */
/**
 * @defgroup general_events General Events
 *
 * @brief General or miscellaneous events.
 *
 * @details This category of events are general events not pertaining to a peer or context.
 *
 * @{
 */
#define DM_EVT_RFU   0x00 /**< Reserved for future use, is never notified. */
#define DM_EVT_ERROR 0x01 /**< Device Manager Event Error. */
/** @} */

/**
 * @defgroup link_status_events Link Status Events
 *
 * @brief Link Status Events.
 *
 * @details This category of events notify the application of the link status. Event result associated
 *          with the event is provided along with the event in the callback to provide more details of
 *          whether a procedure succeeded or failed and assist the application in decision making of
 *          how to proceed. For example if a DM_DEVICE_CONNECT_IND is indicated with NRF_SUCCESS
 *          result, the application may want to proceed with discovering and association with
 *          service of the peer. However, if indicated with a failure result, the application may
 *          want to take an alternate action such as reattempting to connect or go into a
 *          sleep mode.
 *
 * @{
 */
#define DM_EVT_CONNECTION              0x11 /**< Indicates that link with the peer is established. */
#define DM_EVT_DISCONNECTION           0x12 /**< Indicates that link with peer is torn down. */
#define DM_EVT_SECURITY_SETUP          0x13 /**< Security procedure for link started indication */
#define DM_EVT_SECURITY_SETUP_COMPLETE 0x14 /**< Security procedure for link completion indication. */
#define DM_EVT_LINK_SECURED            0x15 /**< Indicates that link with the peer is secured. For bonded devices, subsequent reconnections with bonded peer will result only in this event when the link is secured and setup procedures will not occur unless the bonding information is either lost or deleted on either or both sides.  */
#define DM_EVT_SECURITY_SETUP_REFRESH  0x16 /**< Indicates that the security on the link was re-established. */
/** @} */

/**
 * @defgroup context_mgmt_events Context Management Events
 *
 * @brief Context Management Events.
 *
 * @details These events notify the application of the status of context loading and storing.
 *
 * @{
 */
#define DM_EVT_DEVICE_CONTEXT_LOADED   0x21 /**< Indicates that device context for a peer is loaded. */
#define DM_EVT_DEVICE_CONTEXT_STORED   0x22 /**< Indicates that device context is stored persistently. */
#define DM_EVT_DEVICE_CONTEXT_DELETED  0x23 /**< Indicates that device context is deleted. */
#define DM_EVT_SERVICE_CONTEXT_LOADED  0x31 /**< Indicates that service context for a peer is loaded. */
#define DM_EVT_SERVICE_CONTEXT_STORED  0x32 /**< Indicates that service context is stored persistently. */
#define DM_EVT_SERVICE_CONTEXT_DELETED 0x33 /**< Indicates that service context is deleted. */
#define DM_EVT_APPL_CONTEXT_LOADED     0x41 /**< Indicates that application context for a peer is loaded. */
#define DM_EVT_APPL_CONTEXT_STORED     0x42 /**< Indicates that application context is stored persistently. */
#define DM_EVT_APPL_CONTEXT_DELETED    0x43 /**< Indicates that application context is deleted. */
/** @} */
/** @} */

#define DM_INVALID_ID 0xFF /**< Invalid instance idenitifer. */

/**
 * @defgroup dm_data_structure Device Manager Data Types
 *
 * @brief This section describes all the data types exposed by the module to the application.
 * @{
 */

/**
 * @brief Application Instance.
 *
 * @details Application instance uniquely identifies an application. The identifier is allocated by
 *          the device manager when application registers with the module. The application is
 *          expected to identify itself with this instance identifier when initiating subsequent
 *          requests. Application should use the utility API \ref dm_application_instance_set in
 *          order to set its application instance in dm_handle_t needed for all subsequent APIs.
 *          See also \ref dm_register.
 */
typedef uint8_t dm_application_instance_t;

/**
 * @brief Connection Instance.
 *
 * @details Identifies connection instance for an active device. This instance is allocated by the 
 *          device manager when a connection is established and is notified with DM_EVT_CONNECTION
 *          with the event result NRF_SUCCESS.
 */
typedef uint8_t dm_connection_instance_t;

/**
 * @brief Device Instance.
 *
 * @details Uniquely identifies a bonded peer device. The peer device may or may not be connected.
 *          In case of the central: The bonded device instance to identify the peer is allocated when bonding procedure is initiated by the central using dm_security_setup_req.
 *          In case of the peripheral: When the bonding procedure is successful, the DM_EVT_SECURITY_SETUP_COMPLETE event with success event result, is received.
 *          In case the module cannot add more bonded devices, no instance is allocated, this is indicated by an appropriate error code for the API/event as the case may be. Application can choose to disconnect the link.
 */
typedef uint8_t dm_device_instance_t;

/**
 * @brief Service Instance.
 *
 * @details Uniquely identifies a peer device. The peer device may or may not be connected. This
 *          instance is allocated by the device manager when a device is bonded and is notified
 *          when security procedures have been initiated.
 *          Security Procedures initiation is notified with DM_SECURITY_SETUP_IND with
 *          success event result. In case the event result indicates that the module cannot add more
 *          bonded devices, no instance is allocated. Application can chose to disconnect the link.
 */
typedef uint8_t dm_service_instance_t;

/**
 * @brief Service/Protocol Type Identifier.
 *
 * @details Uniquely identifies a service or a protocol type. Service/Protocol Type identification
 *          is needed as each service/protocol can have its own contextual data.
 *          This allows the peer to access more than one service at a time. \ref dm_service_cntext_types describes the
 *          list of services/protocols supported.
 */
typedef uint8_t service_type_t;

/**
 * @brief Device Handle used for unique identification of each peer.
 *
 * @details This data type is used to uniquely identify each peer device. A peer device could be
 *          active and/or bonded. Therefore an instance for active and bonded is provided.
 *          However, the application is expected to treat this is an opaque structure and use this for
 *          all API interactions once stored on appropriate events.
 *          See \ref dm_events.
 */
typedef struct device_handle
{
    dm_application_instance_t    appl_id;       /**< Identifies the application instances for the device that is being managed. */
    dm_connection_instance_t     connection_id; /**< Identifies the active connection instance. */
    dm_device_instance_t         device_id;     /**< Identifies peer instance in the data base. */
    dm_service_instance_t        service_id;    /**< Service instance identifier. */
} dm_handle_t;

/**
 * @brief Definition of Data Context.
 *
 * @details Defines contextual data format, it consists of context data length and pointer to data.
 */
typedef struct
{
    uint32_t  len;    /**< Length of data . */
    uint8_t * p_data; /**< Pointer to contextual data, a copy is made of the data. */
} dm_context_t;


/**
 * @brief Device Context.
 *
 * @details Defines "device context" type for a device managed by device manager.
 */
typedef dm_context_t dm_device_context_t;

/**
 * @brief Service Context.
 *
 * @details Service context data for a service identified by the 'service_type' field.
 */
typedef struct
{
    service_type_t service_type; /**< Identifies the service/protocol to which the context data is related. */
    dm_context_t   context_data; /**< Contains length and pointer to context data */
} dm_service_context_t;

/**
 * @brief Application context.
 *
 * @details The application context can be used by the application to map any application level
 *          information that is to be mapped with a particular peer.
 *          For bonded peers, this information will be stored by the bond manager persistently.
 *          Note that the device manager treats this information as an
 *          opaque block of bytes.
 *          Necessary APIs to get and set this context for a peer have been provided.
 */
typedef dm_context_t dm_application_context_t;

/**
 * @brief Event parameters.
 *
 * @details Defines event parameters for each of the events notified by the module.
 */
typedef union
{
    ble_gap_evt_t            * p_gap_param;       /**< All events that are triggered in device manager as a result of GAP events, like connection, disconnection and security procedures are accompanied with GAP parameters. */
    dm_application_context_t * p_app_context;     /**< All events that are associated with application context procedures of store, load, and deletion have this as event parameter. */
    dm_service_context_t     * p_service_context; /**< All events that are associated with service context procedures of store, load and deletion have this as event parameter. */
    dm_device_context_t      * p_device_context;  /**< All events that are associated with device context procedures of store, load and deletion have this as event parameter. */
} dm_event_param_t;

/**
 * @brief Asynchronous events details notified to the application by the module.
 *
 * @details Defines event type along with event parameters notified to the application by the
 *          module.
 */
typedef struct
{
    uint8_t          event_id;       /**< Identifies the event. See \ref dm_events for details on event types and their significance. */
    dm_event_param_t event_param;    /**< Event parameters. Can be NULL if the event does not have any parameters. */
    uint16_t         event_paramlen; /**< Length of the event parameters, is zero if the event does not have any parameters. */
} dm_event_t;

/**
 * @brief Event notification callback registered by application with the module.
 *
 * @details Event notification callback registered by application with the module when registering
 *          the module using \ref dm_register API.
 *
 * @param[in] p_handle   Identifies the peer for which the event is being notified.
 * @param[in] p_event    Identifies the event, any associated parameters and parameter length.
 *                       See \ref dm_events for details on event types and their significance.
 * @param[in,out] event_result   Provide additional information on the event. 
 *                      In addition to SDK error codes there is also a return value
 *                      indicating if maximum number of connections has been reached when connecting or bonding.
 *
 * @retval NRF_SUCCESS on success, or a failure to indicate if it could handle the event
 *         successfully. There is no action taken in case application returns a failure.
 */
typedef api_result_t (*dm_event_cb_t)(dm_handle_t const * p_handle,
                                      dm_event_t const  * p_event,
                                      api_result_t        event_result);

/**
 * @brief Initialization Parameters.
 *
 * @details Indicates the application parameters. Currently this only encompasses clearing
 *          all persistent data.
 */
typedef struct
{
    bool clear_persistent_data; /**< Set to true in case the module should clear all persistent data. */
} dm_init_param_t;

/**
 * @brief Application Registration Parameters.
 *
 * @details Parameters needed by the module when registering with it.
 */
typedef struct
{
    dm_event_cb_t        evt_handler;  /**< Event Handler to be registered. It will receive asynchronous notification from the module, see \ref dm_events for asynchronous events. */
    uint8_t              service_type; /**< Bit mask identifying services that the application intends to support for all peers. */
    ble_gap_sec_params_t sec_param;    /**< Security parameters to be used for the application. */
} dm_application_param_t;

/**
 * @brief Defines possible security status/states.
 *
 * @details Defines possible security status/states of a link when requested by application using
 *          the \ref dm_security_status_req.
 */
typedef enum
{
    NOT_ENCRYPTED,                  /**< The link does not security. */
    ENCRYPTION_IN_PROGRESS, /**< Security is in progress of being established.*/
    ENCRYPTED              /**< The link is secure.*/
} dm_security_status_t;
/** @} */

/** @} */
/** @} */
/** @} */
#endif // DEVICE_MANAGER_H__

