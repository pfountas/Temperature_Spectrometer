/* TMP102.h
 *
 * Author: Petros Fountas
 * Created on Fri 28 Nov 2014
 *
 * Last modified on Fri 28 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#ifndef TMP102_TMP102_H_
#define TMP102_TMP102_H_

#include "mbed.h"

class TMP102 {
public:
	TMP102(int address, PinName sda, PinName scl);
	~TMP102();

	// initialise sensor
	int init(int rate);

	// write temperature to &temp
	int temp(float *temp);

private:
	// device address
	unsigned char address;
	unsigned char rdadd;
	unsigned char wradd;
	// device handler
	I2C *device;

};

#endif // TMP102_TMP102_H_
