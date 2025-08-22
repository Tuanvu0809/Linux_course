#ifndef RAM_H
#define RAM_H
#include "Log.h"

/*macro*/
#define TOP_5_CPU_PROCESS            5
#define NAME_LEN                    256
#define READ_PROCESS                "/proc"
#define READ_PROCESS_STATUS_RAM     "/proc/%d/status"
#define READ_MEMORY_INFO             "/proc/meminfo"

/*Struct*/   
typedef struct {
    int pid;
    char process_name[NAME_LEN];
    unsigned long Memory;
} ram_process_parameter;

typedef struct {
    unsigned long memory_total;
    unsigned long memory_free;
    unsigned long memory_used;
    unsigned long buffer;
    unsigned long cached;
    unsigned long swap_total;
    unsigned long swap_free;
    unsigned long swap_used;
    ram_process_parameter processes[TOP_5_CPU_PROCESS];
} ram_usage_information;


void ram_infomation_display();
void ram_manage_free();

#endif