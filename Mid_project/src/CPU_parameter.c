#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include "../inc/CPU_parameter.h"

int read_core_stats(CPU_Core_Stat *cores, int *core_count) {
    FILE *fp = fopen(READ_CORE_STAT, "r");
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
static unsigned long long total_target(CPU_Core_Stat cores)
{
    return cores.user + cores.nice + cores.system + cores.idle + cores.iowait + cores.irq + cores.softirq;

}

static unsigned long long idle_target(CPU_Core_Stat cores)
{
    return cores.idle + cores.iowait;
}

static void get_cpu_usages(void) {
    CPU_Core_Stat cores_before[MAX_CORES];
    CPU_Core_Stat cores_after[MAX_CORES];
    int count_1 = 0, count_2 = 0;

    if (read_core_stats(cores_before, &count_1) == -1) {
        printf("read_core_stats(before) failed\n");
        return;
    }
    sleep(1);
    if (read_core_stats(cores_after, &count_2) == -1) {
        printf("read_core_stats(after) failed\n");
        return;
    }

    int n = (count_1 < count_2) ? count_1 : count_2;

    for (int i = 0; i < n; i++) {
        unsigned long long t1 = total_target(cores_before[i]);
        unsigned long long t2 = total_target(cores_after[i]);
        unsigned long long i1 = idle_target(cores_before[i]);
        unsigned long long i2 = idle_target(cores_after[i]);

        if (t2 < t1 || i2 < i1) {
            if (i == 0) printf("CPU total: N/A (counters reset)\n");
            else        printf("Core %d : N/A (counters reset)\n", i - 1);
            continue;
        }

        unsigned long long delta_total = t2 - t1;
        unsigned long long delta_idle  = i2 - i1;

        double percent = 0.0;
        if (delta_total > 0) {
            percent = (double)(delta_total - delta_idle) * 100.0 / (double)delta_total;
            if (percent < 0.0) percent = 0.0;      
            if (percent > 100.0) percent = 100.0;  
        }

        if (i == 0)
        {
            printf("CPU total: %.2f%%\n", percent);
            if (percent > 80)
            {
                log_message(LOG_WARNING, "percent CPU all high %.2f%%\n ",percent);

            }
        }    
        else
        {
            printf("Core %d  : %.2f%%\n", i - 1, percent);
            log_message(LOG_WARNING, "percent CPU %d high %.2f%%\n ",i,percent);
        }    
    }


}


static void get_cpu_frequencies() {
    FILE *fp = fopen(READ_CPU_INFO, "r");
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
    DIR *dir = opendir(READ_PROCESS);

    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (!isdigit(entry->d_name[0])) continue;

        int pid = atoi(entry->d_name);
        char path[64];
        snprintf(path, sizeof(path), READ_PROCESS_STATUS , pid);

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

static void get_top_cpu_processes() {
    CPU_Process processes[TOP_N];
    int count = top_cpu_processes(processes, TOP_N);
    printf("\nTop %d used CPU :\n", count);

    for (int i = 0; i < count; i++) {
        printf("%2d. PID: %d  %-20s CPU %.2f %%\n", i + 1, processes[i].pid, processes[i].name_pid, processes[i].cpu_usage);
    }
}

void CPU_INFO_CHECK()
{
    printf("\n Check CPU \n");
    get_cpu_usages(); 
    get_cpu_frequencies();
    get_top_cpu_processes();

}
