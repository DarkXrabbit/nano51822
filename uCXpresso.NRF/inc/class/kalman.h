/*
 ===============================================================================
 Name        : Kalman Filter
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/22
 Description : kalman filter
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/22	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef KALMAN_H_
#define KALMAN_H_

#include <class/object.h>

/**
 * @brief CKalman class provides Kalman Filter.
 * @class CKalman kalman.h "class/kalman.h"
 * @note The CKalman class can be used for the analog signal measurement.
 * @ingroup Miscellaneous
 */
class CKalman: public CObject {
public:
	/**
	 * @brief CKalman constructor.
	 *
	 * @param[in] p The error covariance.
	 * @param[in] q	The covariance of the process noise.
	 * @param[in] r	the covariance of the observation noise.
	 */
	CKalman(float p=10, float q=0.0001, float r=0.05f);

	/**
	 * @brief Call the filter member to covariance and filter the input value.
	 *
	 * @param[in] value	A float type input value.
	 *
	 * @return the filter result.
	 */
	virtual float filter(float value);

	//
	///@cond
	//
protected:
	float m_value;
	float m_p, m_q, m_r, m_kGain;
	///@endcond
};


/**\example /ble/ble_rssi_measure/src/main.cpp
 * This is an example of how to use the CKalman filter class.
 * More details about this example.
 */

#endif /* KALMAN_FILTER_H_ */
