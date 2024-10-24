#ifndef _LED_MODULE_H_
#define _LED_MODULE_H_

#include "led_drv_pin.h"
#include "led_drv_pwm.h"
#include "led_drv_ws2812b.h"

enum LED_STATE {
        LED_STATE_OFF           = 0, //关灯
        LED_STATE_ON            = 1, //开灯
        LED_STATE_TOGGLE        = 2, //翻转
        LED_STATE_FADE_IN       = 3, //渐亮
        LED_STATE_FADE_OUT      = 4, //渐灭
        LED_STATE_SET_COLOR     = 5, //设置颜色
};

struct LED_MODULE {
        //私有成员
        struct LED_DRIVER *drv;    //LED驱动句柄

        //对外公有成员
        unsigned char count;      //led灯珠数量

        int (*init)(struct LED_MODULE *self);
        int (*start)(struct LED_MODULE *self);
        int (*handler)(struct LED_MODULE *self);
        int (*get_count)(struct LED_MODULE *self);
};

struct LED_MODULE_CFG {
        char *drv_name;              //驱动方式
        //在这里还可以添加更多配置参数
};

struct LED_MODULE *led_module_create(struct LED_MODULE *self,
                                        struct LED_MODULE_CFG *cfg);

#endif
