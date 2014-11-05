/*
 ===============================================================================
 Name        : ble_conn_params.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/11/1
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Module for initiating and executing a connection parameters
 	 	 	   negotiation procedure.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/1	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef BLE_CONN_PARAMS_H_
#define BLE_CONN_PARAMS_H_

#include <class/ble/ble_device.h>

/**
 * @brief Default connection parameters
 */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  5000 	/**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   30000 	/**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3       /**< Number of attempts before giving up the connection parameter negotiation. */


/**
 * @brief 	Connection Parameters Class.
 * @class 	bleConnParams ble_conn_params.h "class/ble/ble_conn_params.h"
 *
 * @details Most use cases require what is referred to as Fast Connection Parameters
 * as soon as a connection is established in order to ensure that service discovery
 * and connection procedures happen quickly. However, continuing with these parameters
 * through out the connection may be unnecessary drain of battery since many applications require a less frequent data exchange.
 * Therefore, it is recommended that the peripheral applications request the master to update connection parameters.
 * The Connection parameters negotiation library of the SDK provides the functionality to do so.
 *
 * @ingroup Bluetooth
 */
class bleConnParams: public bleService {
public:
	/**@brief Construct the Connection Parameters module.
	 *
	 * @note If the negotiation procedure should be triggered when notification/indication of
	 *       any characteristic is enabled by the peer, then this bleConnParams must be created after
	 *       having initialized the services.
	 *
	 * @param[in]	ble					Point to the bleDevice object.
	 * @param[in]	first_update_delay	Time from initiating event to first time connection parameters updated. (in millisecond)
	 * @param[in]	next_update_delay	Time between each connection parameters updated. (in millisecond)
	 * @param[in]	max_update_count	Number of attempts before giving up the connection parameter negotiation.
	 */
	bleConnParams(bleDevice &ble,
			      uint16_t first_update_daley 	= FIRST_CONN_PARAMS_UPDATE_DELAY,
				  uint16_t next_update_delay 	= NEXT_CONN_PARAMS_UPDATE_DELAY,
				  uint16_t max_update_count 	= MAX_CONN_PARAMS_UPDATE_COUNT,
				  uint16_t start_on_notify_cccd_handle=BLE_GATT_HANDLE_INVALID);

	/**
	 * @brief Function for changing the current connection parameters to a new set.
	 *
	 *  @details Use this function to change the connection parameters to a new set of parameter
	 *       (ie different from the ones given at init of the module).
	 *       This function is usefull for scenario where most of the time the application
	 *       needs a relatively big connection interval, and just sometimes, for a temporary
	 *       period requires shorter connection interval, for example to transfer a higher
	 *       amount of data.
	 *       If the given parameters does not match the current connection's parameters
	 *       this function initiates a new negotiation.
	 *
	 * @param[in]   min_conn_interval	Minimum Connection Interval in millisecond units. (min. 8ms)
	 * @param[in]	max_conn_interval	Maximum Connection Interval in millisecond units.
	 * @param[in]	slave_latency		Slave Latency in number of connection events.
	 * @param[in]	conn_sup_timeout	Connection Supervision Timeout in millisecond units.
	 */
	uint32_t change(uint16_t min_conn_interval,
	  	  	  	    uint16_t max_conn_interval,
	  	  	  	    uint16_t slave_latency = 0,
	  	  	  	    uint16_t conn_sup_timeout = 4000 );

	/**
	 * @brief Stop connection parameter update negotiation.
	 */
	uint32_t stop();

	//
	///@cond PRIVATE
	//
	virtual ~bleConnParams();
	virtual inline uint16_t uuid() { return 0;}
protected:
	CTimeout	m_tmCP;
	virtual void on_ble_event(ble_evt_t *p_ble_evt);
	virtual void on_ble_poll();
	///@endcond
};

/**\example /ble/ble_app_hrm_htm_bat/src/main.cpp
 * This is an example of how to use the bleConnParams class.
 * More details about this example.
 */


#endif /* BLE_CONN_PARAMS_H_ */
