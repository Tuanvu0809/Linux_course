#include <stdio.h>
#include <stdlib.h>
#include "factory.h"
#include "../temp/temp.h"
#include "../light/light.h"

sensor* CreatSensor(sensor_type type)
{
    sensor* sen = (sensor*) malloc(sizeof(sensor));
    if( sen == NULL ){
        return NULL;
    }
    switch(type)
    {
        case temp:
            *sen = createmp();
            break;
        case light:
            *sen = creatlight();
            break;
        default:
            free(sen);
            return NULL;
            
    }
    return sen;
}