#include "led_module.h"

static struct LED_MODULE *led;

int main(void)
{
        
        struct LED_MODULE_CFG cfg = {
                .drv_name = "PWM",
        };

        led = led_module_create(led, &cfg);

        if (!led && (led->init(led) == 0)) {
                led->start(led);
                while (1) {
                        led->handler(led);
                        delay_ms(1);
                }
        }

        return 0;
}
