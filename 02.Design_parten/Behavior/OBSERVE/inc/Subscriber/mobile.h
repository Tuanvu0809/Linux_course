#ifndef MOBILE_H
#define MOBILE_H
#include "..\Publisher.h"
#include "..\Subscriber.h"

typedef struct
{
    Subscribers base;
} Mobile;

void Creat_Mobile(Mobile *Sys);
void Mobile_update(Subscribers *self, Publisher *context, char *event);

#endif