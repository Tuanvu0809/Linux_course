#include <stdio.h>
#include "temp.h"

void init_temp()
{
    printf("init success\n");

}
float data_temp()
{
    return 300.00;
}

sensor createmp(){
    sensor creat;
    creat.init = init_temp;
    creat.data = data_temp;
    return creat;

}
