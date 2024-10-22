#include "led_module.h"

#include <stddef.h>

static struct LED_MODULE *led_module;

int main(void)
{
        struct LED_MODULE_CFG cfg = {
                .drv_name = "PWM",
        };

        led_module = led_module_create(led_module, &cfg);

        if (!led_module) {
                if (led_module->init(led_module) == 0) {
                        led_module->start(led_module);
                } else {
                        goto exit;
                }
        } else {
                goto exit;
        }

        while (1) {
                led_module->handler(led_module);
                delay_ms(1);
        }

        exit :
                return 0;
}
