#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
   
  //  #include "Publisher.h"
    #include "Publisher.h"

    typedef struct{
        void (*update)(struct Subscribers *self,Publisher* con, const char *eventInfo);
        void (*data);
    }Subscribers;

#endif