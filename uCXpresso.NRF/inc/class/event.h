/*
 ===============================================================================
 Name        : event.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/2/21
 Description : Event Bit Group (A group = 32 bits)
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/2/21	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <class/object.h>

/**
 * @brief EventBit are used to indicate if an event has occurred or not.
 * @class CEventBit event.h "class/event.h"
 * @ingroup RTOS
 */
class CEventBit: public CObject {
public:

	virtual uint32_t set(uint32_t bits);
	virtual uint32_t clr(uint32_t bits);
	virtual uint32_t get(bool fromISR=false);

	virtual uint32_t wait(uint32_t bitsToWait,				// bitwise indicates bit or bits to wait
			      	  	  bool clearOnExit=true,			// auto clear all bits when return
			      	  	  bool waitForAll=false,			// wait for all bits
			      	  	  uint32_t timeout=MAX_DELAY_TIME);	// timeout when no bit event

	virtual uint32_t sync(uint32_t bitsToSet,
				  	  	  uint32_t bitsToWait,
				  	  	  uint32_t timeout=MAX_DELAY_TIME);

	virtual inline bool isValid() {
		return (m_event!=NULL);
	}

	/// @cond
	CEventBit();
	virtual ~CEventBit();

protected:
	xHandle	m_event;
	/// @endcond
};

#endif /* EVENT_H_ */
