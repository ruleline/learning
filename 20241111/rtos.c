/**
 * @file rtos.c
 * @brief rtos
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


xTaskCreate(Task1_LED, "Task1_LED", STACK1_LED, 0, STASK1_LED, 0);
xTaskCreate(Task2_READSENSOR, "Task2_READSENSOR", STACK2_READSENSOR, 0, STASK2_READSENSOR, NULL);
xTaskCreate(Task3_SEND, "Task3_SEND", STACK3_SEND, 0, STASK3_SEND, 0);


QueueHandle_t xSENSORSendQueue;
xSENSORSendQueue = xQueueCreate(SENSORSEND_QUEUE_LEN, SENSORSEND_QUEUE_SIZE);


void Task1_LED(void *pvParameters)
{
        for (;;) {
                LED_TOGGLE();
                vTaskDelay(500);
        }
}


void Task2_READSENSOR(void *pvParameters)
{
        for (;;) {
                ReadSensor(&sensorData);
                DisplayData(&sensorData);
                xQueueSend(xSENSORSendQueue , &sensorData, 100)
                vTaskDelay(100);
        }
}


static unsigned char sensorData[2];

void Task3_SEND(void *pvParameters)
{
        for (;;) {
                if (xQueueReceive(xSENSORSendQueue, &sensorData, 100) == pdTRUE) {
                        UARTSend(&sensorData);
                }
                vTaskDelay(10);
        }
}
