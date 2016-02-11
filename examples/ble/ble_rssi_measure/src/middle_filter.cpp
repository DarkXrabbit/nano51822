/*
 * Author: Jason
 * Copyright 2015 Embeda Technology Inc.
 */

class middle_filter {
public:
	middle_filter() {
		reset();
	}

	int8_t filter(int8_t rssi) {
		if ( rssi>0 ) rssi -= 128;
		array[i++] = rssi;
		if ( i>=3 ) i=0;
		return middle();
	}

	void reset() {
		i = 0;
		array[0] = -100;
		array[1] = -100;
		array[2] = -100;
	}

protected:
	int	   i;
	int8_t array[3];

	int8_t middle(){
		if (array[0] > array[1]) {
		  if (array[1] > array[2]) {
		    return array[1];
		  } else if (array[0] > array[2]) {
		    return array[2];
		  } else {
		    return array[0];
		  }
		} else {
		  if (array[0] > array[2]) {
		    return array[0];
		  } else if (array[1] > array[2]) {
		    return array[2];
		  } else {
		    return array[1];
		  }
		}
	}
};
