#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

enum LED_ID {
        LED_ID_1 = 0,
        LED_ID_2 = 1,
        LED_ID_3 = 2,
        LED_ID_4 = 3,

        LED_MAX_NUM,
};

//声明一个颜色值结构体，用来存放每个灯珠的颜色值
struct RGBCW {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char cold_w;    //冷白光
        unsigned char white;    //基础白光
};

//声明一个LED驱动抽象接口结构体
struct LED_DRIVER {
        unsigned int count;    //硬件对应的LED总数

        int (*init)(void *self);
        int (*turn_on)(void *self, enum LED_ID id);
        int (*turn_off)(void *self, enum LED_ID id);
        int (*set_brightness)(void *self, enum LED_ID id, unsigned char brightness);
        int (*set_color)(void *self, enum LED_ID id, struct RGBCW *color);
        int (*toggle)(void *self, enum LED_ID id);
};

#endif
