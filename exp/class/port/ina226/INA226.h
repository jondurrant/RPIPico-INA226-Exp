/*
 * INA226.h
 *
 *  Created on: 5 Feb 2026
 *      Author: jondurrant
 */

#ifndef EXP_BASIC_PORT_INA226_INA226_H_
#define EXP_BASIC_PORT_INA226_INA226_H_

#include "driver_ina226.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

class INA226 {
public:
	INA226(i2c_inst_t * i2c, ina226_address_t addr, float ohms);
	virtual ~INA226();

	bool get(float *mV, float *mA, float *mW);

	bool isError();

private:
	bool  init(ina226_address_t addr_pin, double r);


	i2c_inst_t * pI2c;
	ina226_address_t xAddr;
	ina226_handle_t xHandle;

	bool xOK = true;

};

#endif /* EXP_BASIC_PORT_INA226_INA226_H_ */
