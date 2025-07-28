#include <stdio.h>
#include "inc/Uart_builder.h"

int main()
{
    Uart_builder creat;
    creat = Uart_creat_default();
    Print_uart(creat.config);

    Uart_set_baud_rate(&creat,1500);
    Uart_set_parity(&creat,0);
    
    Uart_config final;
    final = creat.config;
    Print_uart(final);


    return 0;

}