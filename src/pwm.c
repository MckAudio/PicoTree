/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

const uint BLUE_PIN = 0;
const uint YELLOW_PIN = 1;
const uint NUM_STATES = 4;

#ifdef PICO_DEFAULT_LED_PIN
    //#define USE_ONBOARD_LED
#endif

void on_pwm_wrap()
{
    static int fade = 0;
    static bool going_up = true;
    static uint state = 0; // 0 - both, 1 - blue, 2 - both, 3 - yellow

    if (state != 1)
    {
        pwm_clear_irq(pwm_gpio_to_slice_num(YELLOW_PIN));
    }
    if (state != 3)
    {
        pwm_clear_irq(pwm_gpio_to_slice_num(BLUE_PIN));
    }
    
    #ifdef USE_ONBOARD_LED
        pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));
    #endif

    if (going_up)
    {
        ++fade;
        if (fade > 255)
        {
            fade = 255;
            going_up = false;
        }
    }
    else
    {
        --fade;
        if (fade < 0)
        {
            fade = 0;
            going_up = true;
            state = (state + 1) % NUM_STATES;
        }
    }
    if (state != 1)
    {
        pwm_set_gpio_level(YELLOW_PIN, fade * fade);
    }
    if (state != 3)
    {
        pwm_set_gpio_level(BLUE_PIN, fade * fade);
    }
    #ifdef USE_ONBOARD_LED
        uint lfade = 255 - fade;
        pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, lfade * lfade);
    #endif
}

int main()
{
    gpio_set_function(BLUE_PIN, GPIO_FUNC_PWM);
    gpio_set_function(YELLOW_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BLUE_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    #ifdef USE_ONBOARD_LED
        gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
        uint led_slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);
        pwm_clear_irq(led_slice_num);
        pwm_set_irq_enabled(led_slice_num, true);
    #endif
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 16.0f);
    pwm_init(slice_num, &config, true);
    #ifdef USE_ONBOARD_LED
        pwm_init(led_slice_num, &config, true);
    #endif

    while (1)
    {
        tight_loop_contents();
    }
    return 0;
}