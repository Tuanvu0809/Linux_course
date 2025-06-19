#include <stdio.h>
#include "..\inc\config.h"
#include "..\inc\button.h"
extern data sensor;
extern STATUS pump;
extern LED_STATUS led;

void Handle_Auto(SETTING *current);
void Handle_Manual(SETTING *current);
void Turn_led(LED_STATUS led);
void Read_TEMP_MOISTURE();


void Set_for_auto(SETTING *mode)
{
   
        printf("\n----AUTO-----\n");
        Read_TEMP_MOISTURE();
        printf("TEMP = %d C || Moisture = %d \n", sensor.Temperature,sensor.Moisture);

        if(sensor.Moisture<mode->moisture_min){
            led = LED_LOW_MOISTURE_ALERT;
        }
      
        printf("  Status led: ");    
        Turn_led(led);
        
        printf("\n");
        Handle_Auto(mode);

}

void Set_for_manual(SETTING *mode)
{
  
        printf("\n---Manual----\n");
        Read_TEMP_MOISTURE();
        printf("TEMP = %d C || Moisture = %d ", sensor.Temperature,sensor.Moisture);
        
        if(sensor.Moisture<mode->moisture_min){
            led = LED_LOW_MOISTURE_ALERT;
        }
  
        printf("  Status led: ");    
        Turn_led(led);
 
         printf("\n");
        Handle_Manual(mode);
      
}