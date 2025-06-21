#include <stdio.h>
#include <stdlib.h>
#include "hvac.h"

static void set_temp(int temp)
{
    printf("Set temp at : %d\n",temp);

}

static void set_mode(char *mode)
{
    printf("set mode : %s\n",mode);
}

Hvac_mode *Creat_hvac()
{
    Hvac_mode *system = (Hvac_mode *) malloc(sizeof(Hvac_mode));

    system->temp = set_temp;
    system->mode = set_mode;

    return  system;

}

