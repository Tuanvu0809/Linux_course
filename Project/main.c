#include <stdio.h>
#include <unistd.h>
#include "inc/model.h"
#include "inc/log.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    printf("Program Manage :\n");
    
    log_init(LOG_NOTICE,"file/console.txt");
    Manager *Ubutu = creat_manager();
    display_parameter(Ubutu);
    log_close();

    free(Ubutu->cpu);
    free(Ubutu->ram);
    free(Ubutu->disk);
    free(Ubutu->network);

    return 0;
}