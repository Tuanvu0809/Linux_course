#include <stdio.h>
#include <stdlib.h>
// #include "../hvac/hvac.h"
// #include "../light/light.h"
// #include "../sercurity/sercurity.h"
#include "smarthome.h"

smarthome *Creatsmarthomefacade()
{
    smarthome *creat =(smarthome *) malloc(sizeof(smarthome));
    creat->light =Creat_light();
    creat->sercurity = Creat_sercuirty();
    creat->hvac = Creat_hvac();
    return creat;
}


void Morning_fuc(smarthome *home)
{
    home->light->Turn_off();
    home->light->Set_bright_ness(30);
    home->hvac->mode("day");
    home->hvac->temp(25);
    home->sercurity->deactive_arlam();
    
}

void Night_fuc(smarthome *home)
{
    home->light->Turn_on();
    home->light->Set_bright_ness(100);
    home->hvac->temp(20);
    home->sercurity->active_arlam();
    home->sercurity->mode_ser("night mode");
}
