#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <ctype.h>
#include "../inc/disk.h"
static disk_instance_t *disk_memory_manage ;

static disk_instance_t *disk_init()
{
    if(disk_memory_manage != NULL)
    {
        return disk_memory_manage;
    }
    disk_memory_manage = malloc(sizeof(disk_instance_t));

    memset(&disk_memory_manage->total, 0, sizeof(unsigned long));
    memset(&disk_memory_manage->free, 0, sizeof(unsigned long));
    memset(&disk_memory_manage->used, 0, sizeof(unsigned long));

    return disk_memory_manage;
}
/*Tính toán dung lượng tổng của ổ đĩa*/
static void disk_usage_read (const char *path) {
    struct statvfs stat;
    if (statvfs(path, &stat) != 0) {
        perror("Failed to get disk usage");
        return;
    }
    disk_memory_manage->total= stat.f_blocks * stat.f_frsize;
    disk_memory_manage->free = stat.f_bfree * stat.f_frsize;
    disk_memory_manage->used = disk_memory_manage->total- disk_memory_manage->free;
}

void disk_display_read()
{
    printf("\nCheck disk\n");
    disk_memory_manage = disk_init();

    disk_usage_read(PATH_FOLDER);
    printf("\n[Disk Usage - %s]\n", PATH_FOLDER);
    printf("Total space: %lu MB\n", disk_memory_manage->total/ (1024 * 1024));
    printf("Used space : %lu MB\n", disk_memory_manage->used / (1024 * 1024));
    printf("Free space : %lu MB\n", disk_memory_manage->free / (1024 * 1024));
 
}

disk_manage_t *disk_manage_creat()
{
    disk_manage_t *Creat = malloc(sizeof(disk_manage_t));
    disk_memory_manage= disk_init();
    Creat->data = disk_memory_manage;
    Creat->disk_display = disk_display_read;
    return Creat;
}
