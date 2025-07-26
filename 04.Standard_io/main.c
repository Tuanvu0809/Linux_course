#include <stdio.h>
#include <stdlib.h>
#include "inc\log.h"

int main()
{
    if (Log_init(LOG_DEBUG,"file/console.txt")!= 0)
    {
        fprintf(stderr, "Failed to initialize logger\n");
        return 1;
    }

    log_message(LOG_ERROR,"Auto test");
    log_message(LOG_DEBUG,"not seen");
    log_message(LOG_CRITICAL,"hi_lo");
    log_message(LOG_ALERT,"%s %s %s","test arg","ok","excellent");

    Set_log_level(LOG_WARNING); 
    log_message(LOG_NOTICE,"cant seen");
    log_message(LOG_ERROR, "seen");
    log_message(LOG_EMERGENCY,"Test happy");

    Log_close();

    return 0;
}