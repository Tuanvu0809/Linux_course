#ifndef NETWORK_H
#define NETWORK_H
#include "Log.h"

/*struct*/
typedef struct{
    unsigned long long RX_byte;
    unsigned long long TX_byte;
} Network_speed;


#define Read_status_rx_tx_byte  "/proc/net/dev"

void NETWORK_INFO_CHECK();

#endif

