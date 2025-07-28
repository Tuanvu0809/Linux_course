#ifndef FACTORY_H
#define FACTORY_H
    #include "sensor.h"
    
    typedef enum{
        temp,
        light,
    }sensor_type;

    sensor* CreatSensor(sensor_type type);

#endif