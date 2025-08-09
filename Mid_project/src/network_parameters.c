#include "../inc/network_parameters.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

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



   