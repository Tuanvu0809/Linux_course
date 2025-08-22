#ifndef DISK_H
#define DISK_H
#include "Log.h"

/*macro*/
#define SECTOR_SIZE 512
#define READ_DISK_STAT "/proc/diskstats"
#define TIME_CALCULATE_ONE_SERCOND      1

/*Struct*/    
typedef struct {
    unsigned long reads;
    unsigned long read_sectors;
    unsigned long writes;
    unsigned long write_sectors;
} disk_parameter;

typedef struct{
    unsigned long total;
    unsigned long free;
    unsigned long used;

} io_parameter;

typedef struct {
    disk_parameter disk_before;
    disk_parameter disk_after;
    double read_MB;
    double write_MB;
    io_parameter    io;
} disk_information;

/*Function user can use*/
void DISK_INFO_CHECK();
#endif