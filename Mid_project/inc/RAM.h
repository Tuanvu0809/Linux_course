#ifndef RAM_H
#define RAM_H

    #define TOP_N 5
    #define NAME_LEN    256

    
    typedef struct {
        int pid;
        char name[NAME_LEN];
        unsigned long Memory_kb;
    } RAM_Process;

    void get_ram_usage();
    void get_swap_usage();
    void get_top_ram_processes();

#endif