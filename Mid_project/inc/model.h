#ifndef MODEL_H
#define MODEL_H

#include "cpu_monitor.h"
#include "ram_monitor.h"
#include "disk_monitor.h"
#include "network_monitor.h"

typedef struct {
    cpu_manager_t *cpu;
    ram_manager_t *ram;
    disk_manager_t *disk;
    network_mananager_t *network;
} Manager;

Manager *creat_manager();

void display_parameter(Manager *computer);



#endif