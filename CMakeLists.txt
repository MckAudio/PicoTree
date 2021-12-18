cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(my_pico)

pico_sdk_init()

add_executable(pwm
    ./src/pwm.c
    )

target_link_libraries(pwm pico_stdlib hardware_pwm hardware_irq)

pico_add_extra_outputs(pwm)