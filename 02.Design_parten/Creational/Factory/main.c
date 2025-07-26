#include <stdio.h>
#include <stdlib.h>
#include "inc/sensor.h"
#include "inc/factory.h"


int main()
{
   
    printf("program: \n");
    /*creat temp sensor*/
    sensor *Temperature_sensor = CreatSensor(temp) ;
    if(Temperature_sensor != NULL)
    {
        Temperature_sensor->init();
        printf("\tTemp sensor data: %.2f\n", Temperature_sensor->data());
        free(Temperature_sensor);
    }

    /*creat Light sensor*/
    sensor *Light_sensor = CreatSensor(light) ;
    if(Light_sensor != NULL)
    {
        Light_sensor->init();
        printf("\tLight sensor data: %.2f\n", Light_sensor->data());
        free(Light_sensor);
    }
    return 0;
}