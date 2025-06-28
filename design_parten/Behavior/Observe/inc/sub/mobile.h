#ifndef MOBILE_H
#define MOBILE_H
    #include "../Subscriber.h"
    #include "../Publisher.h"

    typedef struct{
        Subscribers base;
    }Mobile;    

    void creat_mobile(Mobile *app);
    void Mobile_update(Subscribers *self,Publisher *context, char *event );



   
#endif