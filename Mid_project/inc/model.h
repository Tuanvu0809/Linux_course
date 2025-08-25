#ifndef MODEL_H
#define MODEL_H

#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include "network.h"
#include "Log.h"

typedef struct{
    cpu_manage *cpu;
    ram_manange *ram;
    disk_manage *disk;
    network_mananage *network;
} Mananger;
Mananger *creat_manager();

void display_parameter(Mananger *computer);
void rank_parameter(Mananger *computer);


#endif