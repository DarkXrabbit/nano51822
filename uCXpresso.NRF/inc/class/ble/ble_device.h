/*
 ===============================================================================
 Name        : ble_device.h
 Author      : uCXpresso
 Version     : v1.0.3
 Date		 : 2014/11/7
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : BLE SoftDevice driver (S110) class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/1	v1.0.0	First Edition for nano51822						Jason
 2014/10/22 v1.0.1	Add information() member to provide "Device		Jason
 	 	 	 	 	Information Service".
 2014/11/3	v1.0.2	Add address() member to retrieve the BLE addr.	Jason
 2014/11/7	v1.0.3	Add wait() member to wait for connected.		Jason
 ===============================================================================
 */

#ifndef BLE_DEVICE_H_
#define BLE_DEVICE_H_

#include <class/thread.h>
#include <class/semaphore.h>
#include <class/peripheral.h>
#include <class/list.h>
#include <class/timeout.h>

#include <class/ble/ble_service.h>
#include <class/ble/ble_advertising.h>
#include <class/ble/ble_gap.h>
#include <class/ble/nrf51/ble_dis.h>

/**@brief Possible lfclk oscillator sources.
 * @ingroup Enumerations
*/
typedef enum
{
  NRF_LFCLKSRC_SYNTH_250_PPM,                       /**< LFCLK Synthesized from HFCLK.                    */
  NRF_LFCLKSRC_XTAL_500_PPM,                        /**< LFCLK crystal oscillator 500 PPM accuracy.       */
  NRF_LFCLKSRC_XTAL_250_PPM,                        /**< LFCLK crystal oscillator 250 PPM accuracy.       */
  NRF_LFCLKSRC_XTAL_150_PPM,                        /**< LFCLK crystal oscillator 150 PPM accuracy.       */
  NRF_LFCLKSRC_XTAL_100_PPM,                        /**< LFCLK crystal oscillator 100 PPM accuracy.       */
  NRF_LFCLKSRC_XTAL_75_PPM,                         /**< LFCLK crystal oscillator 75 PPM accuracy.        */
  NRF_LFCLKSRC_XTAL_50_PPM,                         /**< LFCLK crystal oscillator 50 PPM accuracy.        */
  NRF_LFCLKSRC_XTAL_30_PPM,                         /**< LFCLK crystal oscillator 30 PPM accuracy.        */
  NRF_LFCLKSRC_XTAL_20_PPM,                         /**< LFCLK crystal oscillator 20 PPM accuracy.        */
  NRF_LFCLKSRC_RC_250_PPM_250MS_CALIBRATION,        /**< LFCLK RC oscillator, 250ms  calibration interval.*/
  NRF_LFCLKSRC_RC_250_PPM_500MS_CALIBRATION,        /**< LFCLK RC oscillator, 500ms  calibration interval.*/
  NRF_LFCLKSRC_RC_250_PPM_1000MS_CALIBRATION,       /**< LFCLK RC oscillator, 1000ms calibration interval.*/
  NRF_LFCLKSRC_RC_250_PPM_2000MS_CALIBRATION,       /**< LFCLK RC oscillator, 2000ms calibration interval.*/
  NRF_LFCLKSRC_RC_250_PPM_4000MS_CALIBRATION,       /**< LFCLK RC oscillator, 4000ms calibration interval.*/
  NRF_LFCLKSRC_RC_250_PPM_8000MS_CALIBRATION,       /**< LFCLK RC oscillator, 8000ms calibration interval.*/
  NRF_LFCLKSRC_RC_250_PPM_TEMP_1000MS_CALIBRATION,  /**< LFCLK RC oscillator. Temperature checked every 1000ms, if changed above a threshold, a calibration is done.*/
  NRF_LFCLKSRC_RC_250_PPM_TEMP_2000MS_CALIBRATION,  /**< LFCLK RC oscillator. Temperature checked every 2000ms, if changed above a threshold, a calibration is done.*/
  NRF_LFCLKSRC_RC_250_PPM_TEMP_4000MS_CALIBRATION,  /**< LFCLK RC oscillator. Temperature checked every 4000ms, if changed above a threshold, a calibration is done.*/
  NRF_LFCLKSRC_RC_250_PPM_TEMP_8000MS_CALIBRATION,  /**< LFCLK RC oscillator. Temperature checked every 8000ms, if changed above a threshold, a calibration is done.*/
  NRF_LFCLKSRC_RC_250_PPM_TEMP_16000MS_CALIBRATION, /**< LFCLK RC oscillator. Temperature checked every 16000ms, if changed above a threshold, a calibration is done.*/
}NRF_LFCLKSRC_T;

/**
 * @brief default the BLE SoftDevice Task stack size
 */
#ifndef DEF_BLE_DEVICE_STACK_SIZE
#define DEF_BLE_DEVICE_STACK_SIZE	72
#endif

/**
 * @brief 	BLE Device Class (SoftDevice).
 * @class 	bleDevice ble_device.h "class/ble/ble_device.h"
 *
 * @details This class manages the all BLE event from the SoftDevice driver,
 * 			and provides the device-manager, advertising and gap objects.
 *
 * @ingroup Bluetooth
 */
class bleDevice : public bleBase, public CThread{
public:
	/**
	 * @brief Static function, to initialize the SoftDevice driver.
	 *
	 * @param lfclksrc Low Frequency Crystal source (32.768KHz)
	 *
	 * @note Recommend to use the external 32.768KHz crystal for low power features.
	 *
	 * @warning For tickless, please select the @ref NRF_LFCLKSRC_XTAL_20_PPM accurate crystal.
	 */
	static void Init(NRF_LFCLKSRC_T lfclksrc=NRF_LFCLKSRC_RC_250_PPM_250MS_CALIBRATION);

	/**
	 * @brief BLE softdevice constructor.
	 */
	bleDevice();

	/**@brief Enable the BLE stack (device).
	 *
	 * @param clearAllBoundedCentrals Set to true in case the module should clear all persistent data.
	 * @param stack Set the stack size for the BLE device task.
	 *
	 * @return @ref NRF_SUCCESS BLE stack has been enabled successfully
	 */
	uint32_t enable(uint32_t stack=DEF_BLE_DEVICE_STACK_SIZE);

	/**
	 * @brief Wait for connected.
	 * @param timeout Optional, to specify a timeout for waiting.
	 * @note The waiting member will push the task in to block state to wait the connected event.
	 */
	virtual bool wait(uint32_t timeout=MAX_DELAY_TIME);

	/**@brief Check BLE connection.
	 *
	 * @return true if ble is in connected, false otherwise.
	 */
	virtual bool isConnected();

	/**@brief A Connected Event.
	 *
	 * @details The onConnected will be called when a BLE connection created.
	 */
	virtual void onConnected();

	/**@brief A Disconnected Event.
	 *
	 * @details The onDisconnected will be called when a BLE connection destroy.
	 */
	virtual void onDisconnected();

	/**@brief A BLE stack error occurred.
	 */
	virtual void onError(uint32_t err_code);

	/**@brief A GAP timeout occurred.
	 */
	virtual void onTimeout();

	/**
	 * @brief Get SoftDevice driver version information.
	 *
	 * @param majorVer[out] Link Layer Version number for BT 4.1 spec is 7
	 * @param minorVer[out] Link Layer Sub Version number, corresponds to the SoftDevice Firmware ID (FWID).
	 *
	 * @return @ref NRF_SUCCESS  Version information stored successfully.
	 * @return @ref NRF_ERROR_INVALID_ADDR Invalid pointer supplied.
	 * @return @ref NRF_ERROR_BUSY The stack is busy (typically doing a locally-initiated disconnection procedure).
	 */
	static uint32_t sdVersion(uint8_t &majorVer, uint16_t &minorVer);

	/**
	 * @brief Function for initializing the Device Information Service.
	 *
	 * @details This call allows the application to initialize the device information service.
	 *          It adds the DIS service and DIS characteristics to the database, using the initial
	 *          values supplied through the p_dis_init parameter. Characteristics which are not to be
	 *          added, shall be set to NULL in p_dis_init.
	 *
	 * @param[in]   manufact_name	Manufacturer Name String.
	 * @param[in]	model_number	Model Number String.
	 * @param[in]	serial_number	Serial Number String.
	 * @param[in]	hw_rev			Hardware Reversion String.
	 * @param[in]	fw_rev			Firmware Reversion String.
	 * @param[in]	sw_rev			Software Reversion String.
	 * @param[in]	p_sys_id		Point to the ble_dis_sys_id_t.
	 * @param[in]	p_pnp_id		Point to the ble_dis_pnp_id_t.
	 *
	 * @return      NRF_SUCCESS on successful initialization of service.
	 */
	static uint32_t information(LPCTSTR manufact_name,
								LPCTSTR model_number,
								LPCTSTR serial_number,
								LPCTSTR hw_rev = NULL,
								LPCTSTR fw_rev = NULL,
								LPCTSTR sw_rev = NULL,
								ble_dis_sys_id_t *p_sys_id=NULL,
								ble_dis_pnp_id_t *p_pnp_id=NULL);
	/**
	 * @brief 48bits (6 bytes) device address;
	 */
	static uint8_t *address();

	/**@brief An advertising member object.
	 * @ref bleAdvertising class.
	 */
	bleAdvertising		m_advertising;

	/**@brief GAP member object.
	 * @ref bleGAP class.
	 */
	bleGAP				m_gap;

	//
	/// @cond PRIVATE
	//
	virtual ~bleDevice();
	void on_ble_event(ble_evt_t * p_ble_evt);
	void on_sys_event(uint32_t event);

	ble_evt_t 	*m_p_ble_evt;
	uint16_t    m_conn_handle;
	ble_gap_evt_auth_status_t m_auth_status;
	ble_gap_sec_params_t	  m_sec_params;
	CSemaphore	m_semBleEvent;
protected:
	CSemaphore	m_semWaitForConnected;
	bool		m_memory_access_in_progress;

	void system_off_mode_enter();

	//
	// for services
	//
	CList m_lstService;
	void add_service(bleService *service);
	void del_service(bleService *service);
	void services_evt(ble_evt_t * p_ble_evt);
	void services_poll();

	//
	// Implement CThread::run()
	//
	virtual void run();
//
// friend class for BLE services
//
friend class bleAdvertising;
friend class bleService;
	/// @endcond
};

extern bleDevice *gpBLE;	///< Point to the global bleDevice object.

/**\example /ble/ble_app_hrm_htm_bat_lilypad/src/main.cpp
 * This is an example of how to use the bleDevice class.
 * More details about this example.
 */

/**\example /ble/ble_app_hrm_htm_bat_lilypad/src/setup.cpp
 * This is an example of how to use the bleDevice::Init() member.
 * More details about this example.
 */

#endif /* BLE_DEVICE_H_ */
