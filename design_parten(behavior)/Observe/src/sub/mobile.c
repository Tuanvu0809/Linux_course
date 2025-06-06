#include <stdio.h>

#include "sub/mobile.h"



void Mobile_update(Sub *self,Publisher *context, char *event )
{
    (void *) self;
    (void *) context;
      printf("[Mobille] Mobile: %s\n", event);
}

void creat_mobile(Mobile *app)
{
    app->base.update = Mobile_update;
    app->base.data = NULL;
}