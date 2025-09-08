#include "../inc/network_monitor.h"
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

static network_instance_t *network_speed_manage;

static network_instance_t *network_init()
{
    if(network_speed_manage != NULL)
    {
        return network_speed_manage;
    }

    network_speed_manage = malloc(sizeof(network_instance_t));

    if(network_speed_manage == NULL)
    {
        perror("malloc failed\n");// bỏ log mess
        return NULL;
    }

    memset(&network_speed_manage->upload_speed , 0, sizeof(double));
    memset(&network_speed_manage->dowload_speed , 0, sizeof(double));

    return network_speed_manage;

}


/*Rx Tx bytes*/
static void network_instance_read(network_parameter_t *Check)
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
static void network_parameter_read(int second)
{
    network_parameter_t previous;
    network_parameter_t after ;
   
    network_instance_read(&previous);
    sleep(second);
    network_instance_read(&after);

    network_speed_manage->dowload_speed = speed(previous.RX_byte,after.RX_byte,second);
    network_speed_manage->upload_speed = speed(previous.TX_byte,after.TX_byte,second);

}
/*Get IP*/
static void network_ip_address_read() 
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

void network_instance_display()
{
    printf("\nCheck Network\n");
    network_parameter_read(TIME_CALCULATE_ONE_SECOND);
    
    printf("\n[Dowload and upload Speed]\n");
    printf("Dowload speed : %.3f  KB/s \n ", network_speed_manage->dowload_speed );
    printf("Upload speed : %.3f  KB/s \n ",network_speed_manage->upload_speed );
    
}

network_mananage_t *network_manage_creat()
{
    network_mananage_t *Creat = malloc(sizeof(network_mananage_t));
    network_speed_manage= network_init();
    Creat->data = network_speed_manage;
    Creat->network_speed_display = network_instance_display;
    Creat->network_ip_display = network_ip_address_read;

    return Creat;

}

void network_speed_manage_free()
{
    if(network_speed_manage == NULL)
        return;
    free(network_speed_manage);
    printf("\nfree manage network sucess\n");
    printf("\n============\n");
}