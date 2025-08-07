#ifndef CPU_PARAMETER_H
#define CPU_PARAMETER_H

 
    #define MAX_CORES 64
    #define TOP_N 5
    #define NAME_LEN    256
    #define LINE        512 

    typedef struct {
        unsigned long long user, nice, system, idle, iowait, irq, softirq;
       // unsigned long long total, idle_all;
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

    void get_cpu_usages() ;
    void get_cpu_frequencies();
    void get_top_cpu_processes();
#endif