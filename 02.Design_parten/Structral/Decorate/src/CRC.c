#include<stdio.h>
#include <stdint.h>
#include "../inc/CRC.h"
#include "string.h"
#include <stdlib.h>
// CRC đơn giản XOR toàn bộ dữ liệu
uint8_t compute_crc8(const uint8_t* data, size_t length) {
    uint8_t crc = 0;
    for (size_t i = 0; i < length; i++)
        crc ^= data[i];
    return crc;
}

int crc_send(void* instance, const uint8_t* data, size_t length) {
    CRCChannel* ctx = (CRCChannel*)instance;
    uint8_t* temp = malloc(length + 1);
    if (!temp) return -1;
    memcpy(temp, data, length);
    temp[length] = compute_crc8(data, length);  // Thêm CRC
    int result = ctx->inner->send(ctx->inner->instance, temp, length + 1);
    free(temp);
    return result;
}

int crc_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    CRCChannel* ctx = (CRCChannel*)instance;
    uint8_t temp[256];
    size_t len;
    int result = ctx->inner->receive(ctx->inner->instance, temp, sizeof(temp), &len);
    if (result <= 0 || len < 1) return -1;
    uint8_t crc = temp[len - 1];
    if (compute_crc8(temp, len - 1) != crc) return -2; // CRC sai
    memcpy(buffer, temp, len - 1);
    *receivedLength = len - 1;
    return *receivedLength;
}

Channel create_crc_channel(Channel* inner) {
    CRCChannel* ctx = malloc(sizeof(CRCChannel));
    ctx->inner = inner;
    Channel ch = {
        .send = crc_send,
        .receive = crc_receive,
        .instance = ctx
    };
    return ch;
}
