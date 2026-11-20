#include <stdio.h>
#include "driver/gpio.h"
#include "led_strip.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    led_strip_handle_t led;

    int button_state;
    int previous_state = 1;
    int led_state = 0;

    led_strip_config_t strip_config = {
        .strip_gpio_num = 48,
        .max_leds = 1,
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10000000,
    };

    led_strip_new_rmt_device(&strip_config, &rmt_config, &led);

    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_0),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&button_config);

    while(1)
    {
        button_state = gpio_get_level(GPIO_NUM_0);

        if(button_state == 0 && previous_state == 1)
        {
            led_state = !led_state;

            if(led_state == 1)
            {
                led_strip_set_pixel(led, 0, 255, 0, 0);
                led_strip_refresh(led);
                printf("LED ON\n");
            }
            else
            {
                led_strip_clear(led);
                led_strip_refresh(led);
                printf("LED OFF\n");
            }

            vTaskDelay(pdMS_TO_TICKS(200));
        }

        previous_state = button_state;

            vTaskDelay(pdMS_TO_TICKS(50));
    }
}