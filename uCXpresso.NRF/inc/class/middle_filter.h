/*
 ===============================================================================
 Name        : CMiddleFilter.h
 Author      : jason
 Version     : v1.0.0
 Date		 : 2016年12月23日
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : TODO
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2016年12月23日	v1.0.0	First Edition									Jason
 ===============================================================================
 */

#ifndef CLASS_MIDDLE_FILTER_H_
#define CLASS_MIDDLE_FILTER_H_

#include <class/object.h>

class CMiddleFilter: public CObject {
public:
	/**
	 * @brief Construct, to set the number of sample size to filter.
	 */
	CMiddleFilter(uint8_t size);

	/**
	 * @brief input no-filter value , output filter value.
	 */
	float update(float value);

	virtual ~CMiddleFilter();
protected:
	float	*m_buffer, *m_sort;
	uint8_t	 m_size;
	uint8_t	 m_middle;
	uint8_t	 m_index;
};

#endif /* CLASS_MIDDLE_FILTER_H_ */
