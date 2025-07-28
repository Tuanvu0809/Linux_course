#ifndef LOG_H
#define LOG_H

#include "communicate.h"

typedef struct {
    Channel* inner;
} LoggingChannel;
Channel create_logging_channel(Channel* inner);
int log_send(void* instance, const uint8_t* data, size_t length) ;
int log_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);


#endif