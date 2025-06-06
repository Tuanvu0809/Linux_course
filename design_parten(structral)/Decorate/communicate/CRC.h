#ifndef CRC_H
#define CRC_H
    #include "communicate.h"
    typedef struct {
        Channel* inner;
    } CRCChannel;
    Channel create_crc_channel(Channel* inner);
#endif