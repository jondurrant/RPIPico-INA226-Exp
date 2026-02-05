# RPIPico-INA226-Exp
Experiments with INA226 on a RPI Pico. Using the excellent library framework [ina226](https://github.com/libdriver/ina226).

Examples where built using a Pico and the Pico SDK version 2.2.0.

## Connectivity
An INA226 Module was connected up to I2C0 via GP4 and GP5. 

For my measurements I put 
+ INA226 VBUS: to Measurement supply positive terminal, this was also the source for my load
+ INA226 IN+: to the negative terminal of my load
 + INA226 IN-: to ground of the supply

## Examples
Note real work in each ecample in is the port folder where the library is ported to the Pico architecture.

### Scan
Scan the I2C bus to identify the I2C address being used for the INA226. Mine where all on 0x40

### Basic
Copy of the basic example reading Volts, Current and Watts from the library.

### Class
Added in a C++ Class to encapsulate the INA226 interface. Main reason here was so that I2C bus (i2c0 or i2c1) could be selected in the code rather than hard coded in the interface.

## Build and Flash advise

I have a guide to how my project structures are designed and how to build Pico projects on my website [drjonea.co.uk](https://drjonea.co.uk/2025/12/15/building-my-projects-from-repo/).

