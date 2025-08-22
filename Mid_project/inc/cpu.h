#ifndef CPU_H
#define CPU_H
#include "Log.h"

#define MAX_CORES                       64
#define MAX_PROCESSES                    5
#define NAME_LEN                        256
#define LINE_LEN                        512 
#define NUM_VALUE                       7
#define TIME_CALCULATE_ONE_SERCOND      1
#define TOP_5_CPU_PROCESS               5

#define READ_PROCESS                    "/proc"
#define READ_PROCESS_STATUS_CPU         "/proc/%d/stat"
#define READ_CORE_STAT                   "/proc/stat"
#define READ_CPU_INFO                    "/proc/cpuinfo"

typedef struct {
    unsigned  short int user;
    unsigned  short int nice;
    unsigned  short int system;
    unsigned  short int idle;
    unsigned  short int iowait;
    unsigned  short int irq;
    unsigned  short int softirq;
    
} cpu_usage_parameter;

typedef struct {
    int pid;
    char process_name[NAME_LEN];
    float cpu_usage;
} cpu_process_parameter;

typedef struct{
    cpu_usage_parameter system_core_before[MAX_CORES];
    cpu_usage_parameter system_core_after[MAX_CORES];
    cpu_process_parameter  processes[TOP_5_CPU_PROCESS];
    double percent_core[MAX_CORES];
    double frequency;
    int temperature;
    int core_count;
} cpu_core_infomation;

/*Function user can use*/
void cpu_infomation_display();
void cpu_manage_free();

#endif