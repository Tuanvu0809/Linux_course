#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include "../inc/cpu.h"

cpu_core_instance *cpu_manange_core;

/*caculate*/
double percent_calculate(unsigned long long index , unsigned long long total)
{
    return (double) index * 100 /(double) total;
} 

static unsigned long long total_target(cpu_usage_parameter cores)
{
    return cores.user + cores.nice + cores.system + cores.idle + cores.iowait + cores.irq + cores.softirq;

}

static unsigned long long idle_target( cpu_usage_parameter cores)
{
    return cores.idle + cores.iowait;
}

static void cpu_core_count_update()
{
    if (cpu_manange_core == NULL) return;
   cpu_manange_core->core_count = sysconf(_SC_NPROCESSORS_ONLN) + 1;
}
static int cpu_temperature_read()
{
    srand(time(NULL));
    return rand() %100 +1;
}

static cpu_core_instance *cpu_core_init()
{
    if(cpu_manange_core != NULL)
    {
        return cpu_manange_core;
    }

    cpu_manange_core = malloc(sizeof(cpu_core_instance));

    if (cpu_manange_core == NULL) {
        perror("malloc failed\n");// bỏ log mess
        return NULL;
    }

    cpu_core_count_update();
    int core = cpu_manange_core->core_count ;

    for (int i = 0; i < core; i++) {
        memset(&cpu_manange_core->system_core[i], 0, sizeof(cpu_usage_parameter));
        memset(&cpu_manange_core->percent_core[i], 0, sizeof(double));
    }
    for (int i=0; i<= TOP_5_CPU_PROCESS; i++)
    {
        memset(&cpu_manange_core->processes[i],0,sizeof(cpu_process_parameter));
    }
    return cpu_manange_core;

}   

static int cpu_frequencies_read() 
{
    if (cpu_manange_core == NULL) return -1;

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
        cpu_manange_core->frequency = total_freq / core_count;
    }

    return 0;

}

static int cpu_core_stats_read(cpu_usage_parameter *core)
{
    FILE *fp = fopen(READ_CORE_STAT, "r");
    if (!fp) return -1;

    char line[LINE_LEN];
  
    for(int i=0; i<cpu_manange_core->core_count; i++)
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
  
    unsigned long long target_total,target_idle;

    if(cpu_core_stats_read(cpu_manange_core->system_core) == -1)
    {
        printf("cpu core stat read failed\n");
        return;
    }

    for (int i = 0; i < cpu_manange_core->core_count; i++) 
    {

        target_total= total_target(cpu_manange_core->system_core[i]);
        target_idle = idle_target(cpu_manange_core->system_core[i]);
       
        cpu_manange_core->percent_core[i] = percent_calculate(target_total- target_idle,target_total);
        if (cpu_manange_core->percent_core[i]< 0.0) cpu_manange_core->percent_core[i]= 0.0;      
        if (cpu_manange_core->percent_core[i]> 100.0) cpu_manange_core->percent_core[i]= 100.0;  


    }


}


static int cpu_process_use_most_read(cpu_process_parameter *Process, int top_n) {
    DIR *dir = opendir(READ_PROCESS); 
    int min_idx;
    int pid;
    double cpu;
    unsigned long utime, stime;

    if (!dir) return 0;

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir))) {
        if (!isdigit(entry->d_name[0])) continue;

        pid = atoi(entry->d_name);
        char path[64];
        snprintf(path, sizeof(path), READ_PROCESS_STATUS_CPU , pid);

        FILE *fp = fopen(path, "r");
        if (!fp) continue;
        utime = 0, stime = 0;
        char Name_of_pid[LINE_LEN];
        fscanf(fp, "%*d (%[^)]) %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %lu", Name_of_pid, &utime, &stime);
        fclose(fp);

        cpu = (utime + stime) / 100.0; 
        if (cpu < 0.1f) continue;

        if (count < top_n)
        {
            Process[count].pid = pid;
            strcpy(Process[count].process_name, Name_of_pid);
            Process[count].cpu_usage = cpu;
            count++;
        } else 
        {
       
            min_idx = 0;
            for (int i = 1; i < top_n; i++) {
                if (Process[i].cpu_usage < Process[min_idx].cpu_usage)
                    min_idx = i;
            }
            if (cpu > Process[min_idx].cpu_usage) {
                Process[min_idx].pid = pid;
                strcpy(Process[min_idx].process_name, Name_of_pid);
                Process[min_idx].cpu_usage = cpu;
            }
        }
    }

    closedir(dir);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (Process[i].cpu_usage < Process[j].cpu_usage) {
                cpu_process_parameter temporary = Process[i];
                Process[i] = Process[j];
                Process[j] = temporary;
            }
        }
    }

    return count;
}

void cpu_instance()
{
    
    

  

        
      

}
void cpu_core()
{
    cpu_core_read();

    printf("===CPU Usage=====\n");
    printf("CPU TOTAL USASGE: %.2f %%\n",cpu_manange_core->percent_core[0]);
  
    for(int i=1; i< cpu_manange_core->core_count -1 ;i++)
    {
        printf("CPU CORE %d : %.2f %%\n", i, cpu_manange_core->percent_core[i]);
    }

}
void cpu_frequencies()
{
      if( cpu_frequencies_read()== -1)
    {
        printf("Read frequencies fails");
        return;
    }
    printf("CPU frequency: %.2f MHZ\n",cpu_manange_core->frequency);
}
void cpu_temperature()
{
    
    cpu_manange_core->temperature = cpu_temperature_read();
    printf("CPU temperature : %d", cpu_manange_core->temperature);
}
void cpu_process_use_most()
{ 
    int count = cpu_process_use_most_read(cpu_manange_core->processes, TOP_5_CPU_PROCESS); 
    printf("\nTop %d used CPU :\n", count);
    for (int i = 0; i < count; i++) 
    {
        printf("%2d. PID: %d  %-20s CPU %.2f %%\n", i + 1, cpu_manange_core->processes[i].pid, cpu_manange_core->processes[i].process_name, cpu_manange_core->processes[i].cpu_usage);
    }
}
// void cpu_manage_free()
// {
//     if(cpu_manange_core == NULL)
//         return;
//     free(cpu_manange_core);
//     printf("\nfree manage cpu core sucess\n");
//     printf("\n============\n");
// }

cpu_manage *cpu_manage_creat()
{
    cpu_manage *Creat = malloc(sizeof(cpu_manage));
    cpu_manange_core= cpu_core_init();
    Creat->data = cpu_manange_core;
    Creat->core_display = cpu_core;
    Creat->frequency_display = cpu_frequencies;
    Creat->temperature_display = cpu_temperature;
    Creat->process_usage_cpu_most_display = cpu_process_use_most;
  //  Creat->free_cpu_data = cpu_manage_free;
    return Creat;

}
