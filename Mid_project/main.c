#include <stdio.h>
#include <unistd.h>
#include "inc/cpu.h"
#include "inc/ram.h"
#include "inc/disk.h"
#include "inc/Network_parameters.h"
#include "inc/Handle_function.h"
#include "inc/Log.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

cpu_core_infomation *cpu_manange_core = NULL;
ram_usage_information *ram_manage = NULL;
disk_information *disk_manage = NULL;

/*main*/
int main()
{
    printf("Program Manage :\n");


    cpu_infomation_display();
    cpu_manage_free();
    ram_infomation_display();
    ram_manage_free();
    


    return 0;
}