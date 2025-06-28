#ifndef PUBLISHER_H
#define PUBLISHER_H
   
    //#include "Subscriber.h"
    #define max_sub     10  

    struct Subscribers;


   
    typedef struct
    {   
       
        void (*sub) (struct Publisher *self,struct Subscribers *s);
        void (*unsub) (struct Publisher *self,struct Subscribers *s);
        void (*notify) (struct Publisher *self, const char *s);
        
        struct Subscribers *Subscriber[max_sub];
        int count;

        
    }Publisher;

    
    Publisher creat_pub(Publisher *Publishers);

#endif