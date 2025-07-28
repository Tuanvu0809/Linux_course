#ifndef LOG_H
#define LOG_H
    /*Enum status log*/
    typedef enum{
        LOG_EMERGENCY,
        LOG_ALERT,
        LOG_CRITICAL,
        LOG_ERROR,
        LOG_WARNING,
        LOG_NOTICE,
        LOG_INFO,
        LOG_DEBUG
    }Log_level;

    /*fuction Creat*/
    int Log_init(Log_level current_level , const char *File);
    void Set_log_level(Log_level Set);
    void Log_close();
    void Logger_log_handle(Log_level set, const char *file, const int line, const char *avr ,...);

    #define log_message(level,...)  Logger_log_handle(level,__FILE__, __LINE__, __VA_ARGS__)
#endif