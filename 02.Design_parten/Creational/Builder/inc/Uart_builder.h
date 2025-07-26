#ifndef UART_BUILDER_H
#define UART_BUILDER_H
    #include <stdio.h>
    #include <stdint.h>

    #define START_BIT_DEFAULT   1
    #define BAUD_RATE_DEFAULT   9600
    #define DATA_BITS_DEFAULT   8
    #define STOP_BIT_DEFAULT    1
    #define PARITY_BIT_DEFAULT   1

    typedef struct  {
        uint8_t Start_bit;
        uint32_t Baud_rate;
        uint8_t Data_bits;
        uint8_t Stop_bit;
        uint8_t Parity;
    } Uart_config ;

    typedef struct {
        Uart_config config;

    } Uart_builder ;

    Uart_builder Uart_creat_default();
    void Uart_set_baud_rate(Uart_builder *inital , uint32_t Baud_rate_change);
    void Uart_set_parity(Uart_builder *inital, uint8_t parity_change);
    void Uart_set_stop_bits(Uart_builder *inital , uint8_t stop_bit_change);
    Uart_config Uart_set(Uart_builder *inital);
    void Print_uart(Uart_config inital);


#endif