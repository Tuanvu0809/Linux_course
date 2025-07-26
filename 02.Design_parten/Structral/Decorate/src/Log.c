#include<stdio.h>
#include <stdint.h>
#include "../inc/Log.h"

#include <stdlib.h>

int log_send(void* instance, const uint8_t* data, size_t length) {
    LoggingChannel* ctx = (LoggingChannel*)instance;
    printf("send %zu byte: ", length);
    for (size_t i = 0; i < length && i < 16; i++) printf("%02X ", data[i]);
    printf("\n");
    return ctx->inner->send(ctx->inner->instance, data, length);
}

int log_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    LoggingChannel* ctx = (LoggingChannel*)instance;
    int result = ctx->inner->receive(ctx->inner->instance, buffer, bufferLength, receivedLength);
    if (result > 0) {
        printf("Receive %zu byte: ", *receivedLength);
        for (size_t i = 0; i < *receivedLength && i < 16; i++) printf("%02X ", buffer[i]);
        printf("\n");
    }
    return result;
}

Channel create_logging_channel(Channel* inner) {
    LoggingChannel* ctx = malloc(sizeof(LoggingChannel));
    ctx->inner = inner;
    Channel ch = {
        .send = log_send,
        .receive = log_receive,
        .instance = ctx
    };
    return ch;
}
