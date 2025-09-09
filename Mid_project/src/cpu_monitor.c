#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include "../inc/cpu_monitor.h"

static cpu_monitor_t *cpu_manage_core;

/*caculate*/
double core_percent_calculate(unsigned long long index , unsigned long long total)
{
    return (double) index * 100 /(double) total;
} 

static unsigned long long core_total_target_calculate(cpu_snap_t cores)
{
    return cores.user + cores.nice + cores.system + cores.idle + cores.iowait + cores.irq + cores.softirq;
}

static unsigned long long core_idle_target_calculate( cpu_snap_t cores)
{
    return cores.idle + cores.iowait;
}

static void cpu_core_count_update()
{
    if (cpu_manage_core == NULL) return;
   cpu_manage_core->core_count = sysconf(_SC_NPROCESSORS_ONLN) + 1;
}

static int cpu_temperature_read()
{
    srand(time(NULL));
    return rand() %100 +1;
}

static cpu_monitor_t *cpu_core_init()
{
    if(cpu_manage_core != NULL)
    {
        return cpu_manage_core;
    }

    cpu_manage_core = malloc(sizeof(cpu_monitor_t));

    if (cpu_manage_core == NULL) {
        perror("malloc failed\n");
        return NULL;
    }

    cpu_core_count_update();
    int core = cpu_manage_core->core_count ;

    for (int i = 0; i < core; i++) {
        memset(&cpu_manage_core->previous_snapshot[i], 0, sizeof(cpu_snap_t));
        memset(&cpu_manage_core->current_snapshot[i], 0, sizeof(cpu_snap_t));
    }
    for (int i=0; i<= CPU_TOP_PROCESS; i++)
    {
        memset(&cpu_manage_core->processes[i],0,sizeof(cpu_process_parameter_t));
    }
    return cpu_manage_core;

}   

static int cpu_frequencies_read() 
{
    if (cpu_manage_core == NULL) return -1;

    FILE* file = fopen("/proc/cpuinfo", "r"); 
    if (!file) return -1;
    
    char line[256];
    double total_freq = 0;
    int core_count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "cpu MHz")) {
            double freq;
            if (sscanf(line, "cpu MHz\t: %lf", &freq) == 1) {
                total_freq += freq;
                core_count++;
            }
        }
    }
    fclose(file);
    if (core_count > 0)
    {
        cpu_manage_core->frequency = total_freq / core_count;
    }

    return 0;

}

static int cpu_core_stats_read(cpu_snap_t *core)
{
    FILE *fp = fopen(PROC_CORE_STAT_PATH, "r");
    if (!fp) return -1;

    char line[CPU_LINE_LEN];
  
    for(int i=0; i<cpu_manage_core->core_count; i++)
    {
        fgets(line, sizeof(line), fp);
        if (strncmp(line, "cpu", 3) == 0) 
        {
            if (line[3] == ' ')
            {
                sscanf(line, "cpu  %hu %hu %hu %hu %hu %hu %hu",
                                &core[i].user,
                                &core[i].nice,
                                &core[i].system,
                                &core[i].idle,
                                &core[i].iowait,
                                &core[i].irq,
                                &core[i].softirq);
            }
            else if (isdigit(line[3]))
            {
                int id;
                sscanf(line, "cpu%d %hu %hu %hu %hu %hu %hu %hu",&id,
                        &core[i].user,
                        &core[i].nice,
                        &core[i].system,
                        &core[i].idle,
                        &core[i].iowait,
                        &core[i].irq,
                        &core[i].softirq);
            }
        }
    }

    fclose(fp);
   
    return 0;
}

void cpu_core_read()
{
    
    if(cpu_core_stats_read(cpu_manage_core->previous_snapshot) == -1)
    {
        printf("cpu core stat read failed\n");
        return;
    }

    sleep(CPU_MONITOR_SAMPLE_INTERVAL_S);

    if(cpu_core_stats_read(cpu_manage_core->current_snapshot) == -1)
    {
        printf("cpu core stat read failed\n");
        return;
    }

}
static double cpu_usage_caculate(cpu_process_parameter_t process)
{
    return (double) (process.utimes +process.stimes) / sysconf(_SC_CLK_TCK);
}

static int cpu_process_use_most_read(cpu_process_parameter_t *Process, int top_n) {
    DIR *dir = opendir(PROC_STAT_PATH); 
    int min_idx;
    int pid;
    double cpu;
    unsigned long utime, stime;

    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir))) 
    {
        if (!isdigit(entry->d_name[0])) continue;

        pid = atoi(entry->d_name);
        char path[64];
        snprintf(path, sizeof(path), PROC_PROCESS_PATH_ , pid);

        FILE *fp = fopen(path, "r");
        if (!fp) continue;
        utime = 0, stime = 0;
        char Name_of_pid[CPU_LINE_LEN];
        fscanf(fp, "%*d (%[^)]) %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %lu", Name_of_pid, &utime, &stime);
        fclose(fp);
        
        cpu = (utime + stime) / 100.0; 
        if (cpu < 0.1f) continue;

        if(count < CPU_TOP_PROCESS)
        {
            Process[count].pid = pid;
            strcpy(Process[count].process_name, Name_of_pid);
            Process[count].utimes = utime;
            Process[count].stimes = stime;
            count ++;
        }
        else {
            min_idx = 0;
            for (int i = 1; i < top_n; i++)
            {
                if (cpu_usage_caculate(Process[i]) < cpu_usage_caculate(Process[min_idx]))
                    min_idx = i; 
            }   
            if (cpu > cpu_usage_caculate(Process[min_idx]) )
            {
                    Process[min_idx].pid = pid;
                    strcpy(Process[min_idx].process_name, Name_of_pid);
                    Process[min_idx].utimes = utime;
                    Process[min_idx].stimes = stime;
            }    
        }
    }

    closedir(dir);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) 
        {
            if (cpu_usage_caculate(Process[i]) < cpu_usage_caculate(Process[j]))
            {
                cpu_process_parameter_t temporary = Process[i];
                Process[i] = Process[j];
                Process[j] = temporary;
            }
          }
        }
    
    return count;
}


void cpu_core_display()
{
    cpu_core_read();
    unsigned long long target_total,target_idle;
    double percent_core;
    

    printf("===CPU Usage=====\n");
   // printf("CPU TOTAL USASGE: %.2f %%\n",cpu_manage_core->percent_core[0]);

  
    for(int i= 0 ; i< cpu_manage_core->core_count ;i++)
    {
    target_total= 0;
    target_idle = 0;
    percent_core = 0;
                
    target_total = core_total_target_calculate(cpu_manage_core->previous_snapshot[i]) +  core_total_target_calculate(cpu_manage_core->current_snapshot[i]) ;
    target_idle =core_idle_target_calculate(cpu_manage_core->previous_snapshot[i]) +  core_idle_target_calculate(cpu_manage_core->current_snapshot[i]);    
    
    percent_core = core_percent_calculate(target_idle,target_total);

    printf("CPU CORE %d : %.2f %%\n", i,percent_core);

        if(percent_core > 95 )
        {
            log_message(LOG_WARNING , "CORE %d  high",i);
        }
    }

}
void cpu_frequencies_display()
{
      if( cpu_frequencies_read()== -1)
    {
        printf("Read frequencies fails");
        return;
    }
    printf("CPU frequency: %.2f MHZ\n",cpu_manage_core->frequency);
}
void cpu_temperature_display()
{
    cpu_manage_core->temperature = cpu_temperature_read();
    printf("CPU temperature : %d \n", cpu_manage_core->temperature);
     if(cpu_manage_core->temperature > 80)
    {
        log_message(LOG_WARNING , "CPU HIGH TEMPERATURE");
    }
}
void cpu_process_use_most_display()
{ 
    int count = cpu_process_use_most_read(cpu_manage_core->processes, CPU_TOP_PROCESS); 
    double percent = 0;
    printf("\nTop %d used CPU :\n", count);

    for (int i = 0; i < count; i++) 
    {
        percent = 0;
        percent= cpu_usage_caculate(cpu_manage_core->processes[i]);
        printf("%2d. PID: %d  %-20s CPU %.2f %%\n", i + 1, cpu_manage_core->processes[i].pid, cpu_manage_core->processes[i].process_name, percent);
          if(percent  > 80 )
        {
            log_message(LOG_WARNING , "HIGH PROCESS %s ",cpu_manage_core->processes[i].process_name);
        }
    }
}

cpu_manager_t *cpu_manage_creat()
{
    cpu_manager_t *Creat = malloc(sizeof(cpu_manager_t));
    cpu_manage_core= cpu_core_init();
    Creat->data = cpu_manage_core;
    Creat->core_display = cpu_core_display;
    Creat->frequency_display = cpu_frequencies_display;
    Creat->temperature_display = cpu_temperature_display;
    Creat->process_usage_cpu_most_display = cpu_process_use_most_display;
    return Creat;
}
