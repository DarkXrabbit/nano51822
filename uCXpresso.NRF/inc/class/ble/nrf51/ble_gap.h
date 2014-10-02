/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @addtogroup BLE_GAP Generic Access Profile (GAP)
  @{
  @brief Definitions and prototypes for the GAP interface.
 */

#ifndef _BLE_GAP_H__
#define _BLE_GAP_H__

#include "ble_types.h"
#include "ble_ranges.h"

/**@addtogroup BLE_GAP_ENUMERATIONS Enumerations 
 * @{ */

/**@brief GAP API SVC numbers.
 */
enum BLE_GAP_SVCS
{
  SD_BLE_GAP_ADDRESS_SET  = BLE_GAP_SVC_BASE,  /**< Set own Bluetooth Address. */
  SD_BLE_GAP_ADDRESS_GET,                      /**< Get own Bluetooth Address. */
  SD_BLE_GAP_ADV_DATA_SET,                     /**< Set Advertisement Data. */
  SD_BLE_GAP_ADV_START,                        /**< Start Advertising. */
  SD_BLE_GAP_ADV_STOP,                         /**< Stop Advertising. */
  SD_BLE_GAP_CONN_PARAM_UPDATE,                /**< Connection Parameter Update. */
  SD_BLE_GAP_DISCONNECT,                       /**< Disconnect. */
  SD_BLE_GAP_TX_POWER_SET,                     /**< Set TX Power. */
  SD_BLE_GAP_APPEARANCE_SET,                   /**< Set Appearance. */
  SD_BLE_GAP_APPEARANCE_GET,                   /**< Get Appearance. */
  SD_BLE_GAP_PPCP_SET,                         /**< Set PPCP. */
  SD_BLE_GAP_PPCP_GET,                         /**< Get PPCP. */
  SD_BLE_GAP_DEVICE_NAME_SET,                  /**< Set Device Name. */
  SD_BLE_GAP_DEVICE_NAME_GET,                  /**< Get Device Name. */
  SD_BLE_GAP_AUTHENTICATE,                     /**< Initiate Pairing/Bonding. */
  SD_BLE_GAP_SEC_PARAMS_REPLY,                 /**< Reply with Security Parameters. */
  SD_BLE_GAP_AUTH_KEY_REPLY,                   /**< Reply with an authentication key. */
  SD_BLE_GAP_SEC_INFO_REPLY,                   /**< Reply with Security Information. */
  SD_BLE_GAP_CONN_SEC_GET,                     /**< Obtain connection security level. */
  SD_BLE_GAP_RSSI_START,                       /**< Start reporting of changes in RSSI. */ 
  SD_BLE_GAP_RSSI_STOP,                        /**< Stop reporting of changes in RSSI. */ 
};
/**@} */

/**@addtogroup BLE_GAP_DEFINES Defines
 * @{ */

/**@defgroup BLE_ERRORS_GAP SVC return values specific to GAP
 * @{ */
#define BLE_ERROR_GAP_UUID_LIST_MISMATCH            (NRF_GAP_ERR_BASE + 0x000)  /**< UUID list does not contain an integral number of UUIDs. */
#define BLE_ERROR_GAP_DISCOVERABLE_WITH_WHITELIST   (NRF_GAP_ERR_BASE + 0x001)  /**< Use of Whitelist not permitted with discoverable advertising. */
#define BLE_ERROR_GAP_INVALID_BLE_ADDR              (NRF_GAP_ERR_BASE + 0x002)  /**< The upper two bits of the address do not correspond to the specified address type. */
/**@} */


/**@defgroup BLE_GAP_ROLES GAP Roles
 * @note Not explicitly used in peripheral API, but will be relevant for central API.
 * @{ */
#define BLE_GAP_ROLE_INVALID     0x0            /**< Invalid Role. */
#define BLE_GAP_ROLE_PERIPH      0x1            /**< Peripheral Role. */
#define BLE_GAP_ROLE_CENTRAL     0x2            /**< Central Role. */
/**@} */


/**@defgroup BLE_GAP_TIMEOUT_SOURCES GAP Timeout sources
 * @{ */
#define BLE_GAP_TIMEOUT_SRC_ADVERTISEMENT              0x00 /**< Advertisement timeout. */
#define BLE_GAP_TIMEOUT_SRC_SECURITY_REQUEST           0x01 /**< Security request timeout. */
/**@} */


/**@defgroup BLE_GAP_ADDR_TYPES GAP Address types
 * @{ */
#define BLE_GAP_ADDR_TYPE_PUBLIC                        0x00 /**< Public address. */
#define BLE_GAP_ADDR_TYPE_RANDOM_STATIC                 0x01 /**< Random Static address. */
#define BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE     0x02 /**< Private Resolvable address. */
#define BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE 0x03 /**< Private Non-Resolvable address. */
/**@} */

/**@defgroup BLE_GAP_ADDR_CYCLE_MODES GAP Address cycle modes
 * @{ */
#define BLE_GAP_ADDR_CYCLE_MODE_NONE      0x00 /**< Set addresses directly, no automatic address cycling. */
#define BLE_GAP_ADDR_CYCLE_MODE_AUTO      0x01 /**< Automatically generate and update private addresses. */
/** @} */

/**@brief The default interval in seconds at which a private address is refreshed when address cycle mode is @ref BLE_GAP_ADDR_CYCLE_MODE_AUTO.  */
#define BLE_GAP_DEFAULT_PRIVATE_ADDR_CYCLE_INTERVAL_S (60 * 15)

/** @brief BLE address length. */
#define BLE_GAP_ADDR_LEN            6


/**@defgroup BLE_GAP_AD_TYPE_DEFINITIONS GAP Advertising and Scan Response Data format
 * @note Found at https://www.bluetooth.org/Technical/AssignedNumbers/generic_access_profile.htm
 * @{ */
#define BLE_GAP_AD_TYPE_FLAGS                               0x01 /**< Flags for discoverability. */
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE   0x02 /**< Partial list of 16 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE         0x03 /**< Complete list of 16 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_MORE_AVAILABLE   0x04 /**< Partial list of 32 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_COMPLETE         0x05 /**< Complete list of 32 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE  0x06 /**< Partial list of 128 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE        0x07 /**< Complete list of 128 bit service UUIDs. */
#define BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME                    0x08 /**< Short local device name. */
#define BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME                 0x09 /**< Complete local device name. */
#define BLE_GAP_AD_TYPE_TX_POWER_LEVEL                      0x0A /**< Transmit power level. */
#define BLE_GAP_AD_TYPE_CLASS_OF_DEVICE                     0x0D /**< Class of device. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C               0x0E /**< Simple Pairing Hash C. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R         0x0F /**< Simple Pairing Randomizer R. */
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE           0x10 /**< Security Manager TK Value. */
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS          0x11 /**< Security Manager Out Of Band Flags. */
#define BLE_GAP_AD_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE     0x12 /**< Slave Connection Interval Range. */
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_16BIT       0x14 /**< List of 16-bit Service Solicitation UUIDs. */
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_128BIT      0x15 /**< List of 128-bit Service Solicitation UUIDs. */
#define BLE_GAP_AD_TYPE_SERVICE_DATA                        0x16 /**< Service Data - 16-bit UUID. */
#define BLE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS               0x17 /**< Public Target Address. */
#define BLE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS               0x18 /**< Random Target Address. */
#define BLE_GAP_AD_TYPE_APPEARANCE                          0x19 /**< Appearance. */
#define BLE_GAP_AD_TYPE_ADVERTISING_INTERVAL                0x1A /**< Advertising Interval. */ 
#define BLE_GAP_AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS         0x1B /**< LE Bluetooth Device Address. */
#define BLE_GAP_AD_TYPE_LE_ROLE                             0x1C /**< LE Role. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C256            0x1D /**< Simple Pairing Hash C-256. */
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R256      0x1E /**< Simple Pairing Randomizer R-256. */
#define BLE_GAP_AD_TYPE_SERVICE_DATA_32BIT_UUID             0x20 /**< Service Data - 32-bit UUID. */
#define BLE_GAP_AD_TYPE_SERVICE_DATA_128BIT_UUID            0x21 /**< Service Data - 128-bit UUID. */
#define BLE_GAP_AD_TYPE_3D_INFORMATION_DATA                 0x3D /**< 3D Information Data. */
#define BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA          0xFF /**< Manufacturer Specific Data. */
/**@} */


/**@defgroup BLE_GAP_ADV_FLAGS GAP Advertisement Flags
 * @{ */
#define BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE         (0x01)   /**< LE Limited Discoverable Mode. */
#define BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE         (0x02)   /**< LE General Discoverable Mode. */
#define BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED         (0x04)   /**< BR/EDR not supported. */
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_CONTROLLER         (0x08)   /**< Simultaneous LE and BR/EDR, Controller. */
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_HOST               (0x10)   /**< Simultaneous LE and BR/EDR, Host. */
#define BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   /**< LE Limited Discoverable Mode, BR/EDR not supported. */
#define BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   /**< LE General Discoverable Mode, BR/EDR not supported. */
/**@} */


/**@defgroup BLE_GAP_ADV_INTERVALS GAP Advertising interval max and min
 * @{ */
#define BLE_GAP_ADV_INTERVAL_MIN        0x0020 /**< Minimum Advertising interval in 625 us units, i.e. 20 ms. */
#define BLE_GAP_ADV_NONCON_INTERVAL_MIN 0x00A0 /**< Minimum Advertising interval in 625 us units for non connectable mode, i.e. 100 ms. */
#define BLE_GAP_ADV_INTERVAL_MAX        0x4000 /**< Maximum Advertising interval in 625 us units, i.e. 10.24 s. */
 /**@}  */


/**@brief Maximum size of advertising data in octets. */
#define  BLE_GAP_ADV_MAX_SIZE       31


/**@defgroup BLE_GAP_ADV_TYPES GAP Advertising types
 * @{ */
#define BLE_GAP_ADV_TYPE_ADV_IND          0x00   /**< Connectable undirected. */
#define BLE_GAP_ADV_TYPE_ADV_DIRECT_IND   0x01   /**< Connectable directed. */
#define BLE_GAP_ADV_TYPE_ADV_SCAN_IND     0x02   /**< Scannable undirected. */
#define BLE_GAP_ADV_TYPE_ADV_NONCONN_IND  0x03   /**< Non connectable undirected. */
/**@} */


/**@defgroup BLE_GAP_ADV_FILTER_POLICIES GAP Advertising filter policies
 * @{ */
#define BLE_GAP_ADV_FP_ANY                0x00   /**< Allow scan requests and connect requests from any device. */
#define BLE_GAP_ADV_FP_FILTER_SCANREQ     0x01   /**< Filter scan requests with whitelist. */
#define BLE_GAP_ADV_FP_FILTER_CONNREQ     0x02   /**< Filter connect requests with whitelist. */
#define BLE_GAP_ADV_FP_FILTER_BOTH        0x03   /**< Filter both scan and connect requests with whitelist. */
/**@} */


/**@defgroup BLE_GAP_ADV_TIMEOUT_VALUES GAP Advertising timeout values
 * @{ */
#define BLE_GAP_ADV_TIMEOUT_LIMITED_MAX      180 /**< Maximum advertising time in limited discoverable mode (TGAP(lim_adv_timeout) = 180s in spec (Addendum 2)). */
#define BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED  0 /**< Unlimited advertising in general discoverable mode. */
/**@} */


/**@defgroup BLE_GAP_DISC_MODES GAP Discovery modes
 * @{ */
#define BLE_GAP_DISC_MODE_NOT_DISCOVERABLE  0x00   /**< Not discoverable discovery Mode. */
#define BLE_GAP_DISC_MODE_LIMITED           0x01   /**< Limited Discovery Mode. */
#define BLE_GAP_DISC_MODE_GENERAL           0x02   /**< General Discovery Mode. */
/**@} */

/**@defgroup BLE_GAP_IO_CAPS GAP IO Capabilities
 * @{ */
#define BLE_GAP_IO_CAPS_DISPLAY_ONLY      0x00   /**< Display Only. */
#define BLE_GAP_IO_CAPS_DISPLAY_YESNO     0x01   /**< Display and Yes/No entry. */
#define BLE_GAP_IO_CAPS_KEYBOARD_ONLY     0x02   /**< Keyboard Only. */
#define BLE_GAP_IO_CAPS_NONE              0x03   /**< No I/O capabilities. */
#define BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY  0x04   /**< Keyboard and Display. */
/**@} */


/**@defgroup BLE_GAP_AUTH_KEY_TYPES GAP Authentication Key Types
 * @{ */
#define BLE_GAP_AUTH_KEY_TYPE_NONE        0x00   /**< No key (may be used to reject). */
#define BLE_GAP_AUTH_KEY_TYPE_PASSKEY     0x01   /**< 6-digit Passkey. */
#define BLE_GAP_AUTH_KEY_TYPE_OOB         0x02   /**< Out Of Band data. */
/**@} */

/**@defgroup BLE_GAP_SEC_STATUS GAP Security status
 * @{ */
#define BLE_GAP_SEC_STATUS_SUCCESS                0x00  /**< Successful parameters. */
#define BLE_GAP_SEC_STATUS_TIMEOUT                0x01  /**< Procedure timed out. */
#define BLE_GAP_SEC_STATUS_PDU_INVALID            0x02  /**< Invalid PDU received. */
#define BLE_GAP_SEC_STATUS_PASSKEY_ENTRY_FAILED   0x81  /**< Passkey entry failed (user cancelled or other). */
#define BLE_GAP_SEC_STATUS_OOB_NOT_AVAILABLE      0x82  /**< Out of Band Key not available. */
#define BLE_GAP_SEC_STATUS_AUTH_REQ               0x83  /**< Authentication requirements not met. */
#define BLE_GAP_SEC_STATUS_CONFIRM_VALUE          0x84  /**< Confirm value failed. */
#define BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP       0x85  /**< Pairing not supported.  */
#define BLE_GAP_SEC_STATUS_ENC_KEY_SIZE           0x86  /**< Encryption key size. */
#define BLE_GAP_SEC_STATUS_SMP_CMD_UNSUPPORTED    0x87  /**< Unsupported SMP command. */
#define BLE_GAP_SEC_STATUS_UNSPECIFIED            0x88  /**< Unspecified reason. */
#define BLE_GAP_SEC_STATUS_REPEATED_ATTEMPTS      0x89  /**< Too little time elapsed since last attempt. */
#define BLE_GAP_SEC_STATUS_INVALID_PARAMS         0x8A  /**< Invalid parameters. */
/**@} */

/**@defgroup BLE_GAP_SEC_STATUS_SOURCES GAP Security status sources
 * @{ */
#define BLE_GAP_SEC_STATUS_SOURCE_LOCAL           0x00  /**< Local failure. */
#define BLE_GAP_SEC_STATUS_SOURCE_REMOTE          0x01  /**< Remote failure. */
/**@} */

/**@defgroup BLE_GAP_CP_LIMITS GAP Connection Parameters Limits
 * @{ */
#define BLE_GAP_CP_MIN_CONN_INTVL_NONE           0xFFFF  /**< No new minimum connction interval specified in connect parameters. */
#define BLE_GAP_CP_MIN_CONN_INTVL_MIN            0x0006  /**< Lowest mimimum connection interval permitted, in units of 1.25 ms, i.e. 7.5 ms. */
#define BLE_GAP_CP_MIN_CONN_INTVL_MAX            0x0C80  /**< Highest minimum connection interval permitted, in units of 1.25 ms, i.e. 4 s. */
#define BLE_GAP_CP_MAX_CONN_INTVL_NONE           0xFFFF  /**< No new maximum connction interval specified in connect parameters. */
#define BLE_GAP_CP_MAX_CONN_INTVL_MIN            0x0006  /**< Lowest maximum connection interval permitted, in units of 1.25 ms, i.e. 7.5 ms. */
#define BLE_GAP_CP_MAX_CONN_INTVL_MAX            0x0C80  /**< Highest maximum connection interval permitted, in units of 1.25 ms, i.e. 4 s. */
#define BLE_GAP_CP_SLAVE_LATENCY_MAX             0x03E8  /**< Highest slave latency permitted, in connection events. */
#define BLE_GAP_CP_CONN_SUP_TIMEOUT_NONE         0xFFFF  /**< No new supervision timeout specified in connect parameters. */
#define BLE_GAP_CP_CONN_SUP_TIMEOUT_MIN          0x000A  /**< Lowest supervision timeout permitted, in units of 10 ms, i.e. 100 ms. */
#define BLE_GAP_CP_CONN_SUP_TIMEOUT_MAX          0x0C80  /**< Highest supervision timeout permitted, in units of 10 ms, i.e. 32 s. */
/**@} */


/**@brief GAP device name maximum length. */
#define BLE_GAP_DEVNAME_MAX_LEN           31


/**@defgroup BLE_GAP_CONN_SEC_MODE_SET_MACROS GAP attribute security requirement setters
 *
 * See @ref ble_gap_conn_sec_mode_t.
 * @{ */
/**@brief Set sec_mode pointed to by ptr to have no access rights.*/
#define BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(ptr)         do {(ptr)->sm = 0; (ptr)->lv = 0;} while(0)
/**@brief Set sec_mode pointed to by ptr to require no protection, open link.*/
#define BLE_GAP_CONN_SEC_MODE_SET_OPEN(ptr)              do {(ptr)->sm = 1; (ptr)->lv = 1;} while(0)
/**@brief Set sec_mode pointed to by ptr to require encryption, but no MITM protection.*/
#define BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(ptr)       do {(ptr)->sm = 1; (ptr)->lv = 2;} while(0)
/**@brief Set sec_mode pointed to by ptr to require encryption and MITM protection.*/
#define BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(ptr)     do {(ptr)->sm = 1; (ptr)->lv = 3;} while(0)
/**@brief Set sec_mode pointed to by ptr to require signing or encryption, no MITM protection needed.*/
#define BLE_GAP_CONN_SEC_MODE_SET_SIGNED_NO_MITM(ptr)    do {(ptr)->sm = 2; (ptr)->lv = 1;} while(0)
/**@brief Set sec_mode pointed to by ptr to require signing or encryption with MITM protection.*/
#define BLE_GAP_CONN_SEC_MODE_SET_SIGNED_WITH_MITM(ptr)  do {(ptr)->sm = 2; (ptr)->lv = 2;} while(0)
/**@} */


/**@brief GAP Security Key Length. */
#define BLE_GAP_SEC_KEY_LEN 16

/**@brief GAP Passkey Length. */
#define BLE_GAP_PASSKEY_LEN 6

/**@brief Maximum amount of addresses in a whitelist. */
#define BLE_GAP_WHITELIST_ADDR_MAX_COUNT (8)

/**@brief Maximum amount of IRKs in a whitelist.
 * @note  The number of IRKs is limited to 8, even if the hardware supports more.
 */
#define BLE_GAP_WHITELIST_IRK_MAX_COUNT (8)

/**@defgroup GAP_SEC_MODES GAP Security Modes
 * @{ */
#define BLE_GAP_SEC_MODE 0x00 /**< No key (may be used to reject). */
/**@} */

/**@} */

/**@addtogroup BLE_GAP_STRUCTURES Structures
 * @{ */

/**@brief Bluetooth Low Energy address. */
typedef struct
{
  uint8_t addr_type;                    /**< See @ref BLE_GAP_ADDR_TYPES. */
  uint8_t addr[BLE_GAP_ADDR_LEN];       /**< 48-bit address, LSB format. */
} ble_gap_addr_t;


/**@brief GAP connection parameters.
 *
 * @note  When ble_conn_params_t is received in an event, both min_conn_interval and
 *        max_conn_interval will be equal to the connection interval set by the central.
 */
typedef struct
{
  uint16_t min_conn_interval;         /**< Minimum Connection Interval in 1.25 ms units, see @ref BLE_GAP_CP_LIMITS.*/
  uint16_t max_conn_interval;         /**< Maximum Connection Interval in 1.25 ms units, see @ref BLE_GAP_CP_LIMITS.*/
  uint16_t slave_latency;             /**< Slave Latency in number of connection events, see @ref BLE_GAP_CP_LIMITS.*/
  uint16_t conn_sup_timeout;          /**< Connection Supervision Timeout in 10 ms units, see @ref BLE_GAP_CP_LIMITS.*/
} ble_gap_conn_params_t;


/**@brief GAP link requirements.
 *
 * See Bluetooth Core specification, Volume 3 Part C 10.2 for details.
 *
 * Security Mode 0 Level 0: No access permissions at all (this level is not defined by the Bluetooth Core specification).\n
 * Security Mode 1 Level 1: No security is needed (aka open link).\n
 * Security Mode 1 Level 2: Encrypted link required, MITM protection not necessary.\n
 * Security Mode 1 Level 3: MITM protected encrypted link required.\n
 * Security Mode 2 Level 1: Signing or encryption required, MITM protection not necessary.\n
 * Security Mode 2 Level 2: MITM protected signing required, unless link is MITM protected encrypted.\n
 */
typedef struct
{
  uint8_t sm : 4;                     /**< Security Mode (1 or 2), 0 for no permissions at all. */
  uint8_t lv : 4;                     /**< Level (1, 2 or 3), 0 for no permissions at all. */

} ble_gap_conn_sec_mode_t;


/**@brief GAP connection security status.*/
typedef struct
{
  ble_gap_conn_sec_mode_t sec_mode;           /**< Currently active security mode for this connection.*/
  uint8_t                 encr_key_size;      /**< Length of currently active encryption key, 7 to 16 octets (only applicable for bonding procedures). */
} ble_gap_conn_sec_t;


/**@brief Identity Resolving Key. */
typedef struct
{
  uint8_t irk[BLE_GAP_SEC_KEY_LEN];   /**< Array containing IRK. */
} ble_gap_irk_t;


/**@brief Whitelist structure. */
typedef struct
{
  ble_gap_addr_t   ** pp_addrs;        /**< Pointer to array of device address pointers, pointing to addresses to be used in whitelist. NULL if none are given. */
  uint8_t             addr_count;      /**< Count of device addresses in array, up to @ref BLE_GAP_WHITELIST_ADDR_MAX_COUNT. */
  ble_gap_irk_t    ** pp_irks;         /**< Pointer to array of Identity Resolving Key (IRK) pointers, each pointing to an IRK in the whitelist. NULL if none are given. */
  uint8_t             irk_count;       /**< Count of IRKs in array, up to @ref BLE_GAP_WHITELIST_IRK_MAX_COUNT. */
} ble_gap_whitelist_t;


/**@brief GAP advertising parameters.*/
typedef struct
{
  uint8_t               type;                 /**< See @ref BLE_GAP_ADV_TYPES. */
  ble_gap_addr_t*       p_peer_addr;          /**< For BLE_GAP_CONN_MODE_DIRECTED mode only, known peer address. */
  uint8_t               fp;                   /**< Filter Policy, see @ref BLE_GAP_ADV_FILTER_POLICIES. */
  ble_gap_whitelist_t * p_whitelist;          /**< Pointer to whitelist, NULL if none is given. */
  uint16_t              interval;             /**< Advertising interval between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s), see @ref BLE_GAP_ADV_INTERVALS. This parameter must be set to 0 if type equals @ref BLE_GAP_ADV_TYPE_ADV_DIRECT_IND. */
  uint16_t              timeout;              /**< Advertising timeout between 0x0001 and 0x3FFF in seconds, 0x0000 disables timeout. See also @ref BLE_GAP_ADV_TIMEOUT_VALUES. This parameter must be set to 0 if type equals @ref BLE_GAP_ADV_TYPE_ADV_DIRECT_IND. */
} ble_gap_adv_params_t;


/**@brief GAP scanning parameters. */
typedef struct
{
  uint8_t    filter;                    /**< Filter based on discovery mode, see @ref BLE_GAP_DISC_MODES. */
  uint8_t    active    : 1;             /**< If 1, perform active scanning (scan requests). */
  uint8_t    selective : 1;             /**< If 1, ignore unknown devices (non whitelisted). */
  uint16_t   interval;                  /**< Scan interval between 0x0020 and 0x4000 in 0.625ms units (20ms to 10.24s). */
  uint16_t   window;                    /**< Scan window between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s). */
  uint16_t   timeout;                   /**< Scan timeout between 0x0001 and 0x3FFF in seconds, 0x0000 disables timeout. */
} ble_gap_scan_params_t;


/**@brief GAP security parameters. */
typedef struct
{
  uint16_t   timeout;                   /**< Timeout for SMP transactions or Security Request in seconds, see @ref sd_ble_gap_authenticate and @ref sd_ble_gap_sec_params_reply for more information. */
  uint8_t    bond    : 1;               /**< Perform bonding. */
  uint8_t    mitm    : 1;               /**< Man In The Middle protection required. */
  uint8_t    io_caps : 3;               /**< IO capabilities, see @ref BLE_GAP_IO_CAPS. */
  uint8_t    oob     : 1;               /**< Out Of Band data available. */
  uint8_t    min_key_size;              /**< Minimum encryption key size in octets between 7 and 16. */
  uint8_t    max_key_size;              /**< Maximum encryption key size in octets between min_key_size and 16. */
} ble_gap_sec_params_t;


/**@brief GAP Encryption Information. */
typedef struct
{
  uint16_t  div;                        /**< Encryption Diversifier. */
  uint8_t   ltk[BLE_GAP_SEC_KEY_LEN];   /**< Long Term Key. */
  uint8_t   auth : 1;                   /**< Authenticated Key. */
  uint8_t   ltk_len : 7;                /**< LTK length in octets. */
} ble_gap_enc_info_t;


/**@brief GAP Master Identification. */
typedef struct
{
  uint16_t  ediv;                       /**< Encrypted Diversifier. */
  uint8_t   rand[8];                    /**< Random Number. */
} ble_gap_master_id_t;


/**@brief GAP Identity Information. */
typedef struct
{
  ble_gap_addr_t  addr;                       /**< Bluetooth address to which this key applies. */
  uint8_t         irk[BLE_GAP_SEC_KEY_LEN];   /**< Identity Resolution Key. */
} ble_gap_id_info_t;


/**@brief GAP Signing Information. */
typedef struct
{
  uint8_t   csrk[BLE_GAP_SEC_KEY_LEN]; /* Connection Signature Resolving Key. */
} ble_gap_sign_info_t;


/**@brief GAP Event IDs.
 * Those IDs uniquely identify an event coming from the stack to the application.
 */
enum BLE_GAP_EVTS
{
  BLE_GAP_EVT_CONNECTED  = BLE_GAP_EVT_BASE,    /**< Connection established. */
  BLE_GAP_EVT_DISCONNECTED,                     /**< Disconnected from peer. */
  BLE_GAP_EVT_CONN_PARAM_UPDATE,                /**< Connection Parameters updated. */
  BLE_GAP_EVT_SEC_PARAMS_REQUEST,               /**< Request to provide security parameters. */
  BLE_GAP_EVT_SEC_INFO_REQUEST,                 /**< Request to provide security information. */
  BLE_GAP_EVT_PASSKEY_DISPLAY,                  /**< Request to display a passkey to the user. */
  BLE_GAP_EVT_AUTH_KEY_REQUEST,                 /**< Request to provide an authentication key. */
  BLE_GAP_EVT_AUTH_STATUS,                      /**< Authentication procedure completed with status. */
  BLE_GAP_EVT_CONN_SEC_UPDATE,                  /**< Connection security updated. */
  BLE_GAP_EVT_TIMEOUT,                          /**< Timeout expired. */
  BLE_GAP_EVT_RSSI_CHANGED,                     /**< Signal strength measurement report. */
};


/**
 * @brief GAP Option IDs.
 * IDs that uniquely identify a GAP option.
 */
enum BLE_GAP_OPTS
{
  BLE_GAP_OPT_LOCAL_CONN_LATENCY  = BLE_GAP_OPT_BASE,    /**< Local connection latency. */
  BLE_GAP_OPT_PASSKEY,                                   /**< Set passkey to be used during pairing. This option can be used to make the SoftDevice use an application provided passkey instead of generating a random passkey.*/
  BLE_GAP_OPT_PRIVACY,                                   /**< Set or get custom IRK or custom private address cycle interval. */
};
/**@} */


/**@brief Event data for connected event. */
typedef struct
{
  ble_gap_addr_t        peer_addr;              /**< Bluetooth address of the peer device. */
  uint8_t               irk_match :1;           /**< If 1, peer device's address resolved using an IRK. */
  uint8_t               irk_match_idx  :7;      /**< Index in IRK list where the address was matched. */
  ble_gap_conn_params_t conn_params;            /**< GAP Connection Parameters. */
} ble_gap_evt_connected_t;


/**@brief Event data for disconnected event. */
typedef struct
{
  uint8_t reason;                               /**< HCI error code. */
} ble_gap_evt_disconnected_t;


/**@brief Event data for connection parameter update event. */
typedef struct
{
  ble_gap_conn_params_t conn_params;            /**<  GAP Connection Parameters. */
} ble_gap_evt_conn_param_update_t;


/**@brief Event data for security parameters request event. */
typedef struct
{
  ble_gap_sec_params_t peer_params;             /**< Initiator Security Parameters. */
} ble_gap_evt_sec_params_request_t;


/**@brief Event data for security info request event. */
typedef struct
{
  ble_gap_addr_t peer_addr;                     /**< Bluetooth address of the peer device. */
  uint16_t       div;                           /**< Encryption diversifier for LTK lookup. */
  uint8_t        enc_info  : 1;                 /**< If 1, Encryption Information required. */
  uint8_t        id_info   : 1;                 /**< If 1, Identity Information required. */
  uint8_t        sign_info : 1;                 /**< If 1, Signing Information required. */
} ble_gap_evt_sec_info_request_t;


/**@brief Event data for passkey display event. */
typedef struct
{
  uint8_t passkey[BLE_GAP_PASSKEY_LEN];         /**< 6-digit passkey in ASCII ('0'-'9' digits only). */
} ble_gap_evt_passkey_display_t;


/**@brief Event data for authentication key request event. */
typedef struct
{
  uint8_t key_type;                             /**< See @ref BLE_GAP_AUTH_KEY_TYPES. */
} ble_gap_evt_auth_key_request_t;


/**@brief Security levels supported.
 * @note See Bluetooth Specification Version 4.1 Volume 3, Part C, Chapter 10.
*/
typedef struct
{
  uint8_t lv1 : 1;                              /**< If 1: Level 1 is supported. */
  uint8_t lv2 : 1;                              /**< If 1: Level 2 is supported. */
  uint8_t lv3 : 1;                              /**< If 1: Level 3 is supported. */
} ble_gap_sec_levels_t;


/**@brief Keys that have been exchanged. */
typedef struct
{
  uint8_t ltk       : 1;                        /**< Long Term Key. */
  uint8_t ediv_rand : 1;                        /**< Encrypted Diversifier and Random value. */
  uint8_t irk       : 1;                        /**< Identity Resolving Key. */
  uint8_t address   : 1;                        /**< Public or static random address. */
  uint8_t csrk      : 1;                        /**< Connection Signature Resolving Key. */
} ble_gap_sec_keys_t;


/**@brief Event data for authentication status event. */
typedef struct
{
  uint8_t               auth_status;            /**< Authentication status, see @ref BLE_GAP_SEC_STATUS. */
  uint8_t               error_src;              /**< On error, source that caused the failure, see @ref BLE_GAP_SEC_STATUS_SOURCES. */
  ble_gap_sec_levels_t  sm1_levels;             /**< Levels supported in Security Mode 1. */
  ble_gap_sec_levels_t  sm2_levels;             /**< Levels supported in Security Mode 2. */
  ble_gap_sec_keys_t    periph_kex;             /**< Bitmap stating which keys were exchanged (distributed) by the peripheral. */
  ble_gap_sec_keys_t    central_kex;            /**< Bitmap stating which keys were exchanged (distributed) by the central. */
  struct periph_keys_t
  {
    ble_gap_enc_info_t    enc_info;             /**< Peripheral's Encryption information. */
  } periph_keys;                                /**< Actual keys distributed from the Peripheral to the Central. */ 
  struct central_keys_t
  {
    ble_gap_irk_t         irk;                  /**< Central's IRK. */
    ble_gap_addr_t        id_info;              /**< Central's Identity Info. */
  } central_keys;                               /**< Actual keys distributed from the Central to the Peripheral. */
} ble_gap_evt_auth_status_t;


/**@brief Event data for connection security update event. */
typedef struct
{
  ble_gap_conn_sec_t conn_sec;                  /**< Connection security level. */
} ble_gap_evt_conn_sec_update_t;


/**@brief Event data for timeout event. */
typedef struct
{
  uint8_t src;                                  /**< Source of timeout event, see @ref BLE_GAP_TIMEOUT_SOURCES. */
} ble_gap_evt_timeout_t;


/**@brief Event data for advertisement report event. */
typedef struct
{
  int8_t  rssi;                               /**< Received Signal Strength Indication in dBm. */
} ble_gap_evt_rssi_changed_t;


/**@brief GAP event callback event structure. */
typedef struct
{
  uint16_t conn_handle;                                     /**< Connection Handle on which event occured. */
  union                                                     /**< union alternative identified by evt_id in enclosing struct. */
  {
    ble_gap_evt_connected_t          connected;             /**< Connected Event Parameters. */
    ble_gap_evt_disconnected_t       disconnected;          /**< Disconnected Event Parameters. */
    ble_gap_evt_conn_param_update_t  conn_param_update;     /**< Connection Parameter Update Parameters. */
    ble_gap_evt_sec_params_request_t sec_params_request;    /**< Security Parameters Request Event Parameters. */
    ble_gap_evt_sec_info_request_t   sec_info_request;      /**< Security Information Request Event Parameters. */
    ble_gap_evt_passkey_display_t    passkey_display;       /**< Passkey Display Event Parameters. */
    ble_gap_evt_auth_key_request_t   auth_key_request;      /**< Authentication Key Request Event Parameters. */
    ble_gap_evt_auth_status_t        auth_status;           /**< Authentication Status Event Parameters. */
    ble_gap_evt_conn_sec_update_t    conn_sec_update;       /**< Connection Security Update Event Parameters. */
    ble_gap_evt_timeout_t            timeout;               /**< Timeout Event Parameters. */
    ble_gap_evt_rssi_changed_t       rssi_changed;          /**< RSSI Event parameters. */
  } params;

} ble_gap_evt_t;


/**@brief Local connection latency option.
 *
 *         Local connection latency is a feature which enables the slave to improve
 *         current consumption by ignoring the slave latency set by the peer. The
 *         local connection latency can only be set to a multiple of the slave latency,
 *         and cannot be longer than half of the supervision timeout.
 *
 *         Used with @ref sd_ble_opt_set to set the local connection latency. The
 *         @ref sd_ble_opt_get is not supported for this option, but the actual 
 *         local connection latency (unless set to NULL) is set as a return parameter
 *         when setting the option.
 *
 *  @note  The latency set will be truncated down to the closest slave latency event
 *         multiple, or the nearest multiple before half of the supervision timeout.
 *
 *  @note  The local connection latency is default off, and needs to be set for new
 *         connections and whenever the connection is updated.
 *
 *  @retval ::NRF_SUCCESS Set successfully.
 *  @retval ::NRF_ERROR_NOT_SUPPORTED Get is not supported.
 *  @retval ::BLE_ERROR_INVALID_CONN_HANDLE Invalid connection handle parameter.
 */
typedef struct
{
  uint16_t   conn_handle;                       /**< Connection Handle */
  uint16_t   requested_latency;                 /**< Requested local connection latency. */
  uint16_t * p_actual_latency;                  /**< Pointer to storage for the actual local connection latency (can be set to NULL to skip return value). */
} ble_gap_opt_local_conn_latency_t;


/**@brief Passkey Option.
 *
 *        Structure containing the passkey to be used during pairing. This can be used with @ref
 *        sd_ble_opt_set to make the SoftDevice use a pre-programmed passkey for authentication
 *        instead of generating a random one.
 *
 * @note  @ref sd_ble_opt_get is not supported for this option.
 *
 */
typedef struct
{
  uint8_t * p_passkey;                          /**< Pointer to 6-digit ASCII string (digit 0..9 only, no NULL termination) passkey to be used during pairing. If this is NULL, the SoftDevice will generate a random passkey if required.*/
} ble_gap_opt_passkey_t;


/**@brief Custom Privacy Options.
 *
 * @note The specified address cycle interval is used when the address cycle mode is
 * @ref BLE_GAP_ADDR_CYCLE_MODE_AUTO. If 0 is given, the address will not be refreshed at any
 * interval, and not at start of advertising. A new address can be generated manually by calling
 * @ref sd_ble_gap_address_set with the same type again. The default interval is
 * @ref BLE_GAP_DEFAULT_PRIVATE_ADDR_CYCLE_INTERVAL_S.
 *
 * @note If cycle mode is @ref BLE_GAP_ADDR_CYCLE_MODE_AUTO, the address will immediately be
 * refreshed when this option is set.
 */
typedef struct
{
  ble_gap_irk_t * p_irk;        /**< When input: Pointer to custom IRK, or NULL to use/reset to the device's default IRK. When output: Pointer to where the current IRK is to be stored, or NULL to not read out the IRK. */
  uint16_t        interval_s;   /**< When input: Custom private address cycle interval in seconds. When output: The current private address cycle interval. */
} ble_gap_opt_privacy_t;


/**@brief Option structure for GAP options. */
typedef union
{
  ble_gap_opt_local_conn_latency_t local_conn_latency;  /**< Local connection latency. */
  ble_gap_opt_passkey_t            passkey;             /**< Passkey to be used for pairing.*/
  ble_gap_opt_privacy_t            privacy;             /**< Custom privacy options. */
} ble_gap_opt_t;
/**@} */

#endif // BLE_GAP_H__

/**
  @}
*/
