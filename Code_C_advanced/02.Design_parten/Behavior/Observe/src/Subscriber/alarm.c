#include "../../inc/Subscriber/alarm.h"
#include <stdio.h>
void Alarm_update(Subscribers *self, Publisher *context, char *event)
{
    (void)self;
    (void)context;
    printf("[AlarmSystem] Alarm: %s\n", event);
}

void Creat_Alarm(Alarm *System)
{
    System->base.Update = (void *)Alarm_update;
    System->base.data = NULL;
}