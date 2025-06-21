#include <stdio.h>
#include "..\inc\config.h"


static void Status_moisture(LED_STATUS led){
    printf(" Status message: ");
    switch(led){
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

static void RED(){
    printf("Red\t");
}

static void Green(){
    printf("Green\t");
}

static void Yellow(){
    printf("Yellow\t");
}

static void Led_all_off(){
    printf("All led off");
}
void Turn_led(LED_STATUS led){
    switch(led){
        case LED_NORMAL :
            Led_all_off();
            break;
        case LED_WATERING:
            Green();
            break;
        case LED_LOW_MOISTURE_ALERT:
            Yellow();
            break;
        case LED_ERROR:
            RED();
            break;
        default: 
            RED();
            Yellow();
            break;
    }

    Status_moisture(led);
    
}