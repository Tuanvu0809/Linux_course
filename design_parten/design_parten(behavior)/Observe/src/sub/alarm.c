
#include <stdio.h>

#include "../../inc/sub/alarm.h"


void Alarm_update(Subscribers *self,Publisher *context, char *event )
{
    (void *) self;
    (void *) context;
      printf("[AlarmSystem] Alarm: %s\n", event);
}
void creat_Alarm(Alarm *Sys)
{
    Sys->base.update = Alarm_update;
    Sys->base.data = NULL;
}






















