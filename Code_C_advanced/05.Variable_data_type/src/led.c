#include <stdio.h>
#include "../inc/config.h"

static void Turn_led_for_status(LED_STATUS led)
{
    printf(" Status message: ");
    switch (led)
    {
        case LED_NORMAL:
            printf(" Normal");
            break;
        case LED_WATERING:
            printf(" Watering");
            break;
        case LED_LOW_MOISTURE_ALERT:
            printf(" Low moisture");
            break;
        default:
            printf(" `Error");
            break;
    }
}

static void Turn_Red()
{
    printf("Red\t");
}

static void Turn_Green()
{
    printf("Green\t");
}

static void Turn_Yellow()
{
    printf("Yellow\t");
}

static void Turn_All_Led_off()
{
    printf("All led off");
}
void Turn_led(LED_STATUS led)
{
    switch (led)
    {
        case LED_NORMAL:
            Turn_All_Led_off();
            break;
        case LED_WATERING:
            Turn_Green();
            break;
        case LED_LOW_MOISTURE_ALERT:
            Turn_Yellow();
            break;
        case LED_ERROR:
            Turn_Red();
            break;
        default:
            Turn_Red();
            Turn_Yellow();
            break;  
    }

   Turn_led_for_status(led);
}