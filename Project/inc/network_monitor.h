#ifndef NETWORK_H
#define NETWORK_H
#include "log.h"
#include <net/if.h>       
#include <sys/socket.h>    
#include <netinet/in.h>   
#include <netdb.h> 

#define NETWORK_MONITOR_SAMPLE_INTERVAL_S        1

static const char *const PROC_NETWORK_STAT = "/proc/net/dev";

/*struct*/
typedef struct{
    unsigned long long RX_byte;
    unsigned long long TX_byte;
} network_parameter_t;

typedef struct{
    double  upload_speed;
    double  download_speed;
} network_instance_t;

typedef struct{
    network_instance_t *data;
    void (*network_speed_display)();
    void (*network_ip_display )();
}  network_mananager_t;

 network_mananager_t *network_manage_creat();
#endif

