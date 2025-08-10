#ifndef HANDLE_FUCTION
#define HANDLE_FUCTION

    #include <string.h>
    
    typedef enum{
        CPU_INFO = 0,
        RAM_INFO ,
        DISK_INFO,
        NETWORK_INFO,
        EXIT,
    } Choice;

    typedef struct{
        Choice INFO_CHECK;
        void (*INFO)();
    } Check_Info;

    
    void choose_fuction(Choice already_choice);


#endif