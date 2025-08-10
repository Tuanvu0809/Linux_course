#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <ctype.h>
#include "../inc/Storetage.h"

static void get_disk_usage (const char *path) {
    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("Failed to get disk usage");
        return;
    }

    unsigned long total = stat.f_blocks * stat.f_frsize;
    unsigned long free = stat.f_bfree * stat.f_frsize;
    unsigned long used = total - free;

    printf("\n[Disk Usage - %s]\n", path);
    printf("Total space: %lu MB\n", total / (1024 * 1024));
    printf("Used space : %lu MB\n", used / (1024 * 1024));
    printf("Free space : %lu MB\n", free / (1024 * 1024));
}


int static get_disk_stats(const char *device, Disk_Status *stats) {
    FILE *fp = fopen(READ_DISK_STAT, "r");
    if (!fp) return -1;

    char line[512], dev[32];
     while (fgets(line, sizeof(line), fp)) {
        sscanf(line,"%*d\t%*d %s", dev);
           
        if (strcmp(dev, device) == 0) {
         
            sscanf(line, "%*d\t%*d %*s %lu %*u %lu %lu %*u %lu",
                   &stats->reads, &stats->read_sectors,
                   &stats->writes, &stats->write_sectors);

             fclose(fp);       
            return 0;
  
        }
    }
    fclose(fp);
    return -1;
}

static void get_disk_io(const char *device, int second) 
{
    Disk_Status stats1, stats2;

    if (get_disk_stats(device, &stats1) == -1) {
        printf("Cannot read disk stats for %s\n", device);
        return;
    }

    sleep(second);

    if (get_disk_stats(device, &stats2) == -1) {
        printf("Cannot read disk stats for %s\n", device);
        return;
    }

    unsigned long delta_reads = stats2.reads - stats1.reads;
    unsigned long delta_read_sectors = stats2.read_sectors - stats1.read_sectors;
    unsigned long delta_writes = stats2.writes - stats1.writes;
    unsigned long delta_write_sectors = stats2.write_sectors - stats1.write_sectors;

    float read_MB = delta_read_sectors * SECTOR_SIZE / (second *1024.0 * 1024.0);
    float write_MB = delta_write_sectors * SECTOR_SIZE / (second * 1024.0 * 1024.0);

    printf("\n[Disk I/O Statistics - %s]\n", device);
    printf("Read speed : %.2f MB/s (%lu IOPS)\n", read_MB, delta_reads);
    printf("Write speed: %.2f MB/s (%lu IOPS)\n", write_MB, delta_writes);
}

void DISK_INFO_CHECK()
{
    printf("\nCheck disk\n");

    int times;
    char disk[10];
    printf("disk: ");
    scanf("%9s", disk);          

    printf("delta times: ");
    scanf(" %d", &times);        

    get_disk_usage("/");
    get_disk_io(disk, times);

}