#include "pico/stdlib.h"
#include "math.h"

int main()
{
    const uint DT_PIN = 14;
    const uint CLK_PIN = 15;
    gpio_init(DT_PIN);
    gpio_set_dir(DT_PIN, GPIO_IN);
    gpio_init(CLK_PIN);
    gpio_set_dir(CLK_PIN, GPIO_IN);

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    stdio_init_all();
    bool clkWise = true;
    bool turning = false;
    bool dt = true;
    bool clk = true;
    int counter = 10;
    int minCounter = 1;
    int maxCounter = 25;

    uint blinkTime = 100;
    uint blinkCount = 0;
    bool blinkHigh = true;
    while (true)
    {
        dt = gpio_get(DT_PIN);
        clk = gpio_get(CLK_PIN);
        if (turning)
        {
            if (dt && clk)
            {
                if (clkWise)
                {
                    counter = fmin(maxCounter, counter + 1);
                    printf("Click clock wise: %d\n", counter);
                }
                else
                {
                    counter = fmax(minCounter, counter - 1);
                    printf("Click counter clock wise: %d\n", counter);
                }
                turning = false;
            }
        }
        else
        {
            turning = dt != clk;
            clkWise = dt && clk == false;
        }

        blinkTime = counter * 100;
        if (blinkCount >= blinkTime) {
            blinkCount = 0;
            gpio_put(LED_PIN, blinkHigh);
            blinkHigh = !blinkHigh;
        }
        blinkCount += 1;


        sleep_ms(1);
    }
    return 0;
}