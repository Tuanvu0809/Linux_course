#ifndef CPU_PARAMETER_H
#define CPU_PARAMETER_H
#include "Log.h"

#define MAX_CORES   64
#define TOP_N        5
#define NAME_LEN    256
#define LINE        512 
#define READ_PROCESS   "/proc"
#define READ_PROCESS_STATUS_CPU     "/proc/%d/stat"
#define READ_CORE_STAT  "/proc/stat"
#define READ_CPU_INFO   "/proc/cpuinfo"

typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
} CPU_Core_Stat;

typedef struct {
    int core_id;
    int frequency_khz;
} CPU_Frequency;

typedef struct {
    int pid;
    char name_pid[NAME_LEN];
    float cpu_usage;
} CPU_Process;
typedef struct{
    CPU_Core_Stat Core[MAX_CORES];
    CPU_Frequency Frequency;
    CPU_Process Process;
    void (*messege) (Log_level log);
} Cpu_info;


/*Function user can use*/
void CPU_INFO_CHECK();

#endif