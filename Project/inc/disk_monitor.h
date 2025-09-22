#ifndef DISK_H
#define DISK_H
#include "log.h"

#define DISK_SECTOR_SIZE                512
#define DISK_MONITOR_SAMPLE_INTERVAL_S           1

static const char *const PROC_STAT_DISK =  "/proc/diskstats";
static const char *const PATH_FOLDER = "/";
typedef struct{
    unsigned long total;
    unsigned long free;
    unsigned long used;
}  disk_snap_t;

typedef struct {
    disk_snap_t *data;
    void (*disk_display)();
  
} disk_manager_t;

disk_manager_t *disk_manage_creat();


#endif