#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "led_strip_rmt.h"
#include "esp_err.h"

#define LED_GPIO 48

led_strip_handle_t led_strip;

void led_task(void *pvParameters)
{
    while (1)
    {
        // Turn LED ON (Red)
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Turn LED OFF
        led_strip_clear(led_strip);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,
        .max_leds = 1,
        .led_model = LED_MODEL_WS2812,
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
        .flags = {
            .invert_out = false,
        },
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10000000,
        .mem_block_symbols = 64,
        .flags = {
            .with_dma = false,
        },
    };

    // Initialize RGB LED
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    // Create LED task
    xTaskCreate(led_task, "led_task", 2048, NULL, 5, NULL);
}