#include <stdio.h>
#include "light.h"


void init_light()
{
    printf("init success\n");

}
float data_light()
{
    return 25;
}

sensor creatlight(){
    sensor creat;
    creat.init = init_light;
    creat.data = data_light;
    return creat;
}