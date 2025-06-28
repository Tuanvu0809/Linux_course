#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
   
   // #include "Publisher.h"
    
    // typedef struct Subscribers Subscribers;
    struct Publisher;
     
    typedef struct{
        void (*update)(struct Subscribers *self,struct Publisher* con, const char *eventInfo);
        void (*data);
    }Subscribers;

   // typedef struct Publisher;
  

   
 

#endif