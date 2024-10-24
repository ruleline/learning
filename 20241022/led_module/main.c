#include "led_module.h"

static struct LED_MODULE *led;

int main(void)
{
        struct LED_MODULE_CFG cfg = {
                .drv_name = "PWM",
        };

        led = led_module_create(led, &cfg);

        if (!led) {
                if (led->init(led) == 0) {
                        led->start(led);
                } else {
                        goto exit;
                }
        } else {
                goto exit;
        }

        while (1) {
                led->handler(led);
                delay_ms(1);
        }

        exit :
                return 0;
}
