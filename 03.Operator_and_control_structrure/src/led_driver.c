#include <stdio.h>
#include "../inc/Led_driver.h"
/*array Led and variable of quantity */
static uint32_t *Led_arr = NULL;
static size_t Led_quantity = 0;

/*Init quantity of Led and buffer of Led */
int Led_init(size_t num_pixels)
{

        Led_arr = (uint32_t *)malloc(num_pixels * sizeof(uint32_t));
        if (Led_arr == NULL || num_pixels > MAX_PIXEL)
                return -1;

        Led_quantity = num_pixels;
        Led_clear();
        return 0;
}

/*Turn off all Led*/
void Led_clear()
{
        Led_fill(0, 0, 0);
}
/*Free memory Led array*/
void Led_shutdown()
{
        free(Led_arr);
        Led_quantity = 0;
        Led_arr = NULL;
}
/*Set color for Led*/
void Led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b)
{
        if (Led_arr == NULL || (index >= Led_get_pixel_count() ))
        {
                printf("can't");
                return;
        }
        Led_arr[index] = ((uint32_t)g << GREEN_SHIFT) | ((uint32_t)r << RED_SHIFT) | ((uint32_t)b << BLUE_SHIFT);
}
/*Set all Led for one color*/
void Led_fill(uint8_t r, uint8_t g, uint8_t b)
{
        uint32_t calculate;

        calculate = ((uint32_t)g << GREEN_SHIFT) | ((uint32_t)r << RED_SHIFT) | ((uint32_t)b << BLUE_SHIFT);

        for (size_t i = 0; i < Led_get_pixel_count(); i++)
        {
                Led_arr[i] = calculate;
        }

}

/*Return Led array*/
const uint32_t *Led_get_buffer()
{
        return Led_arr;
}
/*Return number of Led already init*/
size_t Led_get_pixel_count()
{
        return Led_quantity;
}

/*Check status of Led */
void Led_printf_index(size_t index)
{

        if (Led_arr == NULL || (index >= Led_get_pixel_count() || index < 0))
                return;

        printf("Pixel  %2d = 0x%p\n", index, Led_arr[index]);
}
