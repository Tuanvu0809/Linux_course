#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <ctype.h>
#include "../inc/Disk_parameter.h"

extern disk_information *disk_manage ;

double percent_calculate(unsigned long long index , unsigned long long total)
{
    return (double) index * 100 /(double) total;
} 

static disk_information *disk_init()
{
    if(disk_manage != NULL)
    {
        return disk_manage;
    }
    disk_manage = malloc(disk_information);
    
    memset(&disk_manage->disk_before.reads,0, sizeof(unsigned long));
    memset(&disk_manage->disk_before.read_sectors,0, sizeof(unsigned long));
    memset(&disk_manage->disk_before.writes,0, sizeof(unsigned long));
    memset(&disk_manage->disk_before.write_sectors,0, sizeof(unsigned long));

    memset(&disk_manage->disk_after.reads,0, sizeof(unsigned long));
    memset(&disk_manage->disk_after.read_sectors,0, sizeof(unsigned long));
    memset(&disk_manage->disk_after.writes,0, sizeof(unsigned long));
    memset(&disk_manage->disk_after.write_sectors,0, sizeof(unsigned long));

    disk_manage->read_MB = 0.0;
    disk_manage->write_MB = 0.0;
 
    memset(&disk_manage->io.total,0,sizeof(unsigned long));
    memset(&disk_manage->io.free,0,sizeof(unsigned long));
    memset(&disk_manage->io.used,0,sizeof(unsigned long));

    return disk_manage;
}
/*Tính toán dung lượng tổng của ổ đĩa*/
static void get_disk_usage (const char *path) {
    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("Failed to get disk usage");
        return;
    }

    unsigned long disk_manage->io.total= stat.f_blocks * stat.f_frsize;
    unsigned long disk_manage->io.free = stat.f_bfree * stat.f_frsize;
    unsigned long disk_manage->io.used = disk_manage->io.total- disk_manage->io.free;

    printf("\n[Disk Usage - %s]\n", path);
    printf("Total space: %lu MB\n", disk_manage->io.total/ (1024 * 1024));
    printf("Used space : %lu MB\n", disk_manage->io.used / (1024 * 1024));
    printf("Free space : %lu MB\n", disk_manage->io.free / (1024 * 1024));


}
/*IOPS*/
int static get_disk_stats(const char *device , disk_parameter *disk) {
    FILE *fp = fopen(READ_DISK_STAT, "r");
    if (!fp) return -1;

    char line[512], dev[32];
     while (fgets(line, sizeof(line), fp)) {
        sscanf(line,"%*d\t%*d %s", dev);
           
        if (strcmp(dev, device) == 0) {
         
            sscanf(line, "%*d\t%*d %*s %lu %*u %lu %lu %*u %lu",&disk->reads, &disk->read_sectors,&disk->writes, &disk->write_sectors);
            fclose(fp);       
            return 0;
        }
    }
    fclose(fp);
    return -1;
}
/*iops*/
static void get_disk_io(const char *device) 
{
    //disk_information disk_manage->disk_before, disk_manage->disk_after;
    unsigned long delta_reads;
    unsigned long delta_read_sectors;
    unsigned long delta_writes;
    unsigned long delta_write_sectors;
    //doubledisk_manage->read_MB,disk_manage->write_MB;

    if (get_disk_stats(device, &disk_manage->disk_before) == -1) {
        printf("Cannot read disk stats for %s\n", device);
        return;
    }

    sleep(TIME_CALCULATE_ONE_SERCOND);

    if (get_disk_stats(device, &disk_manage->disk_after) == -1) {
        printf("Cannot read disk stats for %s\n", device);
        return;
    }

    delta_reads = disk_manage->disk_after.reads - disk_manage->disk_before.reads;
    delta_read_sectors = disk_manage->disk_after.read_sectors - disk_manage->disk_before.read_sectors;

    delta_writes = disk_manage->disk_after.writes - disk_manage->disk_before.writes;
    delta_write_sectors = disk_manage->disk_after.write_sectors - disk_manage->disk_before.write_sectors;

    disk_manage->read_MB = delta_read_sectors * SECTOR_SIZE / (second *1024.0 * 1024.0);
   disk_manage->write_MB = delta_write_sectors * SECTOR_SIZE / (second * 1024.0 * 1024.0);

    printf("\n[Disk I/O Statistics - %s]\n", device);
    printf("Read speed : %.2f MB/s (%lu IOPS)\n",disk_manage->read_MB, delta_reads);
    printf("Write speed: %.2f MB/s (%lu IOPS)\n",disk_manage->write_MB, delta_writes);
}

void DISK_INFO_CHECK()
{
    printf("\nCheck disk\n");
    disk_manage = disk_init();



   

}