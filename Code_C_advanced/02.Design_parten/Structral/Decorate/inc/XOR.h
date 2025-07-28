#ifndef XOR_H
#define XOR_H
#include<stdint.h>
#include "communicate.h"
typedef struct {
    Channel* inner;
    uint8_t key;
} EncryptChannel;
Channel create_encrypt_channel(Channel* inner, uint8_t key);
#endif