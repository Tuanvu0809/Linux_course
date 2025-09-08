#ifndef CPU_H
#define CPU_H
#include "log.h"

#define MAX_CORES                           64
#define MAX_PROCESSES                       5
#define NAME_LEN                            256
#define LINE_LEN                            512 
#define NUM_VALUE                           7
#define TIME_CALCULATE_ONE_SECOND           1
#define TOP_PROCESS                         5

#define READ_PROCESS_DIR                    "/proc"
#define READ_PROCESS_STATUS_CPU             "/proc/%d/stat"
#define READ_CORE_STAT                      "/proc/stat"
#define READ_CPU_INFO                       "/proc/cpuinfo"

typedef struct {
    unsigned  short int user;
    unsigned  short int nice;
    unsigned  short int system;
    unsigned  short int idle;
    unsigned  short int iowait;
    unsigned  short int irq;
    unsigned  short int softirq;
    
} cpu_core_time_t;

typedef struct {
    int pid;
    char process_name[NAME_LEN];
    float cpu_usage;
    unsigned short int utimes;
    unsigned short int stimes;
} cpu_process_parameter_t;

typedef struct{
    cpu_core_time_t system_core[MAX_CORES];
    cpu_process_parameter_t  processes[TOP_PROCESS];
    double percent_core[MAX_CORES];
    double frequency;
    int temperature;
    int core_count;
} cpu_snapshot_t;

typedef struct{
    cpu_snapshot_t *data;
    void (*core_display)();
    void (*frequency_display)();
    void (*temperature_display)();
    void (*process_usage_cpu_most_display)();

} cpu_manager_t;

cpu_manager_t *cpu_manage_creat();

#endif