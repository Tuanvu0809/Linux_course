#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include "../inc/CPU_parameter.h"

int read_core_stats(CPU_Core_Stat *cores, int *core_count) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return -1;

    char line[LINE];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "cpu", 3) == 0) {

                if (line[3] == ' ') {
                
                    sscanf(line, "cpu  %llu %llu %llu %llu %llu %llu %llu",
                        &cores[0].user, &cores[0].nice, &cores[0].system,
                        &cores[0].idle, &cores[0].iowait, &cores[0].irq,
                        &cores[0].softirq);
                
                } else if (isdigit(line[3])) {
                    int id;
                    sscanf(line, "cpu%d %llu %llu %llu %llu %llu %llu %llu",
                        &id,
                        &cores[count].user, &cores[count].nice, &cores[count].system,
                        &cores[count].idle, &cores[count].iowait, &cores[count].irq,
                        &cores[count].softirq);
                
            }
            count++;
        }

    }

    fclose(fp);
    *core_count = count;
    return 0;
}

void get_cpu_usages() {

    CPU_Core_Stat cores[MAX_CORES];

    int count = 0;
    unsigned long long total;

    if( read_core_stats(cores,&count) == -1)
    {
        printf("fail \n");
    }
    for (int i=0; i< count; i++)
    {
        total = 0;
        total = cores[i].user + cores[i].nice + cores[i].system + cores[i].idle + cores[i].iowait + cores[i].irq + cores[i].softirq;
        if(i!=0){
            printf("core %d = %.2f %% \n ", i-1,(float)( 100.0f * (total - (cores[i].idle + cores[i].iowait) ) / total) );
        }
        else {
            printf("core all = %.2f %% \n ",(float)( 100.0f * (total - (cores[i].idle + cores[i].iowait) ) / total) );
        }

    }
}

void get_cpu_frequencies() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) {
        perror("Cannot open /proc/cpuinfo");
        return;
    }

    char line[LINE];
    int core_id = -1;

    printf("\n[CPU Frequencies]\n");
    while (fgets(line, sizeof(line), fp)) {

        if (strncmp(line, "processor", 9) == 0) {
            sscanf(line, "processor\t: %d", &core_id);
        }

        if (strncmp(line, "cpu MHz", 7) == 0 && core_id >= 0) {
            float Freq;
            sscanf(line, "cpu MHz\t: %f", &Freq);
            printf("Core %d: %.4f MHz\n", core_id, Freq);
            core_id = -1; 
        }
    }
    fclose(fp);
}



static int top_cpu_processes(CPU_Process *Process, int top_n) {
    DIR *dir = opendir("/proc");
    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!isdigit(entry->d_name[0])) continue;

        int pid = atoi(entry->d_name);
        char path[64];
        snprintf(path, sizeof(path), "/proc/%d/stat", pid);

        FILE *fp = fopen(path, "r");
        if (!fp) continue;

        unsigned long utime = 0, stime = 0;
        char Name_of_pid[LINE];
        fscanf(fp, "%*d (%[^)]) %*c %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lu %lu", Name_of_pid, &utime, &stime);
        fclose(fp);

        float cpu = (utime + stime) / 100.0; 
        if (cpu < 0.1f) continue;

        if (count < top_n) {
            Process[count].pid = pid;
            strcpy(Process[count].name_pid, Name_of_pid);
            Process[count].cpu_usage = cpu;
            count++;
        } else {
       
            int min_idx = 0;
            for (int i = 1; i < top_n; i++) {
                if (Process[i].cpu_usage < Process[min_idx].cpu_usage)
                    min_idx = i;
            }
            if (cpu > Process[min_idx].cpu_usage) {
                Process[min_idx].pid = pid;
                strcpy(Process[min_idx].name_pid, Name_of_pid);
                Process[min_idx].cpu_usage = cpu;
            }
        }
    }

    closedir(dir);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (Process[i].cpu_usage < Process[j].cpu_usage) {
                CPU_Process temporary = Process[i];
                Process[i] = Process[j];
                Process[j] = temporary;
            }
        }
    }

    return count;
}

void get_top_cpu_processes() {
    CPU_Process processes[TOP_N];
    int count = top_cpu_processes(processes, TOP_N);
    printf("\nTop %d used CPU :\n", count);

    for (int i = 0; i < count; i++) {
        printf("%2d. PID: %d  %-20s CPU %.2f %%\n", i + 1, processes[i].pid, processes[i].name_pid, processes[i].cpu_usage);
    }
}


