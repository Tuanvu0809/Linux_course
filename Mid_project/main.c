#include <stdio.h>
#include <unistd.h>
#include "inc/cpu.h"
#include "inc/ram.h"
#include "inc/Disk_parameter.h"
#include "inc/Network_parameters.h"
#include "inc/Handle_function.h"
#include "inc/Log.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

cpu_core_infomation *cpu_manange_core = NULL;
ram_usage_parameter *ram_manage = NULL;
//cpu_process_parameter   *cpu_manage_process = NULL;

int main()
{
    printf("Program Manage :\n");


    cpu_infomation_display();
  
    cpu_manage_free();

     ram_infomation_display();
     ram_manage_free();
    


    return 0;
}