#ifndef CPU_H
#define CPU_H
#include "log.h"

#define CPU_MAX_CORES                           64
#define CPU_MAX_PROCESSES                       5
#define CPU_NAME_LEN                            256
#define CPU_LINE_LEN                            512 
#define NUM_VALUE                               7
#define CPU_MONITOR_SAMPLE_INTERVAL_S            1
#define CPU_TOP_PROCESS                         5

static const char *const PROC_STAT_PATH = "/proc" ;
static const char *const PROC_PROCESS_PATH_=   "/proc/%d/stat";
static const char *const PROC_CORE_STAT_PATH =   "/proc/stat";
static const char *const PROC_CPU_INFO_PATH = "/proc/cpuinfo";

typedef struct {
    unsigned  short int user;
    unsigned  short int nice;
    unsigned  short int system;
    unsigned  short int idle;
    unsigned  short int iowait;
    unsigned  short int irq;
    unsigned  short int softirq;
    
} cpu_snap_t;

typedef struct {
    int pid;
    char process_name[CPU_NAME_LEN];
    unsigned short int utimes;
    unsigned short int stimes;
} cpu_process_parameter_t;

typedef struct{
    cpu_snap_t previous_snapshot[CPU_MAX_CORES];
    cpu_snap_t current_snapshot[CPU_MAX_CORES];
    cpu_process_parameter_t  processes[CPU_TOP_PROCESS];
    double percent_core[CPU_MAX_CORES];
    double frequency;
    int temperature;
    int core_count;
}  cpu_monitor_t;

typedef struct{
    cpu_monitor_t *data;
    void (*core_display)();
    void (*frequency_display)();
    void (*temperature_display)();
    void (*process_usage_cpu_most_display)();

} cpu_manager_t;

cpu_manager_t *cpu_manage_creat();

#endif