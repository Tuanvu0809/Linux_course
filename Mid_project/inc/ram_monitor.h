#ifndef RAM_H
#define RAM_H
#include "log.h"

#define TOP_5_PROCESS_USE_RAM_MOST                          5
#define MAX_NAME_PROCESS_LEN                            256

static const char *const PROC_RAM_DIR =  "/proc";
static const char *const PROC_RAM_PROCESS_DIR = "/proc/%d/status";
static const char *const PROC_MEMEMORY_INFO =  "/proc/meminfo";
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
}  ram_manager_t;

 ram_manager_t *ram_manage_creat();

#endif