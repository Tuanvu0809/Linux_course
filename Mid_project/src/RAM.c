#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../inc/RAM.h"

void get_ram_usage() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("Cannot open /proc/meminfo");
        return;
    }

    unsigned long mem_total = 0, mem_free = 0, buffers = 0, cached = 0;
    char label[64];

    while (!feof(fp)) {
        fscanf(fp, "%s", label);
        if (strcmp(label, "MemTotal:") == 0)
            fscanf(fp, "%lu", &mem_total);
        else if (strcmp(label, "MemFree:") == 0)
            fscanf(fp, "%lu", &mem_free);
        else if (strcmp(label, "Buffers:") == 0)
            fscanf(fp, "%lu", &buffers);
        else if (strcmp(label, "Cached:") == 0)
            fscanf(fp, "%lu", &cached);
    }
    fclose(fp);

    unsigned long used = mem_total - mem_free - buffers - cached;

    printf(" RAM Usage:\n");
    printf(" Total: %lu MB\n", mem_total / 1024);
    printf("Used : %lu MB\n", used / 1024);
    printf("Free : %lu MB\n", mem_free / 1024);
    printf("Cache : %lu MB\n",cached/1024);
}

void get_swap_usage() {
    FILE *fp = fopen("/proc/meminfo", "r");
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
 



static int top_ram_processes(RAMProcess top_procs[], int top_n) {
    DIR *dir = opendir("/proc");
    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir))) {
        if (!isdigit(entry->d_name[0])) continue;

        int pid = atoi(entry->d_name);
        char status_path[64];
        snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);

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
                top_procs[count].pid = pid;
                strcpy(top_procs[count].name, name);
                top_procs[count].mem_kb = vmrss;
                count++;
            } else {
                int min_idx = 0;
                for (int i = 1; i < top_n; i++) {
                    if (top_procs[i].mem_kb < top_procs[min_idx].mem_kb)
                        min_idx = i;
                }
                if (vmrss > top_procs[min_idx].mem_kb) {
                    top_procs[min_idx].pid = pid;
                    strcpy(top_procs[min_idx].name, name);
                    top_procs[min_idx].mem_kb = vmrss;
                }
            }
        }
    }

    closedir(dir);

    // Sắp xếp giảm dần
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (top_procs[i].mem_kb < top_procs[j].mem_kb) {
                RAMProcess tmp = top_procs[i];
                top_procs[i] = top_procs[j];
                top_procs[j] = tmp;
            }
        }
    }

    return count;
}

void get_top_ram_processes() {
    RAMProcess processes[TOP_N];
    int count = top_ram_processes(processes, TOP_N);

    printf("\n Top %d processes by RAM usage:\n", count);
    for (int i = 0; i < count; i++) {
        printf("%2d. PID: %-5d  %-20s  %6lu KB\n",
               i + 1, processes[i].pid, processes[i].name, processes[i].mem_kb);
    }
}

