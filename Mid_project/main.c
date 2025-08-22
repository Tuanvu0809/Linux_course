#include <stdio.h>
#include <unistd.h>
#include "inc/cpu.h"
#include "inc/RAM_parameter.h"
#include "inc/Disk_parameter.h"
#include "inc/Network_parameters.h"
#include "inc/Handle_function.h"
#include "inc/Log.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

cpu_core_infomation *cpu_manange_core = NULL;
//cpu_process_parameter   *cpu_manage_process = NULL;

int main()
{
    printf("Program Manage :\n");


    CPU_INFO_CHECK();
   
    cpu_manage_free();
    


    return 0;
}