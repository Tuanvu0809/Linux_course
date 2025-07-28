#ifndef SMOKE_H
#define SMOKE_H
#include "..\Publisher.h"

typedef enum
{
    No_smoke = 0,
    Smoke,
} Smoke_status;

typedef struct
{
    Publisher base;
    Smoke_status Current_status;
} Smoke_sensor;
void Creat_smoke_sensor(Smoke_sensor *sensor);
void Trigger_smoke(Smoke_sensor *sensor, Smoke_status status);

#endif