#include "led_drv_ws2812b.h"
#include "stm32f10x.h"

static struct LED_DRV_WS2812B led_drv_ws2812b;

#define DATA_PIN_HIGH()    GPIO_SetBits(GPIOA, GPIO_PIN_13)
#define DATA_PIN_LOW()     GPIO_ResetBits(GPIOA, GPIO_PIN_13)

static void delay_ns(unsigned int ns)
{
        while (ns--) {
                __nop();
        }
}

static void ws2812b_reset(void)
{
        DATA_PIN_LOW(); delay_ns(1000);
}

static void ws2812b_t0(void)
{
        DATA_PIN_HIGH(); delay_ns(7);
        DATA_PIN_LOW(); delay_ns(26);
}

static void ws2812b_t1(void)
{
        DATA_PIN_HIGH(); delay_ns(26);
        DATA_PIN_LOW(); delay_ns(7);
}

static ws2812b_set_one_rgb(unsigned char *data, unsigned char brightness)
{
        unsigned char i = 0, j = 0;
        unsigned char c_temp = 0;
        unsigned int i_temp = 0;

        for (j = 0; j < 3; j++) {
                i_temp =  data[j] * brightness / 255;
                c_temp = (unsigned char)i_temp;
                for (i = 0; i < 8; i++) {
                        if (c_temp & 0x80) {
                                ws2812b_t1();
                        } else {
                                ws2812b_t0();
                        }
                        c_temp <<= 1;
                }
        }
}

//把RGB和亮度数据，发送到ws2812b的数据线上
static void ws2812b_set_data(struct LED_DRV_WS2812B *ws2812b)
{
        unsigned int i = 0, j = 0, k = 0;
        unsigned char color_buff[3];
        unsigned char brightness = 0;
        unsigned int led_count = ws2812b->drv.led_count;    //灯珠总数

        if (led_count == 0) return;

        __disable_irq();
        ws2812b_reset();

        for (i = 0;i < LED_MAX_NUM; i++) {
                color_buff[0] = ws2812b->rgbcw_value[i].green;
                color_buff[1] = ws2812b->rgbcw_value[i].red;
                color_buff[2] = ws2812b->rgbcw_value[i].blue;
                brightness = ws2812b->led_brightness[i];

                ws2812b_set_one_rgb(color_buff, brightness);
        }

        ws2812b_reset();
        __enable_irq();
}

static void ws2812b_gpio_init(void)
{
        GPIO_InitType GPIO_InitStructure;

        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_InitStruct(&GPIO_InitStructure);

        GPIO_InitStructure.Pin = GPIO_PIN_15;// WS2812b驱动IO
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

static int init_(void *self)
{
        ws2812b_gpio_init();
        return 0;
}

static int turn_on_(void *self, enum LED_ID id)
{
        if (id >= LED_MAX_NUM) return -1;

        struct LED_DRV_WS2812B *ws2812b = (struct LED_DRV_WS2812B *)self;

        ws2812b->led_brightness[id] = ws2812b->old_led_brightness[id];    //用关灯前的亮度进行开灯

        ws2812b_set_data(ws2812b);
        return 0;
}

static int turn_off_(void *self, enum LED_ID id)
{
        if (id >= LED_MAX_NUM)return -1;

        struct LED_DRV_WS2812B *ws2812b = (struct LED_DRV_WS2812B *)self;

        ws2812b->old_led_brightness[id] = ws2812b->led_brightness[id];    //关灯前保存亮度，开灯时使用
        ws2812b->led_brightness[id] = 0;

        ws2812b_set_data(ws2812b);
        return 0;
}

static int set_brightness_(void *self, enum LED_ID id, unsigned char brightness)
{
        if (id >= LED_MAX_NUM)return -1;

        struct LED_DRV_WS2812B *ws2812b = (struct LED_DRV_WS2812B *)self;

        ws2812b->led_brightness[id] = brightness;
        ws2812b->old_led_brightness[id] = brightness;

        ws2812b_set_data(ws2812b);
        return 0;
}

static int set_color_(void *self, enum LED_ID id, struct RGBCW *color)
{
        if (id >= LED_MAX_NUM)return -1;

        struct LED_DRV_WS2812B *ws2812b = (struct LED_DRV_WS2812B *)self;

        ws2812b->rgbcw_value[id].red = color->red;
        ws2812b->rgbcw_value[id].green = color->green;
        ws2812b->rgbcw_value[id].blue = color->blue;
        ws2812b->rgbcw_value[id].cold_w = color->cold_w;
        ws2812b->rgbcw_value[id].white = color->white;

        ws2812b_set_data(ws2812b);
        return 0;
}

static int toggle_(void *self, enum LED_ID id)
{
        if (id >= LED_MAX_NUM) return -1;

        struct LED_DRV_WS2812B *ws2812b = (struct LED_DRV_WS2812B *)self;

        if (ws2812b->led_brightness[id] > 0) {
                turn_off_(self, id);
        } else {
                turn_on_(self, id);
        }
        return 0;
}


struct LED_DRV_WS2812B *led_drv_ws2812b_create(void)
{
        led_drv_ws2812b.drv.init = init_;
        led_drv_ws2812b.drv.turn_on = turn_on_;
        led_drv_ws2812b.drv.turn_off = turn_off_;
        led_drv_ws2812b.drv.toggle = toggle_;
        led_drv_ws2812b.drv.set_brightness = set_brightness_;
        led_drv_ws2812b.drv.set_color = set_color_;
        led_drv_ws2812b.flush_data = ws2812b_set_data;
        led_drv_ws2812b.drv.led_count = LED_MAX_NUM;
        return (&led_drv_ws2812b);
}
