#include <stdio.h>
#include <stdlib.h>
#include "../inc/light.h"


static void Turn_light_on(){
    printf("TURN ON THE LIGHT\n");
}
static void Turn_light_Off(){
    printf("TURN OFF THE LIGHT\n");
}
static void Set_bright(int level)
{
    printf("Bright ness: %d\n",level);
}

Light_mode *Creat_light()
{
    Light_mode *system = (Light_mode*) malloc(sizeof(Light_mode));
    system->Turn_on = Turn_light_on;
    system->Turn_off = Turn_light_Off;
    system->Set_bright_ness = Set_bright;
    return system;
}

