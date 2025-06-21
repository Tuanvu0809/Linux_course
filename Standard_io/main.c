#include <stdio.h>
#include <stdlib.h>
#include "inc\log.h"

int main()
{
    if (Log_init(LOG_NOTICE,"file/test.txt")!= 0)
    {
        fprintf(stderr, "Failed to initialize logger\n");
        return 1;
    }

    log_message(LOG_ERROR,"Important okay");
    log_message(LOG_DEBUG,"not seen");
    log_message(LOG_CRITICAL,"hi_lo");
    log_message(LOG_ALERT,"%s %s %s","test more","ok","excellent");


    Set_log_level(LOG_WARNING); 
    log_message(LOG_NOTICE,"cant seen");
    log_message(LOG_ERROR, "seen");
    log_message(LOG_EMERGENCY," NEED");

    Log_close();

    return 0;
}