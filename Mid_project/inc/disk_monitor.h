#ifndef DISK_H
#define DISK_H
#include "log.h"

/*macro*/
#define DISK_SECTOR_SIZE                512
// #define READ_DISK_STAT                      "/proc/diskstats"
#define DISK_MONITOR_SAMPLE_INTERVAL_S           1
// #define PATH_FOLDER                         "/"
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