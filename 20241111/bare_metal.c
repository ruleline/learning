/**
 * @file bare_metal.c
 * @brief bare_metal
 * @author ruleline (ruleline@outlook.com)
 * @since 2024-11-11
 *
 * @authors ruleline (ruleline@outlook.com)
 * @date 2024-11-11
 * @version 0.00.001
 *
 * @copyright ©2024 UNISAR
 *
 * @details
 * -----------------------------------------------------------------------------
 *    version   |    date    |     author     |             comments
 * ------------ | ---------- | -------------- | --------------------------------
 *   0.00.001   | 2024-11-11 |    ruleline    | 初版
 * -----------------------------------------------------------------------------
 */

unsigned char sensorData[2];

int main(void)
{
        while(1)
        {
                LED_TOGGLE();            //LED亮灭

                ReadSensor(&sensorData); //读取传感器数据并显示
                DisplayData(&sensorData);

                UARTSend(&sensorData);   //发送数据
                Delay(100);
        }
}
