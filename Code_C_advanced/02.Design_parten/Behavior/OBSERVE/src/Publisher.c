#include "../inc/Publisher.h"
#include "../inc/Subscriber.h"
#include <stdio.h>
#include <string.h>
void Subscriber_Fuction(Publisher *self, Subscribers *s)
{
    if (self->count < MAX_SUBSCRIBERS)
    {
        self->subscribers[(self->count)++] = s;
    }
}

void unSubscriber_Fuction(Publisher *self, Subscribers *s)
{
    int i, j;
    for (i = 0; i < self->count; i++)
    {
        if (self->subscribers[i] == s)
        {
            for (j = i; j <= self->count - 1; j++)
            {
                self->subscribers[j] = self->subscribers[j + 1];
            }
            self->count--;
            break;
        }
    }
}

void notifys_Fuction(Publisher *self, const char *event)
{
    for (int i = 0; i <= self->count; i++)
    {
        if (self->subscribers[i])
        {
            self->subscribers[i]->Update(self->subscribers[i], self, event);
        }
    }
}

void creat_publisher(Publisher *Publishers)
{
    memset(Publishers, 0, sizeof(Publisher));
    Publishers->count = 0;
    Publishers->sub = Subscriber_Fuction;
    Publishers->unsub = unSubscriber_Fuction;
    Publishers->notify = notifys_Fuction;
}