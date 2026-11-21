#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Task handles
TaskHandle_t Task1_Handle = NULL;
TaskHandle_t Task2_Handle = NULL;

// Task 1 - Sender
void Task1(void *arg)
{
    while (1)
    {
        printf("Task 1 sending notification to Task 2\n");

        xTaskNotifyGive(Task2_Handle);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 2 - Receiver
void Task2(void *arg)
{
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        printf("Task 2 received notification from Task 1\n");
    }
}

void app_main(void)
{
    // Create Task 2 first
    xTaskCreate(Task2, "Task2", 2048, NULL, 1, &Task2_Handle);

    // Create Task 1
    xTaskCreate(Task1, "Task1", 2048, NULL, 1, &Task1_Handle);
    
}