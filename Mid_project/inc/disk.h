#ifndef DISK_H
#define DISK_H
#include "Log.h"

/*macro*/
#define SECTOR_SIZE 512
#define READ_DISK_STAT "/proc/diskstats"
#define TIME_CALCULATE_ONE_SERCOND      1
#define PATH_FOLDER             "/"

typedef struct{
    unsigned long total;
    unsigned long free;
    unsigned long used;
}  disk_instance;

typedef struct {
    disk_instance *data;
    void (*disk_display)();
  
} disk_manage;

disk_manage *disk_manage_creat();


#endif