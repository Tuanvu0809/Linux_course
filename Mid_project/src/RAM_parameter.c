#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../inc/RAM_parameter.h"
/*Hàm tính ứng dụng ram nhiều nhất*/
static int top_ram_processes(RAM_Process *top_process, int top_n) 
{
    /*Variable*/
    struct dirent *entry; 
    int count = 0;
    int pid;
    char status_path[64];
    char line[NAME_LEN], name[NAME_LEN] = "";
    unsigned long Ram_usage = 0;
    int min_idx = 0;

    /*Đọc các úng dụng đang sủ dụng*/
    DIR *dir = opendir(READ_PROCESS);
    if (!dir) return 0;

    while ((entry = readdir(dir))) 
    {
        if (!isdigit(entry->d_name[0])) continue;

        pid = atoi(entry->d_name);           
        snprintf(status_path, sizeof(status_path), READ_PROCESS_STATUS , pid); 

        FILE *fp = fopen(status_path, "r");
        if (!fp) continue;

        while (fgets(line, sizeof(line), fp))
        {
            if (strncmp(line, "Name:", 5) == 0)
            {
                sscanf(line, "Name: %s", name);   
            }    
            else if (strncmp(line, "VmRSS:", 6) == 0) 
            {
                sscanf(line, "VmRSS: %lu", &Ram_usage);  
                break;
            }
        }
        fclose(fp);

       
        if (Ram_usage > 0) {
            if (count < top_n)
            {
                top_process[count].pid = pid;
                strcpy(top_process[count].name, name);
                top_process[count].Memory_kb = Ram_usage;
                count++;
            } else {
            
                for (int i = 1; i < top_n; i++) 
                {
                    if (top_process[i].Memory_kb < top_process[min_idx].Memory_kb)
                    {
                        min_idx = i;
                    }    
                }
                if (Ram_usage > top_process[min_idx].Memory_kb) 
                {
                    top_process[min_idx].pid = pid;
                    strcpy(top_process[min_idx].name, name);
                    top_process[min_idx].Memory_kb = Ram_usage;
                }
            }
        }
    }

    closedir(dir); // đóng tiến trình
     /*Sắp xếp 5 Pid chiếu nhiều ram nhất*/
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++)
        {
            if (top_process[i].Memory_kb < top_process[j].Memory_kb) 
            {
                RAM_Process temporary = top_process[i];
                top_process[i] = top_process[j];
                top_process[j] = temporary;
            }
        }
    }
    return count;
}
/*Hàm đọc giá trị ram sử dụng*/
static void get_ram_usage()
{
    /*Đọc giá trị ram trong proc/meminfo */
    FILE *fp = fopen( READ_MEMORY_INFO , "r");
    if (!fp) {
        perror("Cannot open /proc/meminfo");
        return;
    }

    unsigned long Memory_total = 0, Memory_free = 0, buffers = 0, cached = 0;
    char label[64];

    while (!feof(fp)) {
        fscanf(fp, "%s", label);
        if (strcmp(label, "MemTotal:") == 0)
            fscanf(fp, "%lu", &Memory_total);
        else if (strcmp(label, "MemFree:") == 0)
            fscanf(fp, "%lu", &Memory_free);
        else if (strcmp(label, "Buffers:") == 0)
            fscanf(fp, "%lu", &buffers);
        else if (strcmp(label, "Cached:") == 0)
            fscanf(fp, "%lu", &cached);
    }
    fclose(fp);
    /*tính toán ram đã sử dụng*/
    unsigned long used = Memory_total - Memory_free - buffers - cached;

    printf(" RAM Usage:\n");
    printf(" Total: %lu MB\n", Memory_total / 1024);
    printf("Used : %lu MB\n", used / 1024);
    printf("Free : %lu MB\n", Memory_free / 1024);
    printf("Cache : %lu MB\n",cached/1024);

    
}
/*tính toán Swap Ram*/
static void get_swap_usage()
{
    unsigned long swap_total = 0, swap_free = 0;
    char label[64];
    unsigned long used;

    FILE *fp = fopen( READ_MEMORY_INFO , "r");
    if (!fp) {
        perror("Cannot open /proc/meminfo");
        return;
    }
   
    while (!feof(fp)) {
        fscanf(fp, "%s", label);
        if (strcmp(label, "SwapTotal:") == 0)
            fscanf(fp, "%lu", &swap_total);
        else if (strcmp(label, "SwapFree:") == 0)
            fscanf(fp, "%lu", &swap_free);
    }
    fclose(fp);

    used = swap_total - swap_free;

    printf("\nSwap Usage:\n");
    printf(" Total: %lu MB\n", swap_total / 1024);
    printf(" Used : %lu MB\n", used / 1024);
    printf(" Free : %lu MB\n", swap_free / 1024);
}
/*xếp hạng ứng dụng sử dung nhiều nhất ram  */
static void get_top_ram_processes() 
{
    RAM_Process processes[TOP_N];
    int count = top_ram_processes(processes, TOP_N);

    printf("\n Top %d processes by RAM usage:\n", count);
    for (int i = 0; i < count; i++) 
    {
        printf("%2d. PID: %-5d  %-20s  %6lu KB\n",i + 1, processes[i].pid, processes[i].name, processes[i].Memory_kb);
    }
}
/*Check Ram */
void RAM_INFO_CHECK()
{
    printf("\n Check Ram\n");
    get_ram_usage();
    get_swap_usage();
    get_top_ram_processes();
}
