#include <stdio.h>
#include "publisher.h"
#include <string.h>

void subcribe(Publisher *self, Sub* s)
{
    if(self->count<max_sub)
    {
        self->subcriber[self->count ++ ] = s;
    }
}

void unsubcribe(Publisher *self, Sub *s)
{
    int i,j;
    for( i=0; i< self->count ;i++){
        if( self->subcriber[i] == s)
        {
            for( j=i; j<=self->count -1 ;j++)
            {
                self->subcriber[j] = self->subcriber[j+1];
            }
            self->count -- ;
            break;
        }
    }
}


void notify(Publisher *self,const char *event)
{
    for(int i=0;i<=self->count;i++)
    {
        if(self->subcriber[i] && self->subcriber[i]->update){
            self->subcriber[i]->update(self->subcriber[i],self,event);
        }
    }


}


Publisher creat_pub(Publisher *Publishers)
{
    memcpy(Publishers->subcriber,0,sizeof(Publisher));
    Publishers->count = 0;
    Publishers->sub =subcribe;
    Publishers->unsub =unsubcribe;
    Publishers->notify = notify;
}







