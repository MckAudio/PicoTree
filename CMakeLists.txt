cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(my_pico)

pico_sdk_init()

# Christmas Tree - Simple PWM LED
add_executable(pwm
    ./src/pwm.c
    )
target_link_libraries(pwm pico_stdlib hardware_pwm hardware_irq)
pico_add_extra_outputs(pwm)

# LED Blink Example
add_executable(blink
    ./src/blink.c
    )
target_link_libraries(blink pico_stdlib)
pico_add_extra_outputs(blink)

# Hello World USB Example
add_executable(encoder
    ./src/encoder.c
    )
target_link_libraries(encoder pico_stdlib)
pico_enable_stdio_usb(encoder 1)
pico_enable_stdio_uart(encoder 0)
pico_add_extra_outputs(encoder)

# LED PWM Fade
add_executable(led
    ./src/led_fade.c
    )
target_link_libraries(led pico_stdlib hardware_pwm hardware_irq)
pico_add_extra_outputs(led)