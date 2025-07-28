#ifndef ALARM_H
#define ALARM_H
#include "..\Publisher.h"
#include "..\Subscriber.h"

typedef struct
{
    Subscribers base;
} Alarm;

void Creat_Alarm(Alarm *System);
void Alarm_update(Subscribers *self, Publisher *context, char *event);

#endif