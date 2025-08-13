#include "../inc/Network_parameters.h"
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

/*Rx Tx bytes*/
static void rx_tx_bytes(Network_speed *Check)
{
    FILE *fp = fopen( Read_status_rx_tx_byte , "r");
     if (!fp) {
        perror("Failed to open /proc/net/dev");
        return ;
    }

    char line[512];

    do{
        fgets(line,sizeof(line),fp);

    } while (strncmp(line," ens33:",7) || (line== NULL));

    sscanf(line," ens33: %llu\t%*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%llu",&Check->RX_byte,&Check->TX_byte);
    fclose(fp);
}
/*calculate speed*/
static double  speed(  unsigned long long speed_1,   unsigned long long speed_2, int second)
{
    return (double ) (speed_2 - speed_1) /(second * 1024 );
}
/*Calculate speed dowload and upload*/
static void get_dowload_upload_speed(int second)
{
    Network_speed previous;
    Network_speed after ;
    double  upload_speed;
    double  dowload_speed;

    rx_tx_bytes(&previous);
    sleep(second);
    rx_tx_bytes(&after);

    dowload_speed = speed(previous.RX_byte,after.RX_byte,second);
    upload_speed = speed(previous.TX_byte,after.TX_byte,second);

    printf("\n[Dowload and upload Speed]\n");
    printf("Dowload speed : %.3f  KB/s \n ", dowload_speed );
    printf("Upload speed : %.3f  KB/s \n ", upload_speed );
}
/*Get IP*/
static void get_ip_addresses() 
{
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1) {
        perror("Getifaddrs failed");
        return;
    }

    printf("\n[IP Addresses]\n");
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) continue;

        int family = ifa->ifa_addr->sa_family;
        char host[NI_MAXHOST];

        if (family == AF_INET || family == AF_INET6) {
            void *addr_ptr = NULL;

            if (family == AF_INET) 
            {
                addr_ptr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
                
            } else
            {
                addr_ptr = &((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
            }
            if (inet_ntop(family, addr_ptr, host, sizeof(host))) 
            {
                printf("  %-12s  %s (%s)\n", ifa->ifa_name, host, family == AF_INET ? "IPv4" : "IPv6");
            }
        }
    }
    freeifaddrs(ifaddr);
}

void NETWORK_INFO_CHECK()
{
    printf("\nCheck Network\n");
    
    get_dowload_upload_speed(TIME_CALCULATE);
    get_ip_addresses();
}