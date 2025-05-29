#include <stdio.h>
#include <stdlib.h>
#include "sensor/factory.h"


int main()
{
    sensor *tempsensor = CreatSensor(temp) ;
    printf("program: \n");
    if(tempsensor != NULL)
    {
        tempsensor->init();
        printf("Temp sensor data: %.2f\n", tempsensor->data());
        free(tempsensor);
    }
        sensor *lightsensor = CreatSensor(light) ;
    if(lightsensor != NULL)
    {
        lightsensor->init();
        printf("Light sensor data: %.2f\n", lightsensor->data());
        free(lightsensor);
    }
    return 0;
}