#ifndef SMART_HOME
#define SMART_HOME
    #include "../hvac/hvac.h"
    #include "../light/light.h"
    #include "../sercurity/sercurity.h"

    typedef struct 
    {
        Light_mode *light;
        Hvac_mode *hvac;
        Sercurity_mode *sercurity;
    }smarthome;
    
    
    smarthome *Creatsmarthomefacade();
    void Morning_fuc(smarthome *home);
    void Night_fuc(smarthome *home);
#endif