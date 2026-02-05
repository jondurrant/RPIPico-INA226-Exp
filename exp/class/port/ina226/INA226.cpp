/*
 * INA226.cpp
 *
 *  Created on: 5 Feb 2026
 *      Author: jondurrant
 */

#include "INA226.h"
#include "driver_ina226_interface.h"

/**
 * @brief ina226 basic example default definition
 */
#define INA226_BASIC_DEFAULT_AVG_MODE                             INA226_AVG_16                        /**< 16 averages */
#define INA226_BASIC_DEFAULT_BUS_VOLTAGE_CONVERSION_TIME          INA226_CONVERSION_TIME_1P1_MS        /**< bus voltage conversion time 1.1 ms */
#define INA226_BASIC_DEFAULT_SHUNT_VOLTAGE_CONVERSION_TIME        INA226_CONVERSION_TIME_1P1_MS        /**< shunt voltage conversion time 1.1 ms */



INA226::INA226(i2c_inst_t * i2c, ina226_address_t addr, float ohms) {

	pI2c = i2c;
	xAddr = addr;
	ina226_interface_iic_channel(i2c);
	xOK = init( addr,  ohms);
}

INA226::~INA226() {
	//NOP
}

bool INA226::isError(){
	return !xOK;
}

bool INA226::init(ina226_address_t addr_pin, double r){
	uint8_t res;
	uint16_t calibration;

	/* link interface function */
	DRIVER_INA226_LINK_INIT(&xHandle, ina226_handle_t);
	DRIVER_INA226_LINK_IIC_INIT(&xHandle, ina226_interface_iic_init);
	DRIVER_INA226_LINK_IIC_DEINIT(&xHandle, ina226_interface_iic_deinit);
	DRIVER_INA226_LINK_IIC_READ(&xHandle, ina226_interface_iic_read);
	DRIVER_INA226_LINK_IIC_WRITE(&xHandle, ina226_interface_iic_write);
	DRIVER_INA226_LINK_DELAY_MS(&xHandle, ina226_interface_delay_ms);
	DRIVER_INA226_LINK_DEBUG_PRINT(&xHandle, ina226_interface_debug_print);
	DRIVER_INA226_LINK_RECEIVE_CALLBACK(&xHandle, ina226_interface_receive_callback);

	/* set addr pin */
	res = ina226_set_addr_pin(&xHandle, addr_pin);
	if (res != 0){
		ina226_interface_debug_print("ina226: set addr pin failed.\n");

		return false;
	}

	/* set the r */
	res = ina226_set_resistance(&xHandle, r);
	if (res != 0){
		ina226_interface_debug_print("ina226: set resistance failed.\n");

		return false;
	}

	/* init */
	res = ina226_init(&xHandle);
	if (res != 0){
		ina226_interface_debug_print("ina226: init failed.\n");

		return 1;
	}

	/* set default average mode */
	res = ina226_set_average_mode(&xHandle, INA226_BASIC_DEFAULT_AVG_MODE);
	if (res != 0){
		ina226_interface_debug_print("ina226: set average mode failed.\n");
		(void)ina226_deinit(&xHandle);

		return false;
	}

	/* set default bus voltage conversion time */
	res = ina226_set_bus_voltage_conversion_time(&xHandle, INA226_BASIC_DEFAULT_BUS_VOLTAGE_CONVERSION_TIME);
	if (res != 0){
		ina226_interface_debug_print("ina226: set bus voltage conversion time failed.\n");
		(void)ina226_deinit(&xHandle);

		return false;
	}

	/* set default shunt voltage conversion time */
	res = ina226_set_shunt_voltage_conversion_time(&xHandle, INA226_BASIC_DEFAULT_SHUNT_VOLTAGE_CONVERSION_TIME);
	if (res != 0){
		ina226_interface_debug_print("ina226: set shunt voltage conversion time failed.\n");
		(void)ina226_deinit(&xHandle);

		return false;
	}

	/* calculate calibration */
	res = ina226_calculate_calibration(&xHandle, (uint16_t *)&calibration);
	if (res != 0){
		ina226_interface_debug_print("ina226: calculate calibration failed.\n");
		(void)ina226_deinit(&xHandle);

		return false;
	}
	res = ina226_set_calibration(&xHandle, calibration);
	if (res != 0){
		ina226_interface_debug_print("ina226: set calibration failed.\n");
		(void)ina226_deinit(&xHandle);

		return false;
	}

	/* set shunt bus voltage continuous */
	res = ina226_set_mode(&xHandle, INA226_MODE_SHUNT_BUS_VOLTAGE_CONTINUOUS);
	if (res != 0){
		ina226_interface_debug_print("ina226: set mode failed.\n");
		(void)ina226_deinit(&xHandle);

		return false;
	}

	return true;
}


bool INA226::get(float *mV, float *mA, float *mW){
    uint8_t res;
    int16_t s_raw;
    uint16_t u_raw;

    /* read bus voltage */
    res = ina226_read_bus_voltage(&xHandle, (uint16_t *)&u_raw, mV);
    if (res != 0)
    {
        return false;
    }

    /* read current */
    res = ina226_read_current(&xHandle, (int16_t *)&s_raw, mA);
    if (res != 0)
    {
        return false;
    }

    /* read power */
    res = ina226_read_power(&xHandle, (uint16_t *)&u_raw, mW);
    if (res != 0)
    {
        return false;
    }

    return true;
}


