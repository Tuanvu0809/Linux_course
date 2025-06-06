#ifndef SUBCRIBER_H
#define SUBCRIBER_H
   
    #include "publisher.h"
    typedef struct{
        void (*update)(struct sub *self, Publisher *con, const char *eventInfo);
        void (*data);
    }Sub;

#endif