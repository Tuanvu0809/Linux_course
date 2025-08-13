#ifndef HANDLE_FUCTION
#define HANDLE_FUCTION

    #include <string.h>
        /*macro*/
    /*Enum and struct*/
    typedef enum{
        CPU_INFO= 0,
        RAM_INFO ,
        DISK_INFO,
        NETWORK_INFO,
        EXIT
    } Choice;

    typedef struct{
        Choice INFO_CHECK;
        void (*INFO)();
    } Check_Info;

        /*Function user can use*/
    void choose_fuction(Choice already_choice);
    void Print_menu();
    void get_valid_choice(Choice *choice, int max);

#endif