#ifndef LED_DRIVER_H
#define LED_DRIVER_H
    /*Libary*/
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>

    /*Marco*/
    #define MAX_PIXEL  32
    #define GREEN_SHIFT  8
    #define RED_SHIFT  16
    #define BLUE_SHIFT  0

    /*Fuction Creat*/
    int Led_init(size_t num_pixels);
    const uint32_t* Led_get_buffer();
    size_t Led_get_pixel_count();

    void Led_printf_index(size_t index);
    void Led_shutdown();
    void Led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);
    void Led_fill(uint8_t r, uint8_t g, uint8_t b);
    void Led_clear();

#endif