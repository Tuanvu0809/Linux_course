#ifndef PUBLISHER_H
#define PUBLISHER_H
    #include "Subscriber.h"
    #define max_sub 10

    typedef struct Publisher;
 
    typedef struct
    {   
        Subscribers * Subscriber [max_sub];
        int count;

        void (*sub) (struct Publisher *self, Subscribers *s);
        void (*unsub) (struct Publisher *self, Subscribers *s);
        void (*notify) (struct Publisher *self, const char *s);
    
        
    }Publisher;
    
    Publisher creat_pub(Publisher *Publishers);

#endif