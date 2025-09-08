#ifndef DISK_H
#define DISK_H
#include "log.h"

/*macro*/
#define SECTOR_SIZE                         512
#define READ_DISK_STAT                      "/proc/diskstats"
#define TIME_CALCULATE_ONE_SECOND           1
#define PATH_FOLDER                         "/"

typedef struct{
    unsigned long total;
    unsigned long free;
    unsigned long used;
}  disk_instance_t;

typedef struct {
    disk_instance_t *data;
    void (*disk_display)();
  
} disk_manage_t;

disk_manage_t *disk_manage_creat();


#endif