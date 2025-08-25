#include <stdio.h>
#include <unistd.h>
#include "inc/model.h"
#include "inc/Log.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*main*/
int main()
{
    printf("Program Manage :\n");
    
    Mananger *Ubutu = creat_manager();
    display_parameter(Ubutu);
    printf("\n----------------------------\n");
    rank_parameter(Ubutu);    

    free(Ubutu->cpu);
    free(Ubutu->ram);
    free(Ubutu->disk);
    free(Ubutu->network);

    return 0;
}