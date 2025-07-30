#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Subscriber.h"

#define MAX_SUBSCRIBERS 100

typedef struct Publisher
{
    void (*sub)(struct Publisher *self, Subscribers *s);
    void (*unsub)(struct Publisher *self, Subscribers *s);
    void (*notify)(struct Publisher *self, const char *event);

    Subscribers *subscribers[MAX_SUBSCRIBERS];
    int count;
} Publisher;

void creat_publisher(Publisher *Publishers);

#endif
