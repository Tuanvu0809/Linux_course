#include "../inc/Publisher.h"
#include "../inc/Subscriber.h"
#include <stdio.h>
#include <string.h>
void subscriber_function(Publisher *self, Subscribers *s)
{
    if (self->count < MAX_SUBSCRIBERS)
    {
        self->subscribers[(self->count)++] = s;
    }
}

void unSubscriber_function(Publisher *self, Subscribers *s)
{
    for (int i = 0; i < self->count; i++)
    {
        if (self->subscribers[i] == s)
        {
            for (int j = i; j <= self->count - 1; j++)
            {
                self->subscribers[j] = self->subscribers[j + 1];
            }
            self->count--;
            break;
        }
    }
}

void notifys_function(Publisher *self, const char *event)
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
    Publishers->sub = subscriber_function;
    Publishers->unsub = unSubscriber_function;
    Publishers->notify = notifys_function;
}