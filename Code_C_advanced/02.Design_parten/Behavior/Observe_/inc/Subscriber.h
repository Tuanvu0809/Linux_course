#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

struct Publisher;

typedef struct Subscribers
{
    void (*Update)(struct Subscribers *self, struct Publisher *publish, const char *event);
    void *data;

} Subscribers;

#endif