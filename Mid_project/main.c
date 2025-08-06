#include <stdio.h>
#include <unistd.h>
#include "inc/CPU_parameter.h"
#include "inc/RAM.h"
int main()
{
    printf("Program Manage :\n");

    print_cpu_usages();
    print_cpu_frequencies();
    
    print_top_cpu_processes();
    get_ram_usage();
    get_swap_usage();
    get_top_ram_processes();
    return 0;
}