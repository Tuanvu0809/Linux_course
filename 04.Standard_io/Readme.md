# Logger

#### 🧠 Mục đích của chương trình

Tạo ra một hệ thống ghi log đơn giản dùng trong các ứng dụng C, giúp ghi lại thông báo lỗi, cảnh báo, thông tin hệ thống,... kèm timestamp và thông tin vị trí trong mã nguồn.

🔍 Cấu trúc chương trình

## 1. File main.c

    Đây là nơi kiểm tra và sử dụng logger.

         #include <stdio.h>
         #include <stdlib.h>
         #include "inc\log.h"

Các bước thực hiện trong main():

#### Khởi tạo logger:

        Log_init(LOG_DEBUG,"file/console.txt")

Ghi log ở cấp DEBUG trở lên vào file console.txt.

Ghi một số log với các cấp khác nhau:

        log_message(LOG_ERROR,"Auto test");
        log_message(LOG_DEBUG,"not seen");
        log_message(LOG_ALERT,"%s %s %s","test more","ok","excellent");

#### Thay đổi cấp ghi log:

        Set_log_level(LOG_WARNING);

#### Ghi log sau khi thay đổi cấp (chỉ log từ WARNING trở lên mới được ghi):

        log_message(LOG_NOTICE,"cant seen"); // bị bỏ qua
        log_message(LOG_ERROR, "seen"); // được ghi
        log_message(LOG_EMERGENCY," NEED"); // được ghi

#### Đóng logger:

        Log_close();

## 1. File log.c (hoặc phần định nghĩa hàm)

Biến toàn cục
Handle_log: con trỏ file dùng để ghi log.

level: cấp độ hiện tại của log.

Hàm Log_init()

##### Khởi tạo logger:

Lưu cấp độ ghi log.

Mở file log nếu có đường dẫn.

Hàm Set_log_level()

#### Thay đổi cấp độ log trong khi đang chạy chương trình.

Hàm Log_close()
Đóng file log khi không cần nữa.

Hàm Logger_log_handle()
Ghi log thực sự:

#### Kiểm tra cấp độ log:

- Nếu Log hiện tại ít nguy hiểm log Set
  if(set > level ) return;
  Lấy thời gian hiện tại.
  Định dạng chuỗi log sử dụng va_list:
  Cho phép truyền nhiều tham số giống printf.

Console: stderr cho lỗi, stdout cho thông tin.

File: nếu Handle_log mở thành công.

1.  File log.h (giả định nội dung)

            #ifndef LOG_H
            #define LOG_H

            typedef enum {
                LOG_EMERGENCY = 0,
                LOG_ALERT,
                LOG_CRITICAL,
                LOG_ERROR,
                LOG_WARNING,
                LOG_NOTICE,
                LOG_INFO,
                LOG_DEBUG
            } Log_level;

            int Log_init(Log_level current_level, const char \*File);
            void Set_log_level(Log_level Set);
            void Log_close();

            #define log_message(level, ...) \
            Logger_log_handle(level, __FILE__, __LINE__, VA_ARGS)       void Logger_log_handle(Log_level set, const char *file, const int line, const char *avr ,...);

            #endif

    ## 📝 Kết luận

    Chương trình này:

Cho phép tùy chọn cấp độ log.

Ghi log vào file và/hoặc màn hình.

Có hỗ trợ định dạng chuỗi và thông tin vị trí lỗi (**FILE**, **LINE**,).

Hữu ích cho debugging và ghi nhật ký trong các chương trình nhúng hoặc ứng dụng lớn.
