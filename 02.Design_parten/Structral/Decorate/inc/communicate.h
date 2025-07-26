#ifndef COMMUNICATE_H
#define COMMUNICATE_H
    #include <stdio.h>
    #include <stdint.h>

   
    typedef struct{
        uint8_t buffer[256];
        size_t size;
    }Raw_data;


    typedef struct{
        int (*send)(void* instance, const uint8_t* data, size_t length);
        int (*receive)(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
        void* instance;

    }Channel;
    
    Channel create_raw_channel(Raw_data *raw);
   
#endif