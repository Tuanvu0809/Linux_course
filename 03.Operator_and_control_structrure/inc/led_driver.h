#ifndef LED_DRIVER_H
#define LED_DRIVER_H
    /*Libary*/
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>

    /*Marco*/
    #define Max_pixel   32
    #define Green_on_pixel  8
    #define Red_on_pixel  16
    #define Blue_on_pixel  0

    /*Fuction Creat*/
    int led_init(size_t num_pixels);
    const uint32_t* led_get_Buffer();
    size_t led_get_pixel_count();

    void led_printf_index(size_t index);
    void led_shutdown();
    void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);
    void led_fill(uint8_t r, uint8_t g, uint8_t b);
    void led_clear();

#endif