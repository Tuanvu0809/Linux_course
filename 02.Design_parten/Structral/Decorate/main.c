#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "inc/communicate.h"
#include "inc/CRC.h"
#include "inc/Log.h"
#include "inc/XOR.h"
#include "inc/decorate.h"


int main() {
    // Tạo kênh thô (giả lập UART)
    Raw_data rawStorage = {0};
    Channel raw = create_raw_channel(&rawStorage);

    // Xây lớp: mã hóa -> CRC -> log
    Channel enc = create_encrypt_channel(&raw, 0x5A);     // XOR mã hóa
    Channel crc = create_crc_channel(&enc);               // Thêm CRC
    Channel log = create_logging_channel(&crc);          // Ghi log

    // Gửi dữ liệu
    uint8_t data[] = {0x10, 0x20, 0x30, 0x40};
    log.send(log.instance, data, sizeof(data));

    // Nhận lại
    uint8_t buffer[64];
    size_t received;
    log.receive(log.instance, buffer, sizeof(buffer), &received);

    // In ra
    printf("Data recieve is (%zu byte): ", received);
    for (size_t i = 0; i < received; i++)
        printf("%02X ", buffer[i]);
    printf("\n");

    return 0;
}
