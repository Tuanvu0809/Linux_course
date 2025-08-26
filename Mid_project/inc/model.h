#ifndef MODEL_H
#define MODEL_H

#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include "network.h"

typedef struct {
    cpu_manage_t *cpu;
    ram_manage_t *ram;
    disk_manage_t *disk;
    network_mananage_t *network;
} Manager;

Manager *creat_manager();

void display_parameter(Manager *computer);
void rank_parameter(Manager *computer);


#endif