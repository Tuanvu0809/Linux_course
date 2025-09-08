#ifndef MODEL_H
#define MODEL_H

#include "cpu_monitor.h"
#include "ram_monitor.h"
#include "disk_monitor.h"
#include "network_monitor.h"

typedef struct {
    cpu_manager_t *cpu;
    ram_manage_t *ram;
    disk_manage_t *disk;
    network_mananage_t *network;
} Manager;

Manager *creat_manager();

void display_parameter(Manager *computer);
void rank_parameter(Manager *computer);


#endif