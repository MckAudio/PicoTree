#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "math.h"

const int LED_PIN = PICO_DEFAULT_LED_PIN;

int pwmValue = 127;

void on_pwm_wrap()
{
    static int fade = 0;
    static bool up = true;

    pwm_clear_irq(pwm_gpio_to_slice_num(LED_PIN));
    /*
    if (up)
    {
        fade++;
        if (fade > 255)
        {
            fade = 255;
            up = false;
        }
    }
    else
    {
        fade--;
        if (fade < 0)
        {
            fade = 0;
            up = true;
        }
    }*/
    fade = pwmValue;
    pwm_set_gpio_level(LED_PIN, fade * fade);
}

int main()
{
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint sliceNum = pwm_gpio_to_slice_num(LED_PIN);

    pwm_clear_irq(sliceNum);
    pwm_set_irq_enabled(sliceNum, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(sliceNum, &config, true);

    // Set up encoder
    const uint DT_PIN = 14;
    const uint CLK_PIN = 15;
    gpio_init(DT_PIN);
    gpio_set_dir(DT_PIN, GPIO_IN);
    gpio_init(CLK_PIN);
    gpio_set_dir(CLK_PIN, GPIO_IN);
    
    bool clkWise = true;
    bool turning = false;
    bool dt = true;
    bool clk = true;
    int counter = 64;
    int minCounter = 0;
    int maxCounter = 127;
    
    while (1)
    {
        //tight_loop_contents();
        /*
        for(pwmValue = 0; pwmValue < 256; pwmValue++)
        {   
            sleep_ms(1);
        }
        for(pwmValue = 255; pwmValue >= 0; pwmValue--)
        {   
            sleep_ms(1);
        }*/
        dt = gpio_get(DT_PIN);
        clk = gpio_get(CLK_PIN);
        if (turning)
        {
            if (dt && clk)
            {
                if (clkWise)
                {
                    counter = fmin(maxCounter, counter + 1);
                }
                else
                {
                    counter = fmax(minCounter, counter - 1);
                }
                turning = false;
            }
        }
        else
        {
            turning = dt != clk;
            clkWise = dt && clk == false;
        }

        pwmValue = counter + counter + 1;


        sleep_ms(1);
    }
    return 0;
}