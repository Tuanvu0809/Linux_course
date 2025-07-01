#include <stdio.h>
#include <stdbool.h>
#include "inc/led_driver.h"


int main()
{ 
    printf("Program Pixel \n");
    /*Init array led */
    if(led_init(10) != 0)
    {
        fprintf(stderr, "Failed to initialize logger\n");
            printf("Failed init data");
            return -1;
    }

    /*Const Buffer for led */
    const uint32_t* Buffer ; 
    Buffer = led_get_Buffer();
    for(int i=0; i<led_get_pixel_count() ;i++){
        if(Buffer[i]  != 0 ){
            printf("Buffer[%d] not init",i);
        }    
    } 

    /*Set color for Led */    
    led_set_pixel_color(0,255,0,0);
    led_set_pixel_color(9,0,0,255);
    led_set_pixel_color(4,255,255,255);
    
    led_printf_index(0);
    led_printf_index(4);
    led_printf_index(9);
    
    /*Set all pixel is green*/
    led_fill(0,255,0);
    bool check_is_green = true;
    for(int i=0;i<led_get_pixel_count();i++)
    {
        if(Buffer[i]!= 0x0000FF00 )
        {
            printf("Buffer[%d] not green",i);
            check_is_green = false;
        }
    }

    /*Check flag*/
    if(check_is_green == true)
    {
        printf("All green !! \n");
    }
    else {
        printf("fail\n");
    }
    
    /*Free memory*/
    led_shutdown();
   
    return 0;
}