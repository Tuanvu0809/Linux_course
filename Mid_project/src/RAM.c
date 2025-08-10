#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../inc/RAM.h"

 
static int top_ram_processes(RAM_Process top_process[], int top_n) {
    DIR *dir = opendir(READ_PROCESS);
    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir))) {
        if (!isdigit(entry->d_name[0])) continue;

        int pid = atoi(entry->d_name);
        char status_path[64];
        snprintf(status_path, sizeof(status_path), READ_PROCESS_STATUS , pid);

        FILE *fp = fopen(status_path, "r");
        if (!fp) continue;

        char line[256], name[256] = "";
        unsigned long vmrss = 0;

        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "Name:", 5) == 0)
                sscanf(line, "Name: %s", name);
            else if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line, "VmRSS: %lu", &vmrss);  // RAM usage in KB
                break;
            }
        }
        fclose(fp);

        if (vmrss > 0) {
            if (count < top_n) {
                top_process[count].pid = pid;
                strcpy(top_process[count].name, name);
                top_process[count].Memory_kb = vmrss;
                count++;
            } else {
                int min_idx = 0;
                for (int i = 1; i < top_n; i++) {
                    if (top_process[i].Memory_kb < top_process[min_idx].Memory_kb)
                        min_idx = i;
                }
                if (vmrss > top_process[min_idx].Memory_kb) {
                    top_process[min_idx].pid = pid;
                    strcpy(top_process[min_idx].name, name);
                    top_process[min_idx].Memory_kb = vmrss;
                }
            }
        }
    }

    closedir(dir);

    // Sắp xếp giảm dần
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (top_process[i].Memory_kb < top_process[j].Memory_kb) {
                RAM_Process tmp = top_process[i];
                top_process[i] = top_process[j];
                top_process[j] = tmp;
            }
        }
    }

    return count;
}


static void get_ram_usage() {
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

    unsigned long used = Memory_total - Memory_free - buffers - cached;

    printf(" RAM Usage:\n");
    printf(" Total: %lu MB\n", Memory_total / 1024);
    printf("Used : %lu MB\n", used / 1024);
    printf("Free : %lu MB\n", Memory_free / 1024);
    printf("Cache : %lu MB\n",cached/1024);
}

static void get_swap_usage() {
    FILE *fp = fopen( READ_MEMORY_INFO , "r");
    if (!fp) {
        perror("Cannot open /proc/meminfo");
        return;
    }

    unsigned long swap_total = 0, swap_free = 0;
    char label[64];

    while (!feof(fp)) {
        fscanf(fp, "%s", label);
        if (strcmp(label, "SwapTotal:") == 0)
            fscanf(fp, "%lu", &swap_total);
        else if (strcmp(label, "SwapFree:") == 0)
            fscanf(fp, "%lu", &swap_free);
    }
    fclose(fp);

    unsigned long used = swap_total - swap_free;

    printf("\nSwap Usage:\n");
    printf("Total: %lu MB\n", swap_total / 1024);
    printf(" Used : %lu MB\n", used / 1024);
    printf(" Free : %lu MB\n", swap_free / 1024);
}

static void get_top_ram_processes() {
    RAM_Process processes[TOP_N];
    int count = top_ram_processes(processes, TOP_N);

    printf("\n Top %d processes by RAM usage:\n", count);
    for (int i = 0; i < count; i++) 
    {

        printf("%2d. PID: %-5d  %-20s  %6lu KB\n",i + 1, processes[i].pid, processes[i].name, processes[i].Memory_kb);
   
    }
}

void RAM_INFO_CHECK()
{
    printf("\n Check Ram\n");
    get_ram_usage();
    get_swap_usage();
    get_top_ram_processes();
}
