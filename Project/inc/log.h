#ifndef LOG_H
#define LOG_H


typedef enum
{
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} log_level;

/*fucnction */
void log_init(log_level current_level, const char *File);
void Set_log_level(log_level Set);
void log_close();
void logger_log_handle(log_level level, const char *fmt, ...);

#define log_message(level,...)  logger_log_handle(level, __VA_ARGS__)
#endif