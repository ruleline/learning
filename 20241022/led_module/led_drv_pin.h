#ifndef _LED_DRV_PIN_H_
#define _LED_DRV_PIN_H_

#include "led_driver.h"

struct LED_DRV_PIN {
        struct LED_DRIVER drv;    //LED驱动层接口

        //添加某些特定参数；
        unsigned char state[LED_MAX_NUM];    //led灯的状态
};

struct LED_DRV_PIN *led_drv_pin_create(void);

#endif
