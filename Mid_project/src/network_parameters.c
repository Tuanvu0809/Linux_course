#include "../inc/network_parameters.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>     
#include <ifaddrs.h>      
#include <arpa/inet.h>     
#include <netinet/in.h>   
#include <netdb.h> 

/*Rx bytes*/
static void rx_tx_bytes(uint64_t *rx , uint64_t *tx)
{
 
    FILE *fp = fopen("/proc/net/dev", "r");
     if (!fp) {
        perror("Failed to open /proc/net/dev");
        return ;
    }

    char line[512];

    do{
        fgets(line,sizeof(line),fp);

    } while (strncmp(line," ens33:",7) || (line== NULL));

    sscanf(line," ens33: %lu\t%*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%lu",rx,tx);
    
}

static double  speed(uint64_t speed_1, uint64_t speed_2, int second)
{
    return (double ) (speed_2 - speed_1) /(second * 1024 );
}

void get_dowload_upload_speed(int second)
{
    uint64_t rx1,rx2;
    uint64_t tx1,tx2;;
    double  upload_speed;
    double  dowload_speed;

    rx_tx_bytes(&rx1,&tx1);
    sleep(second);
    rx_tx_bytes(&rx2,&tx2);

    dowload_speed = speed(rx1,rx2,second);
    upload_speed = speed(tx1,tx2,second);

    printf("Dowload speed : %.3f  KB/s \n ", dowload_speed );
    printf("Upload speed : %.3f  KB/s \n ", upload_speed );
}

void get_ip_addresses() 
{
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs failed");
        return;
    }
    printf("\n[IP Addresses]\n");
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) continue;
        int family = ifa->ifa_addr->sa_family;
        char host[NI_MAXHOST];

        if (family == AF_INET || family == AF_INET6) {
            void *addr_ptr = NULL;
            if (family == AF_INET) {
                addr_ptr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
            } else {
                addr_ptr = &((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
            }
            if (inet_ntop(family, addr_ptr, host, sizeof(host))) {
                printf("  %-12s  %s (%s)\n",
                       ifa->ifa_name, host, family == AF_INET ? "IPv4" : "IPv6");
            }
        }
    }
    freeifaddrs(ifaddr);
}

   