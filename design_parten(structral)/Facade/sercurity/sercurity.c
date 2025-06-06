#include <stdio.h>
#include <stdlib.h>
#include "sercurity.h"

static void Set_mode(char *mode)
{
    printf("Set mode : %s \n",mode);
}

static void Active()
{
    printf("Active arlam \n");
}
 static void Deactive()
{
    printf("deactive arlam \n");
}

Sercurity_mode *Creat_sercuirty()
{
    Sercurity_mode *system = (Sercurity_mode *) malloc(sizeof(Sercurity_mode));
    system->mode_ser = Set_mode;
    system->active_arlam = Active;
    system->deactive_arlam = Deactive;
    return system;

}

