#include "inc/pub/door.h"
#include "inc/pub/smoke.h"
#include "inc/sub/alarm.h"
#include "inc/sub/mobile.h"
// #include "inc/sub/alarm.h"
// #include "inc/sub/mobile.h"

#include <stdio.h>

int main()
{
    /* init publisher*/
    door_sensor door;
    Creat_door_sensor(&door);

    smoke_sensor smoke;
    Creat_smoke_sensor(&smoke);

    /*Init  Subscriber */
    Alarm Alarm_bell;
    creat_Alarm(&Alarm_bell);
    
    Mobile Mobile_phone;
    creat_mobile(&Mobile_phone);

    /*register  Subscriber  for Publisher*/
    door.base.sub(&door.base,(Sub*) &Mobile_phone);
    door.base.sub(&door.base,(Sub*) &Alarm_bell);

    smoke.base.sub(&smoke.base,(Sub*) &Mobile_phone);
    smoke.base.sub(&smoke.base,(Sub*) &Alarm_bell);

    /*Information*/

    trigger_s(&smoke,have_smoke);


    return 0;
}