
# Module UART Builder

Đây là module áp dụng **mẫu thiết kế Builder (Builder Pattern)** trong ngôn ngữ lập trình C để cấu hình UART theo từng bước trong hệ thống nhúng. Mục đích là giúp cấu hình UART một cách **linh hoạt, rõ ràng và dễ mở rộng**, thay vì truyền toàn bộ tham số một lần.

---

## 📁 Cấu trúc thư mục

    src/
    ├── Uart_builder.c
    inc/
    ├── Uart_builder.h
    main.c
    Readme.md
    Makefile



---

## ⚙️ Cấu trúc dữ liệu

### `Uart_config` – Cấu hình UART

    typedef struct {
        uint8_t Start_bit;
        uint32_t Baud_rate;
        uint8_t data_bits;
        uint8_t stop_bit;
        uint8_t Parity;
    } Uart_config;

Uart_builder – Bộ xây dựng cấu hình

    typedef struct {
        Uart_config config;
    } Uart_builder;

## Hướng dẫn sử dụng API

### 1. Tạo cấu hình mặc định

        Uart_builder creat = Uart_creat();

### 2. Thiết lập từng thành phần

    Uart_set_baud_rate(&creat, 115200);
    Uart_set_parity(&creat, 0);      
    Uart_set_stop_bits(&creat, 2);

### 3. Lấy cấu hình cuối cùng

    Uart_config final;
    final = creat.config;
    Print_uart(final);

#### 4. In cấu hình ra màn hình (để kiểm tra)

        Print_uart(final);