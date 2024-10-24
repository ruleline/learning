#include "led_drv_pwm.h"

static struct LED_DRV_PWM led_drv_pwm;

static void mcu_pwm_init(void)
{
        //在这里初始化MCU的PWM外设接口，比如初始化STM32的定时器PWM
}

static int init_(void *self)
{
        mcu_pwm_init();
        return 0;
}

static int turn_on_(void *self, enum LED_ID id)
{
        //调用PWM接口，设置占空比
        return 0;
}

static int turn_off_(void *self, enum LED_ID id)
{
        //调用PWM接口，设置占空比
        return 0;
}

static int set_brightness_(void *self, enum LED_ID id, unsigned char level)
{
        //调用PWM接口，设置占空比
        return 0;
}

static int set_color_(void *self, enum LED_ID id, struct RGBCW *color)
{
        return 0;
}

static int toggle_(void *self, enum LED_ID id)
{
        return 0;
}


struct LED_DRV_PWM *led_drv_pwm_create(void)
{
        led_drv_pwm.drv.init = init_;
        led_drv_pwm.drv.turn_on = turn_on_;
        led_drv_pwm.drv.turn_off = turn_off_;
        led_drv_pwm.drv.toggle = toggle_;
        led_drv_pwm.drv.set_brightness = set_brightness_;
        led_drv_pwm.drv.set_color = 0;
        led_drv_pwm.drv.led_count = LED_MAX_NUM;
        return (&led_drv_pwm);
}
