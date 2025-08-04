#include <stdio.h>
#include <stdbool.h>
#include "inc/led_driver.h"
#include "test/test.h"

int main()
{
    printf("Program Pixel \n");
    /*Init array Led */
    if (Led_init(10) != 0)
    {
        fprintf(stderr, "FaiLed to initialize logger\n");
        printf("FaiLed init data");
        return -1;
    }

    /*Const Buffer for Led */
    const uint32_t *Buffer;
    Buffer = Led_get_buffer();
    for (int i = 0; i < Led_get_pixel_count(); i++)
    {
        if (Buffer[i] != 0)
        {
            printf("Buffer[%d] not init", i);
        }
    }

    /*Set color for Led */
    Led_set_pixel_color(0, 255, 0, 0);
    Led_set_pixel_color(9, 0, 0, 255);
    Led_set_pixel_color(4, 255, 255, 255);

    for (int i = 0; i <= Led_get_pixel_count(); i++)
    {
        Led_printf_index(i);
    }
    
    /*Set all pixel is green*/
    Led_fill(0, 255, 0);
    test_led_all(Buffer, 0x0000FF00);

    /*Free memory*/
    Led_shutdown();

    return 0;
}