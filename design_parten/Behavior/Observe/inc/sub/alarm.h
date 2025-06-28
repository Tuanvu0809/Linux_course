#ifndef ALARM_H
#define ALARM_H
    #include "../Subscriber.h"
    #include "../Publisher.h"


    typedef struct{
        Subscribers base;
    }Alarm;

    void creat_Alarm(Alarm *Sys);
    void Alarm_update(Subscribers *self,Publisher *context, char *event );

    


#endif