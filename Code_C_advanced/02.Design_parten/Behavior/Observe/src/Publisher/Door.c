#include "../../inc/Publisher/Door.h"

void Creat_door_sensor(Door_sensor *sensor)
{
    creat_publisher(&sensor->base);

    sensor->Current_status = open;
}

void Trigger_door(Door_sensor *sensor, Door_status status)
{
    sensor->Current_status = status;

    if (sensor->Current_status == open)
    {
        sensor->base.notify(&sensor->base, "Door open");
    }
    if (sensor->Current_status == close)
    {
        sensor->base.notify(&sensor->base, "Door Close");
    }
}