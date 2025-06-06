#include <stdio.h>
#include "pub/door.h"


    void Creat_door_sensor(door_sensor *sensor)
    {
        creat_pub(&sensor->base);

        sensor->isopen = open;
    }
    void trigger_d(door_sensor *sensor, door_status is_open)
    {
        sensor->isopen = is_open;

        if(is_open == open )
        {
            sensor->base.notify(&sensor->base,"Door Open");
        }
        else
        {
            sensor->base.notify(&sensor->base,"Door Close");
        }



    }


