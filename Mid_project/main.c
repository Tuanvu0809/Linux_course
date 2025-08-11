#include <stdio.h>
#include <unistd.h>
#include "inc/CPU_parameter.h"
#include "inc/RAM_parameter.h"
#include "inc/Disk_parameter.h"
#include "inc/Network_parameters.h"
#include "inc/Handle_function.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    printf("Program Manage :\n");
    Choice Your_choice;
    do
    {
        Print_menu();
        printf("Enter your Choice: ");
        scanf("%d", (int*)&Your_choice);
        choose_fuction(Your_choice);

    } while (Your_choice != EXIT);

    printf("\n---end----\n");
     
    return 0;
}