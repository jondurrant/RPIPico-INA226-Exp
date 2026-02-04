

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define SDA 4
#define SCL 5

#include "driver_ina226_basic.h"



int main() {
    // Enable UART so we can print status output
    stdio_init_all();

    // This example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on a Pico)
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);

    uint8_t res;

    res = ina226_basic_init(INA226_ADDRESS_0, 0.1);
    if (res != 0){
       printf("Error INA226 Init failed\n");
       for (;;){
    	   sleep_ms(1000);
       }
    }

    for (;;){
        float mV;
        float mA;
        float mW;

        res = ina226_basic_read(&mV, &mA, &mW);
        if (res != 0)
        {
            (void)ina226_basic_deinit();

            return 1;
        }

        printf("ina226: bus voltage is %0.3fmV.\n", mV);
        printf("ina226: current is %0.3fmA.\n", mA);
        printf("ina226: power is %0.3fmW.\n", mW);
        sleep_ms(1000);

    }


    printf("Done.\n");
    return 0;

}
