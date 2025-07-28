#include "../inc/Uart_builder.h"
/*Creat uart default */
Uart_builder Uart_creat_default()
{
    Uart_builder  default_uart;

    default_uart.config.Start_bit = START_BIT_DEFAULT;
    default_uart.config.Baud_rate = BAUD_RATE_DEFAULT;
    default_uart.config.Data_bits = DATA_BITS_DEFAULT;
    default_uart.config.Stop_bit = STOP_BIT_DEFAULT;
    default_uart.config.Parity = PARITY_BIT_DEFAULT;

    return default_uart;
}

/*set baud rate*/
void Uart_set_baud_rate(Uart_builder *inital , uint32_t Baud_rate_change)
{
    inital->config.Baud_rate = Baud_rate_change;
}

/*Set parity*/
void Uart_set_parity(Uart_builder *inital, uint8_t parity_change)
{
    inital->config.Parity = parity_change;
}

/*Set stop bits*/
void Uart_set_stop_bits(Uart_builder *inital , uint8_t Stop_bit_change)
{
    inital->config.Stop_bit = Stop_bit_change;
}

/*uart config */
Uart_config Uart_set(Uart_builder *inital)
{
    return inital->config;
}

/*print uart*/
void Print_uart(Uart_config inital)
{
    printf(" UART Config:\n");
    printf("  Start bit : %d\n", inital.Start_bit);
    printf("  Baud rate : %d\n", inital.Baud_rate);
    printf("  Data bits : %d\n", inital.Data_bits);
    printf("  Parity    : %d\n", inital.Parity);
    printf("  Stop bits : %d\n", inital.Stop_bit);
    printf("------------------------------------\n");
}
