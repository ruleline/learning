#include "led_module.h"

#include <stddef.h>
#include <string.h>

static struct LED_MODULE led_module = {
        .led_count = 0,
        .led_drv = NULL,
};

static int init_(struct LED_MODULE *self)
{
        if (!self) return -1;

        if (NULL != led_module.led_drv) {
                led_module.led_drv->init(led_module.led_drv);
        }

        return 0;
}

//启动LED模块状态机
static int start_(struct LED_MODULE *self)
{
        if (!self) return -1;

        //在这里添加某些启动条件，也可以不添加

        return 0;
}

//LED模块状态机处理函数
static int handler_(struct LED_MODULE *self)
{
        if (!self) return -1;

        static unsigned int count = 0;
        static unsigned char flag = 0;

        if (count++ < 1000) return 0;
        count = 0;

        //在这里完善led模块的状态机（TODO）

        //每隔1秒，翻转指定的LED（演示作用）
        self->led_drv->toggle(self->led_drv, LED_ID_1);
        self->led_drv->toggle(self->led_drv, LED_ID_2);
        self->led_drv->toggle(self->led_drv, LED_ID_3);
        self->led_drv->toggle(self->led_drv, LED_ID_4);

        return 0;
}

//获取LED硬件数量
static int get_led_count_(struct LED_MODULE *self)
{
        if (!self) return -1;

        self->led_count = self->led_drv->led_count;

        return self->led_count;
}

/**
 * @brief 创建一个LED模块
 *
 * @param self LED模块句柄
 * @param cfg 配置信息结构体
 * @return struct LED_MODULE*
 */
struct LED_MODULE *led_module_create(struct LED_MODULE *self, struct LED_MODULE_CFG *cfg)
{
        if (!cfg)return NULL;

        led_module.init = init_;
        led_module.start = start_;
        led_module.handler = handler_;
        led_module.get_led_count = get_led_count_;

        //使用简单工厂模式，初始化led驱动
        if (strcmp("PIN", cfg->drv_name) == 0) {
                led_module.led_drv = (struct LED_DRIVER*)led_drv_pin_create();
        } else if (strcmp("PWM", cfg->drv_name) == 0) {
                led_module.led_drv = (struct LED_DRIVER*)led_drv_pwm_create();
        } else if(strcmp("WS2812B", cfg->drv_name) == 0) {
                led_module.led_drv = (struct LED_DRIVER*)led_drv_ws2812b_create();
        } else {
                led_module.led_drv = NULL;
        }

        return (&led_module);
}
