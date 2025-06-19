#ifndef SMOKE_H
#define SMOKE_H

    #include "publisher.h"

    typedef enum{
        havesmoke=0,
        nosmoke,
    }smoke_status;

    typedef struct{
        Publisher base;
        smoke_status ismoke;
        
    }smoke_sensor;

    
    void Creat_smoke_sensor(smoke_sensor *sensor);
    void trigger_s(smoke_sensor *sensor, smoke_status Have_smoke);


#endif    