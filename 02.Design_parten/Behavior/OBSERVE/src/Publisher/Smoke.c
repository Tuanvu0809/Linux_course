#include "../../inc/Publisher/Smoke.h"

void Creat_smoke_sensor(Smoke_sensor *sensor)
{
    creat_publisher(&sensor->base);

    sensor->Current_status = No_smoke;
}

void Trigger_smoke(Smoke_sensor *sensor, Smoke_status status)
{
    sensor->Current_status = status;

    if (sensor->Current_status == No_smoke)
    {
        sensor->base.notify(&sensor->base, "No Smoke ");
    }
    if (sensor->Current_status == Smoke)
    {
        sensor->base.notify(&sensor->base, "Smoke");
    }
}