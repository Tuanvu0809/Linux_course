#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../inc/communicate.h"

typedef struct {
    uint8_t buffer[256];
    size_t size;
} RawChannel;

int raw_send(void* instance, const uint8_t* data, size_t length) {
    RawChannel* ch = (RawChannel*)instance;
    if (length > sizeof(ch->buffer)) return -1;
    memcpy(ch->buffer, data, length);
    ch->size = length;
    return length;
}

int raw_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    RawChannel* ch = (RawChannel*)instance;
    if (ch->size > bufferLength) return -1;
    memcpy(buffer, ch->buffer, ch->size);
    *receivedLength = ch->size;
    return ch->size;
}

Channel create_raw_channel(Raw_data *raw)
{
    Channel ch;
    ch.send = raw_send;
    ch.receive = raw_receive;
    ch.instance = raw;
    return ch;
}
