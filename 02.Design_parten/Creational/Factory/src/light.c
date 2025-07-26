#include <stdio.h>
#include "../inc/light.h"


void init_light()
{
    printf("Init success\n");
}

float data_light()
{
    return 25;
}

sensor creat_light(){
    sensor creat;
    creat.init = init_light;
    creat.data = data_light;
    return creat;
}