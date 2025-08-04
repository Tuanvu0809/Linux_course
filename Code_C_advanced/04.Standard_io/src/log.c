#include "../inc/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

static FILE *Handle_log = NULL;
static Log_level level = LOG_DEBUG;
/*Log level message*/
static const char *message_log(Log_level current_level)
{
    switch (current_level)
    {
        case LOG_EMERGENCY:
            return "EMERGENCY";
        case LOG_ALERT:
            return "ALERT";
        case LOG_CRITICAL:
            return "CRITICAL";
        case LOG_ERROR:
            return "ERROR";
        case LOG_WARNING:
            return "WARNING";
        case LOG_NOTICE:
            return "NOTICE";
        case LOG_INFO:
            return "INFO";
        case LOG_DEBUG:
            return "DEBUG";
        default:
            return "Error";
    }
}
/*init Log for program*/
int Log_init(Log_level current_level, const char *File)
{

    level = current_level;
    if (File)
    {
        Handle_log = fopen(File, "w");
        if (!Handle_log)
            return -1;
    }

    return 0;
}
/*set log*/
void Set_log_level(Log_level Set)
{
    level = Set;
}
/*close file*/
void Log_close()
{
    if (Handle_log)
    {
        fclose(Handle_log);
        Handle_log = NULL;
    }
}
/*handle */
void Logger_log_handle(Log_level set, const char *file, const int line, const char *avr, ...)
{
    if (set > level)
        return;

    /*Get time*/
    time_t now = time(NULL);
    struct tm *Info = localtime(&now);
    char time_stamp[50];
    strftime(time_stamp, sizeof(time_stamp), "%d-%m-%Y %H:%M:%S", Info);

    /*message */
    char message[1000];
    va_list arg;
    va_start(arg, avr);
    vsnprintf(message, sizeof(message), avr, arg);
    va_end(arg);

    /*Print*/
    char log_line[1024];
    snprintf(log_line, sizeof(log_line), "[%s] [%s] [%s:%d] - %s\n", time_stamp, message_log(set), file, line, message);

    /*output to console*/

    FILE *output = (set <= LOG_ERROR) ? stderr : stdout;
    fputs(log_line, Handle_log);
    fflush(output);
}