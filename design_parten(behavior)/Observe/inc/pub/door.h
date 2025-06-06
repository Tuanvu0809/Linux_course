#ifndef DOOR_H
#define DOOR_H
   
    #include "inc/publisher.h"

    typedef enum{
        open=0,
        close,
    }door_status;



    typedef struct{
        Publisher base;
        door_status isopen;

    }door_sensor;

    void Creat_door_sensor(door_sensor *sensor);
    void trigger_d(door_sensor *sensor, door_status is_open);

#endif    