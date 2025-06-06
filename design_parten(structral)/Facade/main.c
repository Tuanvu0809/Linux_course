#include <stdio.h>
#include <stdlib.h>
#include "smarthome/smarthome.h"


int main()
{
    smarthome *home = Creatsmarthomefacade();

    printf(">Morning:\n");

    Morning_fuc(home);


    printf(">Night: \n");

 
    Night_fuc(home);


    free(home->light);
    free(home->hvac);
    free(home->sercurity);

    printf("End of program");

    return 0;
}