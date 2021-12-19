#include "pico/stdlib.h"

int main() {
    #ifdef PICO_DEFAULT_LED_PIN
        const uint LED_PIN = PICO_DEFAULT_LED_PIN;
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
        uint ledTime = 1500;
        while(true) {
            gpio_put(LED_PIN, 1);
            sleep_ms(ledTime);
            gpio_put(LED_PIN, 0);
            sleep_ms(ledTime);
        }
    #endif
    return 0;
}