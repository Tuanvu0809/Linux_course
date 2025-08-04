#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/config.h"
#include "../inc/watering_logic.h"

#define MOISTER_MIN_FOR_AUTO 50
#define MOISTER_MAX_FOR_AUTO 70
#define TIMES_NEED 5
#define TIMES_CHECKS 10

/*Extern variable*/
extern data sensor;
extern LED_STATUS led;
extern STATUS pump;

void Pump_operator();
void Turn_led(LED_STATUS led);
void Read_TEMP_MOISTURE();

void init_For_Auto(SETTING *want)
{
    want->moisture_min = MOISTER_MIN_FOR_AUTO;
    want->moisture_max = MOISTER_MAX_FOR_AUTO;
    want->times = TIMES_NEED;
    want->check = TIMES_CHECKS;
    want->Mode_sys = MODE_AUTO;
}

void Display_For_Auto(SETTING want)
{
    printf("Moister need : %d between %d \n", want.moisture_min, want.moisture_max);
    printf("Times to water: %d\n", want.times);
    printf("Check after: %d\n", want.check);
}

void Handle_Auto(SETTING *current)
{
    /*check current not equal NULL*/
    if (current == NULL)
        return;

    if (current->Mode_sys != MODE_AUTO)
        return;

    for (int i = 0; i <= current->check; i++)
    {
        if (sensor.Moisture < current->moisture_min && i < current->times)
        {
            led = LED_WATERING;
            pump = PUMP_ON;
        }
        else
        {
            led = LED_NORMAL;
            pump = PUMP_OFF;
        }
        printf("%2ds  Status Pump:  ", i);
        Pump_operator();
        printf(" Status for led:  ");
        Turn_led(led);
        printf("\n");
    }
}

void Handle_Manual(SETTING *current)
{
    /*check current not equal NULL*/
    if (current == NULL)
        return;
    if (current->Mode_sys != MODE_MANUAL)
        return;
    printf("  Status Pump:  ");
    Pump_operator();
    printf(" Status led:  ");
    Turn_led(led);
}