#ifndef NETWORK_H
#define NETWORK_H
#include "Log.h"
#include <net/if.h>       
#include <sys/socket.h>    
#include <netinet/in.h>   
#include <netdb.h> 

#define Read_status_rx_tx_byte  "/proc/net/dev"
#define TIME_CALCULATE_ONE_SERCOND      1

/*struct*/
typedef struct{
    unsigned long long RX_byte;
    unsigned long long TX_byte;
} network_parameter;

typedef struct{
    double  upload_speed;
    double  dowload_speed;
} network_instance;

typedef struct{
    network_instance *data;
    void (*network_speed_display)();
    void (*network_ip_display )();
} network_mananage;

network_mananage *network_manage_creat();
#endif

