#ifndef LOG_H
#define LOG_H

#include "communicate.h"

typedef struct {
    Channel* inner;
} LoggingChannel;
Channel create_logging_channel(Channel* inner);
#endif