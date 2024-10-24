#include "led_drv_pin.h"

static struct LED_DRV_PIN led_drv_pin;

static void mcu_gpio_init(void)
{
        //在这里初始化各个LED灯引脚
}

static void set_gpio_high(unsigned char gpio_num)
{
        //在这里设置指定的GPIO高电平
}

static void set_gpio_low(unsigned char gpio_num)
{
        //在这里设置指定的GPIO低电平
}

static int init_(void *self)
{
        mcu_gpio_init();
        return 0;
}

static int turn_on_(void *self, enum LED_ID id)
{
        if (!self) return -1;

        struct LED_DRV_PIN *drv_pin = (struct LED_DRV_PIN *)self;

        set_gpio_high(id);
        drv_pin->state[id] = 1;
        return 0;
}

static int turn_off_(void *self, enum LED_ID id)
{
        if (!self) return -1;

        struct LED_DRV_PIN *drv_pin = (struct LED_DRV_PIN *)self;

        set_gpio_low(id);
        drv_pin->state[id] = 0;
        return 0;
}

//引脚高低电平驱动不支持设置亮度
static int set_brightness_(void *self, enum LED_ID id, unsigned char level)
{
        return -1;
}

//引脚高低电平驱动不不支持设置颜色
static int set_color_(void *self, enum LED_ID id, struct RGBCW *color)
{
        return -1;
}


static int toggle_(void *self, enum LED_ID id)
{
        if (!self) return -1;

        struct LED_DRV_PIN *drv_pin = (struct LED_DRV_PIN *)self;

        if (drv_pin->state[id]) {
                set_gpio_low(id);
        } else {
                set_gpio_high(id);
        }
        return 0;
}

struct LED_DRV_PIN *led_drv_pin_create(void)
{
        led_drv_pin.drv.init = init_;
        led_drv_pin.drv.turn_on = turn_on_;
        led_drv_pin.drv.turn_off = turn_off_;
        led_drv_pin.drv.toggle = toggle_;
        led_drv_pin.drv.set_brightness = 0;
        led_drv_pin.drv.set_color = 0;
        led_drv_pin.drv.led_count = LED_MAX_NUM;
        return &led_drv_pin;
}
