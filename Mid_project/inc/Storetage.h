#ifndef STORETAGE_H
#define STORETAGE_H

    #define SECTOR_SIZE 512

    typedef struct {
        unsigned long reads;
        unsigned long read_sectors;
        unsigned long writes;
        unsigned long write_sectors;
    } Disk_Status;

    void get_disk_usage(const char *path);
    void get_disk_io(const char *device);

#endif