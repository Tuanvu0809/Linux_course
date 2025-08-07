#include <stdio.h>
#include <unistd.h>
#include "inc/CPU_parameter.h"
#include "inc/RAM.h"

int main()
{
        printf("Program Manage :\n");   
        get_cpu_usages(); 
        get_cpu_frequencies();
        get_top_cpu_processes();
        get_ram_usage();
        get_swap_usage();
        get_top_ram_processes();
    return 0;
}