#ifndef SMART_HOME
#define SMART_HOME
    #include "hvac.h"
    #include "light.h"
    #include "sercurity.h"

    typedef struct 
    {
        Light_mode *light;
        Hvac_mode *hvac;
        Sercurity_mode *sercurity;
    }smarthome;
    
    
    smarthome *Creat_smart_home_facade();
    void Morning_fuc(smarthome *home);
    void Night_fuc(smarthome *home);
#endif