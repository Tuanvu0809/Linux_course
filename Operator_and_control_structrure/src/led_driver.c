#include <stdio.h>
#include "..\inc\led_driver.h"
/*array led and variable of quantity */
static uint32_t *Led_arr = NULL;
static size_t Led_quantity = 0;

/*Init quantity of led and buffer of led */
int  led_init(size_t num_pixels){

        Led_arr = (uint32_t *) malloc(num_pixels * sizeof(uint32_t));
        if(Led_arr == NULL || num_pixels >Max_pixel )    
            return -1;
        Led_quantity = num_pixels ;
        led_clear();
        return 0;
}

/*Turn off all Led*/
void led_clear()
{
        led_fill(0,0,0);
}
/*Free memory Led array*/
void led_shutdown()
{
        free(Led_arr);
        Led_quantity = 0;
        Led_arr = NULL;

}
/*Set color for led*/
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b){
        if(Led_arr == NULL || (index >= led_get_pixel_count() || index < 0)) return;

        Led_arr[index] = ((uint32_t) g<<Green_on_pixel) | ((uint32_t) r<<Red_on_pixel) | ((uint32_t) b<<Blue_on_pixel); 
 }
/*Set all led for one color*/
void led_fill(uint8_t r, uint8_t g, uint8_t b){

    uint32_t *calculate = (uint32_t *) malloc(sizeof(uint32_t));
    *calculate = ((uint32_t) g<<Green_on_pixel) | ((uint32_t) r<<Red_on_pixel) | ((uint32_t) b<<Blue_on_pixel);

        for(size_t i=0; i<led_get_pixel_count();i++)
        {
            Led_arr[i] = *calculate;
        }
    free(calculate);
}

/*Return Led array*/
const uint32_t* led_get_Buffer(){
        return Led_arr;
}
/*Return number of led already init*/
size_t led_get_pixel_count(){
        return Led_quantity;
}

/*Check status of led */
void led_printf_index(size_t index){
        
        if(Led_arr == NULL || (index >= led_get_pixel_count() || index <0)) return;

        printf("Pixel  %2d = 0x%p\n",index,Led_arr[index]);
}
