#ifndef PUBLISHER_H
#define PUBLISHER_H
    #include "subcriber.h"
    #define max_sub 10
    typedef struct Publisher
    {   
        Sub *subcriber[max_sub];
        int count;

        void (*sub) (struct Publisher *self, Sub *s);
        void (*unsub) (struct Publisher *self, Sub *s);
        void (*notify) (struct Publisher *self, const char *s);
    
        
    }Publisher;
    
    Publisher creat_pub(Publisher *Publishers);

#endif