#include "../inc/network_parameters.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

/*Rx bytes*/
static uint64_t rx_bytes()
{
    uint64_t *rx = (uint64_t *) malloc(sizeof(uint64_t));

    FILE *fp = fopen("/proc/net/dev", "r");
     if (!fp) {
        perror("Failed to open /proc/net/dev");
        return -1;
    }

    char line[512];

    do{
        fgets(line,sizeof(line),fp);

    } while (strncmp(line," ens33:",7) || (line== NULL));

    sscanf(line," ens33: %lu",rx);


    return *rx;
}

/*tx bytes*/
static uint64_t tx_bytes()
{
    uint64_t *tx = (uint64_t *) malloc(sizeof(uint64_t));

    FILE *fp = fopen("/proc/net/dev", "r");
     if (!fp) {
        perror("Failed to open /proc/net/dev");
        return -1;
    }

    char line[512];
    do{
        fgets(line,sizeof(line),fp);

    } while (strncmp(line," ens33:",7) || (line== NULL));

    sscanf(line," ens33: %*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%*d\t%lu",tx);

    return *tx;
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

    rx1 = rx_bytes();
    tx1 = tx_bytes();
    sleep(second);
    rx2 = rx_bytes();
    tx2 = tx_bytes(); 

    dowload_speed = speed(rx1,rx2,second);
    upload_speed = speed(tx1,tx2,second);

    printf("Dowload speed : %.3f  KB/s \n ", dowload_speed );
    printf("Upload speed : %.3f  KB/s \n ", upload_speed );
}



   