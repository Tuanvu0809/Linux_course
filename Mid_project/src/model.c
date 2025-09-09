#include <stdio.h>
#include <stdlib.h>
#include "../inc/model.h"

Manager *creat_manager()
{
    Manager *Creat = malloc(sizeof(Manager));
    Creat->cpu = cpu_manage_creat();
    Creat->ram = ram_manage_creat();
    Creat->disk = disk_manage_creat();
    Creat->network = network_manage_creat();

    return Creat;
}

void display_parameter(Manager *computer)
{
    printf("parameter store \n");
    computer->cpu->core_display();
    computer->cpu->frequency_display();
    computer->cpu->temperature_display();
    computer->ram->ram_memory_display();
    computer->disk->disk_display();
    computer->network->network_ip_display();

}
void sort_parameter(Manager *computer)
{
        printf("parameter sorrt \n");
    computer->cpu->process_usage_cpu_most_display();
    computer->ram->process_usage_ram_most_display();
    computer->network->network_speed_display();
}