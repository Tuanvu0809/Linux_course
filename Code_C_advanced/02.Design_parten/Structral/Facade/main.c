#include <stdio.h>
#include <stdlib.h>
#include "inc/smarthome.h"


int main()
{
    smarthome *home = Creat_smart_home_facade();

    printf(">Morning:\n\t");
    Morning_fuc(home);

    printf(">Night: \n\t");
    Night_fuc(home);


    free(home->light);
    free(home->hvac);
    free(home->sercurity);

    printf("End of program");

    return 0;
}