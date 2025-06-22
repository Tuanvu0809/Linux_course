#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "..\inc\config.h"
#include  "..\inc\sensor.h"

extern data sensor;
static int readTemp()
{
    return 20;
} 

static int readMoisture(){
    
    return  rand() % 100 ;
}

void Read_TEMP_MOISTURE(){
    // read Temp and Moisture

    sensor.Temperature = readTemp();
    sensor.Moisture = readMoisture();

    // display 

}