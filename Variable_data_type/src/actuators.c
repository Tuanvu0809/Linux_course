#include <stdio.h>
#include "..\inc\config.h"
#include "..\inc\actuators.h"
/*Extern variable*/
extern LED_STATUS led;
extern STATUS pump;
void Turn_led(LED_STATUS led);

STATUS init_pump(){
    return PUMP_OFF;
}

static void Pump_On_operator(){
    printf("Pump on \t");
    led = LED_WATERING;

}

static void Pump_OFF_operator(){
    printf("Pump off\t");
    led = LED_NORMAL;

}

void Pump_operator(){
    if(pump == PUMP_ON){
        Pump_On_operator();
    }    
    else {
        Pump_OFF_operator();
    }

}
