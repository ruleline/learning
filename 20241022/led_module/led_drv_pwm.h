#ifndef _LED_DRV_PWM_H_
#define _LED_DRV_PWM_H_

#include "led_driver.h"

struct LED_DRV_PWM {
        struct LED_DRIVER drv;    //LED驱动层接口

        //添加某些特定参数；
        unsigned char led_level[LED_MAX_NUM];    //LED灯的亮度占空比
};

struct LED_DRV_PWM *led_drv_pwm_create(void);

#endif
