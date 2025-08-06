#ifndef CPU_PARAMETER_H
#define CPU_PARAMETER_H

 
    #define MAX_CORES 64
    #define TOP_N 5

    typedef struct {
        unsigned long long user, nice, system, idle, iowait, irq, softirq;
       // unsigned long long total, idle_all;
    } CPUCoreStat;

    typedef struct {
        int core_id;
        int frequency_khz;
    } CPUFreq;

    typedef struct {
        int pid;
        char name[256];
        float cpu_usage;
    } CPUProcess;

    void print_cpu_usages() ;
    void print_cpu_frequencies();
    void print_top_cpu_processes();
#endif