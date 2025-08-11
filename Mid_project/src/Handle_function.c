#include "../inc/Handle_function.h"
#include "../inc/CPU_parameter.h"
#include "../inc/RAM.h"
#include "../inc/Storetage.h"
#include "../inc/network_parameters.h"
#include <stdio.h>

Check_Info Infomation[]=
{
        { CPU_INFO ,CPU_INFO_CHECK },
        { RAM_INFO ,RAM_INFO_CHECK},
        {DISK_INFO, DISK_INFO_CHECK},
        {NETWORK_INFO,NETWORK_INFO_CHECK},
};


void choose_fuction(Choice already_choice)
{
    if(already_choice > (sizeof(Infomation) / sizeof(Infomation[0])))
    {
        printf(" Not handle please try again \n");
        return;
    }
    for (int i = 0; i < (sizeof(Infomation) / sizeof(Infomation[0])); i++)
    {
        if (Infomation[i].INFO_CHECK == already_choice)
        {
            Infomation[i].INFO();
            return;
        }
    }
}