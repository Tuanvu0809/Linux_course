#ifndef RAM_H
#define RAM_H

    #define TOP_N 5

    
    typedef struct {
        int pid;
        char name[256];
        unsigned long mem_kb;
    } RAMProcess;

    void get_ram_usage();
    void get_swap_usage();
    void get_top_ram_processes();

#endif