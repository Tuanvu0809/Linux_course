#include "../../inc/Subscriber/mobile.h"
#include <stdio.h>
void Mobile_update(Subscribers *self, Publisher *context, char *event)
{
    (void)self;
    (void)context;
    printf("[MobileSystem] Mobile: %s\n", event);
}

void Creat_Mobile(Mobile *System)
{
    System->base.Update = (void *)Mobile_update;
    System->base.data = NULL;
}