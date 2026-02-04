# Add library cpp files

if (NOT DEFINED INA226_DIR)
    set(INA226_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/ina226")
endif()

if (NOT DEFINED INA226_PORT)
    set(INA226_PORT "${CMAKE_CURRENT_LIST_DIR}/port/ina226")
endif()

add_library(ina226 STATIC)
target_sources(ina226 PUBLIC
    ${INA226_DIR}/src/driver_ina226.c
    ${INA226_PORT}/driver_ina226_interface_pico.c
    ${INA226_DIR}/example/driver_ina226_basic.c
)

# Add include directory
target_include_directories(ina226 PUBLIC 
   ${INA226_DIR}/src/
   ${INA226_DIR}/example/
   ${INA226_PORT}/
)

# Add the standard library to the build
target_link_libraries(ina226 PUBLIC 
    pico_stdlib
    hardware_i2c
    )