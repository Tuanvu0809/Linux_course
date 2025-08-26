#ifndef RAM_H
#define RAM_H
#include "log.h"

/*macro*/
#define TOP_PROCESS                          5
#define NAME_LEN                            256
#define READ_PROCESS_DIR                    "/proc"
#define READ_PROCESS_STATUS_RAM             "/proc/%d/status"
#define READ_MEMORY_INFO                    "/proc/meminfo"

/*Struct*/   
typedef struct {
    int pid;
    char process_name[NAME_LEN];
    unsigned long Memory;
} ram_process_parameter_t;

typedef struct {
    unsigned long memory_total;
    unsigned long memory_free;
    unsigned long memory_used;
    unsigned long buffer;
    unsigned long cached;
    unsigned long swap_total;
    unsigned long swap_free;
    unsigned long swap_used;
    ram_process_parameter_t processes[TOP_PROCESS];
} ram_usage_instance_t;

typedef struct{
    ram_usage_instance_t *data;
    void (*ram_memory_display)();
    void (*process_usage_ram_most_display)();
} ram_manage_t;

ram_manage_t *ram_manage_creat();

#endif