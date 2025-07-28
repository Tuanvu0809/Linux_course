#include <stdio.h>
#include "../inc/temp.h"

void init_temp()
{
    printf("Init success\n");

}
float data_temp()
{
    return 300.00;
}

sensor creat_temp(){
    sensor creat;
    creat.init = init_temp;
    creat.data = data_temp;
    return creat;

}
