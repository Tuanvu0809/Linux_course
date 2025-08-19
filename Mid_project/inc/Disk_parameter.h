#ifndef DISK_PARAMETER_H
#define DISK_PARAMETER_H
#include "Log.h"

/*macro*/
#define SECTOR_SIZE 512
#define READ_DISK_STAT "/proc/diskstats"
    /*Struct*/    
typedef struct {
    unsigned long reads;
    unsigned long read_sectors;
    unsigned long writes;
    unsigned long write_sectors;
} Disk_Status;

/*Function user can use*/
void DISK_INFO_CHECK();
#endif