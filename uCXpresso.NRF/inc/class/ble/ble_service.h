/*
 * ble_service.h
 *
 *  Created on: Aug 5, 2014
 *      Author: Jason
 */

#ifndef BLE_SERVICE_H_
#define BLE_SERVICE_H_

#include <class/ble/ble_base.h>

class bleService: virtual public bleBase {
public:
	bleService(bleBase &ble);

	/** @brief Check this service is available for access
	 * @return true if service available, false otherwise.
	 */
	virtual inline bool isAvailable() { return true; }

	//
	/// @cond PRIVATE
	//
	virtual void on_ble_event(xHandle evt) = PURE_VIRTUAL_FUNC;
	~bleService();
protected:
	bleBase	*m_p_ble;
	/// @endcond
};

#endif /* BLE_SERVICE_H_ */
