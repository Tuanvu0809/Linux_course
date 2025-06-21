#include <stdio.h>

#include "../../inc/sub/mobile.h"

void Mobile_update(Subscribers *self,Publisher *context, char *event )
{
    (void *) self;
    (void *) context;
      printf("[Mobile] Mobile: %s\n", event);
}

void creat_mobile(Mobile *app)
{
    app->base.update = Mobile_update;
    app->base.data = NULL;
}