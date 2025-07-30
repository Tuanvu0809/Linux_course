#include <stdio.h>
#include "inc/Publisher.h"
#include "inc/Subscriber.h"
#include "inc/Publisher/Door.h"
#include "inc/Publisher/Smoke.h"
#include "inc/Subscriber/alarm.h"
#include "inc/Subscriber/mobile.h"

int main()
{
    printf(">> Smart home Observe: \n");

    /*Init Publisher*/
    Door_sensor door;
    Creat_door_sensor(&door);

    Smoke_sensor smoke;
    Creat_smoke_sensor(&smoke);

    /*Init  Subscriber */
    Alarm Alarm_bell;
    Creat_Alarm(&Alarm_bell);

    Mobile Mobile_phone;
    Creat_Mobile(&Mobile_phone);

    /*register  Subscriber  for Publisher*/
    door.base.sub(&door.base, &Mobile_phone.base);
    door.base.sub(&door.base, &Alarm_bell.base);

    smoke.base.sub(&smoke.base, &Mobile_phone.base);
    smoke.base.sub(&smoke.base, &Alarm_bell.base);

    /*Information*/
    Trigger_smoke(&smoke, No_smoke);
    Trigger_door(&door, close);
    Trigger_smoke(&smoke, Smoke);
    printf("----\n");

    /*Unsubscribe for Publisher */
    door.base.unsub(&door.base, &Alarm_bell.base);

    /*Information*/
    Trigger_door(&door, open);
    Trigger_smoke(&smoke, Smoke);
    printf("\nend of program");

    return 0;
}