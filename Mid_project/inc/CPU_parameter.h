#ifndef CPU_PARAMETER_H
#define CPU_PARAMETER_H

 
    #define MAX_CORES   64
    #define TOP_N        5
    #define NAME_LEN    256
    #define LINE        512 
    #define READ_PROCESS   "/proc"
    #define READ_PROCESS_STATUS     "/proc/%d/status"
    #define READ_CORE_STAT  "/proc/stat"
    #define READ_CPU_INFO   "/proc/cpuinfo"


    typedef struct {
        unsigned long long user, nice, system, idle, iowait, irq, softirq;

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

 
    void CPU_INFO_CHECK();

#endif