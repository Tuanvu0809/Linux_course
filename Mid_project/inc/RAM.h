#ifndef RAM_H
#define RAM_H

    #define TOP_N 5
    #define NAME_LEN    256
    #define READ_PROCESS             "/proc"
    #define READ_PROCESS_STATUS     "/proc/%d/status"
    #define READ_MEMORY_INFO        "/proc/meminfo"

    
    typedef struct {
        int pid;
        char name[NAME_LEN];
        unsigned long Memory_kb;
    } RAM_Process;

    void RAM_INFO_CHECK();


#endif