#include <stdio.h>
#include <stdlib.h>
#include "../inc/factory.h"
#include "../inc/temp.h"
#include "../inc/factory.h"
#include "../inc/light.h"

sensor* CreatSensor(sensor_type type)
{
    sensor* That_sensor = (sensor*) malloc(sizeof(sensor));
    if( That_sensor == NULL ){
        return NULL;
    }
    switch(type)
    {
        case temp:
            *That_sensor = creat_temp();
            break;
        case light:
            *That_sensor =  creat_light();
            break;
        default:
            free(That_sensor);
            return NULL;
            
    }
    return That_sensor;
}