#ifndef DOOR_H
#define DOOR_H

#include "..\Publisher.h"

typedef enum
{
    open = 0,
    close,
} Door_status;

typedef struct
{
    Publisher base;
    Door_status Current_status;
} Door_sensor;
void Creat_door_sensor(Door_sensor *sensor);
void Trigger_door(Door_sensor *sensor, Door_status status);

#endif