idf_component_register(SRCS "button_control_rgb_led.c"
                     INCLUDE_DIRS "."
                     REQUIRES led_strip esp_driver_gpio)