/*
 ===============================================================================
 Name        : object.h
 Author      : uCXpresso
 Version     : v1.0.3
 Date		 : 2010/10/18
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Object Base Class
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2011/12/18	v1.0.0	First Edition									Jason
 2013/6/25	v1.0.1	remove onEvent() member function				Jason
 2013/7/5	v1.0.2	Add isThread() member function					Jason
 2010/10/18 v1.0.3	Add isValid() member function					Jason
 ===============================================================================
 */
#ifndef OBJECT_H_
#define OBJECT_H_

#include <uCXpresso.h>

/**Enumerator group define
 * \defgroup Enumerations
 */

/**Miscellaneous
 * \defgroup Miscellaneous
 */

/**CObject class is all classes base.
 * \class CObject object.h "class/object.h"
 * \ingroup Miscellaneous
 */
class CObject {
public:
	/**Check current object that inherits from CThread class or not.
	 * \note The isTherad() will be override by CThread class.
	 */
	virtual inline bool isThread() {
		return false;
	}

	virtual inline bool isValid() {
		return true;
	}

	/// @cond
	CObject();
	virtual ~CObject();
	/// @endcond
};

#endif /* OBJECT_H_ */
