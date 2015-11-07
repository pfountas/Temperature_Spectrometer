/* TMP102.cpp
 *
 * Author: Petros Fountas
 * Created on Fri 28 Nov 2014
 *
 * Last modified on Fri 28 Nov 2014
 *
 * Copyright by Petros Fountas. All rights reserved.
 */
#include "TMP102.h"

// addresses for ADD0 connected to GND
//#define TMP102_ADD 	0x48
//#define TMP102_R_ADD 	0x91
//#define TMP102_W_ADD 	0x90

// register addresses
#define TEMP_REG 	0x00
#define CONFIG_REG 	0x01
#define THIGH_REG 	0x02
#define TLOW_REG 	0x03

TMP102::TMP102(int address, PinName sda, PinName scl) {

	this->device = new I2C(sda,scl);
	this->address = (unsigned char)address;
	this->wradd = (this->address << 1);
	this->rdadd = (this->wradd |= 1);
}

TMP102::~TMP102() {
	delete (this->device);
}

// Get temperature
int TMP102::temp(float *temp) {

	int ack; // used to store acknowledgement bit
	char data[2]; // array for data
	char reg = TEMP_REG; // temperature register address

	// send temperature register address
	ack = this->device->write(this->wradd, &reg, 1);
	if (ack)
		return 100; // if we don't receive acknowledgement, return error code

	// read 2 bytes from temperature register and store in array
	ack = this->device->read(this->rdadd, data, 2);
	if (ack)
		return 101; // if we don't receive acknowledgement, return error code

	int temperature = (data[0] << 4) | (data[1] >> 4);
	*temp = temperature * 0.0625;

	return 0;
}

int TMP102::init(int rate) {

	this->device->frequency(400000); // set bus speed to 400 kHz

	int ack; // used to store acknowledgement bit
	char data[2]; // array for data
	char reg = CONFIG_REG; // register address

	//////// Read current status of configuration register ///////

	 // send the slave write address and the configuration register address
	ack = this->device->write(this->wradd, &reg, 1);
	if (ack)
		return 100; // if we don't receive acknowledgement, return error code

	// read default 2 bytes from configuration register and store in buffer
	ack = this->device->read(this->rdadd, data, 2);
	if (ack)
		return 101; // if we don't receive acknowledgement, return error code

	///////// Configure the register //////////

	switch (rate) {
	case 0: // set conversion rate to 0.25 Hz
		data[1] &= ~(1 << 6); // set bit 6
		data[1] &= ~(1 << 7); // set bit 7
		break;

	case 1: // set conversion rate to 1 Hz
		data[1] |= (1 << 6); // set bit 6
		data[1] &= ~(1 << 7); // set bit 7
		break;

	case 2: // set conversion rate to 4 Hz
		data[1] &= ~(1 << 6); // set bit 6
		data[1] |= (1 << 7); // set bit 7
		break;

	case 3: // set conversion rate to 8 Hz
		data[1] |= (1 << 6); // set bit 6
		data[1] |= (1 << 7); // set bit 7
		break;

	default:  // set conversion rate to 4 Hz (default)
		data[1] &= ~(1 << 6); // set bit 6
		data[1] |= (1 << 7); // set bit 7
		break;
	}
	//////// Send the configured register to the slave ////////////

	// send the slave write address and the configuration register address
	ack = this->device->write(this->wradd, &reg, 1);
	if (ack)
		return 110; // if we don't receive acknowledgement, return error code

	// send 2 data bytes to the configuration register
	ack = this->device->write(this->wradd, data, 2);
	if (ack)
		return 111; // if we don't receive acknowledgement, return error code

	return 0;
}
