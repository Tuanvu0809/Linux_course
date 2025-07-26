#include <stdio.h>
#include "test.h"
#include <stdbool.h>

#include "../inc/led_driver.h"

void test_led_all(const uint32_t* Buffer,uint32_t color )
{
    bool check = true;
     for(int i=0;i<Led_get_pixel_count();i++)
    {
        if(Buffer[i]!= color )
        {
            printf("Buffer[%d] = 0x%p \n",i,Buffer[i]);
            check = false; 
        }
    }

    if(check == true)
    {
        printf("\nAll green !! \n");
    }
    else {
        printf("fail\n");
    }
}


