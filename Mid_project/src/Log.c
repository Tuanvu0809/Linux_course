#include "../inc/Log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

static FILE *Handle_log = NULL;
static Log_level current = LOG_DEBUG;

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
/*Init Log */
void Log_init(Log_level current_level, const char *File)
{
    current = current_level;
    if (File)
    {
        Handle_log = fopen(File, "a");
        if (!Handle_log)
        {
            fprintf(stderr, "Failed to initialize logger\n");
            return;
        }
    }
}

/*set log*/
void Set_log_level(Log_level Set)
{
    current = Set;
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

void Logger_log_handle(Log_level level, const char *fmt, ...)
{
    if (level > current) return;  //debug 7 warnh 4

    /* Timestamp */
    time_t now = time(NULL);
    struct tm tmv;
    localtime_r(&now, &tmv);               
    char time[32];
    strftime(time, sizeof(time), "%d-%m-%Y %H:%M:%S", &tmv);

    /* Build log line safely */
    char log_line[1024];
    int n = snprintf(log_line, sizeof(log_line),"[%s] [%s] - ", time, message_log(level));
    if (n < 0) return;

    size_t used = (size_t)n;
    size_t left = (used < sizeof(log_line)) ? (sizeof(log_line) - used) : 0;

    va_list ap;
    va_start(ap, fmt);
    int m = (left > 0) ? vsnprintf(log_line + used, left, fmt, ap) : 0;
    va_end(ap);

    /* Ensure newline if we still have space */
    if (m >= 0) {
        size_t len = strnlen(log_line, sizeof(log_line));
        if (len + 1 < sizeof(log_line)) {
            log_line[len] = '\n';
            log_line[len+1] = '\0';
        }
    }

    /* Output to console */
    FILE *out = (level >= LOG_ERROR) ? stderr : stdout;
    if (Handle_log) 
    {
         fputs(log_line, Handle_log); 
         fflush(Handle_log);
    }
    fputs(log_line, out); 
    fflush(out);

}

double percent_calculate(unsigned long long index , unsigned long long total)
{
    return (double) index * 100 /(double) total;
} 