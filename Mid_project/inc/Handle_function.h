#ifndef HANDLE_FUCTION
#define HANDLE_FUCTION

    #include <string.h>
    
    typedef enum{
        EXIT = 0,
        RAM_INFO ,
        DISK_INFO,
        NETWORK_INFO,
        CPU_INFO,
    } Choice;

    typedef struct{
        Choice INFO_CHECK;
        void (*INFO)();
    } Check_Info;

    
    void choose_fuction(Choice already_choice);
    void Print_menu();



#endif