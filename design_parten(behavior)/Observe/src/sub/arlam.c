
#include <stdio.h>

#include "sub/alarm.h"


void Arlam_update(Sub *self,Publisher *context, char *event )
{
    (void *) self;
    (void *) context;
      printf("[AlarmSystem] Alarm: %s\n", event);
}
void creat_Arlam(Alarm *Sys)
{
    Sys->base.update = Arlam_update;
    Sys->base.data = NULL;
}






















