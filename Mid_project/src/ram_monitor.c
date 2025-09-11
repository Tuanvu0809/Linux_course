#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../inc/ram_monitor.h"
static ram_usage_instance_t *ram_manager_memory ;

static double ram_percent_calculate(unsigned long long index , unsigned long long total)
{
    return (double) index * 100 /(double) total;
} 

static ram_usage_instance_t *ram_usage_init()
{
    if(ram_manager_memory != NULL)
    {
        return ram_manager_memory;
    }
    ram_manager_memory = malloc(sizeof(ram_usage_instance_t));
    if(ram_manager_memory == NULL)
    {
        perror("malloc failed\n");
        return NULL;
    }
    memset(&ram_manager_memory->memory_total,0,sizeof(unsigned long));
    memset(&ram_manager_memory->memory_free,0,sizeof(unsigned long));
    memset(&ram_manager_memory->memory_used,0,sizeof(unsigned long));
    memset(&ram_manager_memory->buffer,0,sizeof(unsigned long));
    memset(&ram_manager_memory->cached,0,sizeof(unsigned long));
    memset(&ram_manager_memory->swap_total,0,sizeof(unsigned long));
    memset(&ram_manager_memory->swap_free,0,sizeof(unsigned long));
    memset(&ram_manager_memory->swap_used,0,sizeof(unsigned long));

    return ram_manager_memory;
}

static int ram_process_use_most_read(ram_process_parameter_t *process, int top_n) 
{
    struct dirent *entry; 
    int count = 0;
    int pid;
    char status_path[64];
    char line[MAX_NAME_PROCESS_LEN], name[MAX_NAME_PROCESS_LEN] = "";
    unsigned long Ram_usage = 0;
    int min_idx = 0;

    DIR *dir = opendir(PROC_RAM_DIR);
    if (!dir) return 0;

    while ((entry = readdir(dir))) 
    {
        if (!isdigit(entry->d_name[0])) continue;

        pid = atoi(entry->d_name);           
        snprintf(status_path, sizeof(status_path), PROC_RAM_PROCESS_DIR , pid); 

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
                process[count].pid = pid;
                strcpy(process[count].process_name, name);
                process[count].Memory = Ram_usage;
                count++;
            } else {
                for (int i = 1; i < top_n; i++) 
                    {
                        if (process[i].Memory < process[min_idx].Memory)
                        {
                            min_idx = i;
                        }    
                    }
                if (Ram_usage > process[min_idx].Memory) 
                    {
                        process[min_idx].pid = pid;
                        strcpy(process[min_idx].process_name, name);
                        process[min_idx].Memory = Ram_usage;
                    }
            }
        }
    }
    return count;
}    

static int ram_usage_read()
{
    FILE *fp = fopen( PROC_MEMEMORY_INFO , "r");
    if (!fp) {
        perror("Cannot open /proc/meminfo");
        return -1 ;
    }
    char label[64];
    ram_manager_memory = ram_usage_init();

    while (!feof(fp))
    {
        fscanf(fp, "%s", label);
        if (strcmp(label, "MemTotal:") == 0)
            fscanf(fp, "%lu", &ram_manager_memory->memory_total);
        else if (strcmp(label, "MemFree:") == 0)
            fscanf(fp, "%lu", &ram_manager_memory->memory_free);
        else if (strcmp(label, "Buffers:") == 0)
            fscanf(fp, "%lu", &ram_manager_memory->buffer);
        else if (strcmp(label, "Cached:") == 0)
            fscanf(fp, "%lu", &ram_manager_memory->cached);
        if (strcmp(label, "SwapTotal:") == 0)
            fscanf(fp, "%lu", &ram_manager_memory->swap_total);
        else if (strcmp(label, "SwapFree:") == 0)
            fscanf(fp, "%lu", &ram_manager_memory->swap_free);
    }
    fclose(fp);
    ram_manager_memory->memory_used = ram_manager_memory->memory_total - ram_manager_memory->memory_free - ram_manager_memory->buffer - ram_manager_memory->cached;
    ram_manager_memory->swap_used = ram_manager_memory->swap_total - ram_manager_memory->swap_free;
    return 0;

}

void ram_display()
{
    double percent_ram = 0; 
    double percent_usage = 0;
    if(ram_usage_read()==-1)
    {
        printf("fail read ram usage\n");
        return;
    }

    printf("Total: %lu MB\n", ram_manager_memory->memory_total/ 1024);
    printf("Free : %lu MB\n", ram_manager_memory->memory_free/ 1024);
    printf("Cache : %lu MB\n",ram_manager_memory->cached/1024);
    printf("Buffer : %lu MB\n",ram_manager_memory->buffer/1024);
    printf("Used : %lu MB\n", ram_manager_memory->memory_used / 1024);
  
    printf("\nSwap Usage:\n"); 
    printf("Total: %lu MB\n", ram_manager_memory->swap_total/ 1024);
    printf("Free : %lu MB\n", ram_manager_memory->swap_free/ 1024);
    printf("Used : %lu MB\n", ram_manager_memory->swap_used/ 1024);

    percent_ram= ram_percent_calculate(ram_manager_memory->memory_used,ram_manager_memory->memory_total);
    percent_usage= ram_percent_calculate(ram_manager_memory->swap_used,ram_manager_memory->swap_total);
    if(percent_ram > 50 && percent_ram <80 )
    {
        log_message(LOG_NOTICE, "ram medium");
    }
    else if (percent_ram >= 80)
    {
        log_message(LOG_WARNING ,"ram high");
    }
    else if(percent_ram >= 80)
    {
        log_message(LOG_ALERT,"ram high");
    }

    if(percent_usage > 50 && percent_usage <80 )
    {
        log_message(LOG_NOTICE, "ram medium");
    }
    else if (percent_usage >= 80)
    {
        log_message(LOG_WARNING ,"ram high");
    }
    else if(percent_usage >= 80)
    {
        log_message(LOG_ALERT,"ram high");
    }
}

void ram_process_use_most()
{
    int count = ram_process_use_most_read(ram_manager_memory->processes, TOP_5_PROCESS_USE_RAM_MOST);
    printf("Top %d apps that use the most RAM\n",count);
    for (int i = 0; i < count; i++) 
    {
        printf("%2d. PID: %-5d  %-20s  %6lu KB\n",i + 1, ram_manager_memory->processes[i].pid, ram_manager_memory->processes[i].process_name, ram_manager_memory->processes[i].Memory);
    }
}

ram_manager_t *ram_manage_creat()
{
    ram_manager_t *Creat = malloc(sizeof(ram_manager_t));
    ram_manager_memory = ram_usage_init() ;
    Creat->data = ram_manager_memory;
    Creat->ram_memory_display = ram_display;
    Creat->process_usage_ram_most_display = ram_process_use_most;
    return Creat;
}

