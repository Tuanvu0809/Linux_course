#ifndef SMOKE_H
#define SMOKE_H

    #include "../publisher.h"
    
    typedef enum{
        have_smoke=0,
        no_smoke,
    }smoke_status;

    typedef struct{
        Publisher base;
        smoke_status is_moke;
        
    }smoke_sensor;

    
    void Creat_smoke_sensor(smoke_sensor *sensor);
    void trigger_s(smoke_sensor *sensor, smoke_status Have_smoke);


#endif    