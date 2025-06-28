#include <stdio.h>
#include "../inc/Publisher.h"
#include "../inc/Subscriber.h"
#include <string.h>

void Subscriber(Publisher *self, Subscribers* s)
{
    if(self->count<max_sub)
    {
        self->Subscriber[self->count ++ ] = s;
    }
}

void unSubscriber(Publisher *self, Subscribers *s)
{
    int i,j;
    for( i=0; i< self->count ;i++){
        if( self->Subscriber[i] == s)
        {
            for( j=i; j<=self->count -1 ;j++)
            {
                self->Subscriber[j] = self->Subscriber[j+1];
            }
            self->count -- ;
            break;
        }
    }
}


void notifys( Publisher* self,const char *event)
{
    for(int i=0;i <= self->count;i++)
    {
        if(self->Subscriber[i]){
            self->Subscriber[i]->update(self->Subscriber[i],self,event);  
        }
    }
}


Publisher creat_pub(Publisher *Publishers)
{
    memcpy(Publishers->Subscriber,0,sizeof(Publisher));
    Publishers->count = 0;
    Publishers->sub =Subscriber;
    Publishers->unsub =unSubscriber;
    Publishers->notify = notifys;
}







