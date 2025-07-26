
#include<stdio.h>
#include <stdint.h>
#include "../inc/XOR.h"

#include <stdlib.h>

int xor_send(void* instance, const uint8_t* data, size_t length) {
    EncryptChannel* ctx = (EncryptChannel*)instance;
    uint8_t* temp = malloc(length);
    if (!temp) return -1;
    for (size_t i = 0; i < length; i++)
        temp[i] = data[i] ^ ctx->key;
    int result = ctx->inner->send(ctx->inner->instance, temp, length);
    free(temp);
    return result;
}

int xor_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    EncryptChannel* ctx = (EncryptChannel*)instance;
    uint8_t temp[256];
    size_t len;
    int result = ctx->inner->receive(ctx->inner->instance, temp, bufferLength, &len);
    if (result <= 0) return result;
    for (size_t i = 0; i < len; i++)
        buffer[i] = temp[i] ^ ctx->key;
    *receivedLength = len;
    return result;
}

Channel create_encrypt_channel(Channel* inner, uint8_t key) {
    EncryptChannel* ctx = malloc(sizeof(EncryptChannel));
    ctx->inner = inner;
    ctx->key = key;
    Channel ch = {
        .send = xor_send,
        .receive = xor_receive,
        .instance = ctx
    };
    return ch;
}
