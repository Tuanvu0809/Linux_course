#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc\config.h"
#include "inc\sensor.h"
#include "inc\actuators.h"
#include "inc\led.h"
#include "inc\watering_logic.h"
#include "inc\button.h"
data sensor;
STATUS pump;
LED_STATUS led;
STATUS init_pump();      


int main()
{
    /*use random function to simulate moisture signal*/
    srand(time(NULL)); 

    /* INIT sensor/LED/ pump*/
    pump = init_pump();
    led = LED_NORMAL;

    /*SET mode */
    SETTING mode;
    init_For_Auto(&mode);

    /*Display Auto setting*/
    Display_For_Auto(mode);
    mode.Mode_sys = MODE_AUTO;

    printf("mode 0. AUTO\n");
    printf("mode 1. MANUAL\n");
    printf("mode 2. EXIT\n");
      
    do {

        printf("\n Select mode: ");
        scanf("%d",(int*) &mode.Mode_sys);

        switch (mode.Mode_sys)
        {
            case MODE_AUTO:
                Set_for_auto(&mode);
                break;
            case MODE_MANUAL:
                Set_for_manual(&mode);
                break;
            case EXIT_CHOICE:
                printf("Exit\n");
                break;
            default:
                break;
        }

    }while(mode.Mode_sys != EXIT_CHOICE);

    return 0;
}    