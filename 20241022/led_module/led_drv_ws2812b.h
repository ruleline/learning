#ifndef _LED_DRV_WS2812B_H_
#define _LED_DRV_WS2812B_H_

#include "led_driver.h"

struct LED_DRV_WS2812B {
        struct LED_DRIVER drv;

        //添加 WS2812B 灯珠某些特定参数；
        unsigned char old_led_brightness[LED_MAX_NUM];    //关灯前的亮度参数
        unsigned char led_brightness[LED_MAX_NUM];    //亮度参数
        struct RGBCW rgbcw_value[LED_MAX_NUM];    //rgbcw颜色值

        void (*flush_data)(struct LED_DRV_WS2812B *self); //刷新ws2812b灯珠数据
};

struct LED_DRV_WS2812B *led_drv_ws2812b_create(void);

#endif
