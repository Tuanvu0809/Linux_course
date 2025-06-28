#include <stdio.h>
#include <stdlib.h>
#include "sensor/factory.h"


int main()
{
   
    printf("program: \n");

     sensor *Temperature_sensor = CreatSensor(temp) ;
    if(Temperature_sensor != NULL)
    {
        Temperature_sensor->init();
        printf("Temp sensor data: %.2f\n", Temperature_sensor->data());
        free(Temperature_sensor);
    }


    sensor *Light_sensor = CreatSensor(light) ;
    if(Light_sensor != NULL)
    {
        Light_sensor->init();
        printf("Light sensor data: %.2f\n", Light_sensor->data());
        free(Light_sensor);
    }
    return 0;
}