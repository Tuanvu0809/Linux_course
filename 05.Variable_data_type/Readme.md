# Smart Plant Watering System - SPWS

## 🎯 MỤC TIÊU CHƯƠNG TRÌNH

Thiết kế một hệ thống tưới cây tự động thông minh sử dụng cảm biến độ ẩm và nhiệt độ để tự động điều khiển bơm tưới nước. Người dùng có thể chuyển đổi giữa chế độ tự động và thủ công, đồng thời có thể kích hoạt tưới bằng nút bấm mô phỏng. Mọi trạng thái đều được in ra console để mô phỏng hoạt động của hệ thống nhúng.

## 📁 TỔNG QUAN CÁC FILE


    main.c .
    config.h .
    sensors.c/h .
    actuators.c/h. 
    buttons.c/h. 
    watering_logic.c/h.  

## 🧱 CẤU TRÚC DỮ LIỆU

    typedef struct{
    int Temperature;
    int Moisture;
    }data;

Giữ giá trị độ ẩm đất và nhiệt độ không khí.

    typedef struct{
    int moisture_min;
    int moisture_max;
    int times;
    int check;
    MODE Mode_sys;
    }SETTING;

Giữ các tham số cấu hình hệ thống và chế độ hoạt động.

## ⚙️ MÔ TẢ CHỨC NĂNG CHÍNH

### main.c

Khởi tạo hệ thống (khởi tạo bơm và cập nhật trạng thái led ).

Thiết lập thông số mặc định (ngưỡng độ ẩm, thời gian tưới .... ).

Khởi tạo giá trị mặc định là auto

Vào vòng lặp vô hạn để xử lý:

Mô phỏng nhấn nút chuyển chế độ hoặc tưới thủ công ngẫu nhiên.

Xử lý logic tưới nếu đang ở chế độ tự động/ chế độ tay.

### Sensors.c

Hàm Read_sensors() mô phỏng giá trị cảm biến:
Độ ẩm đất từ 0% - 100%.
Nhiệt độ không khí từ 20°C - 35°C.
Giá trị được in ra console.

### actuators.c

turn_pump_on() và turn_pump_off() để mô phỏng điều khiển bơm.

### led.c

Turn_led(LED_STATUS led) để cập nhập tình trạng led.

trạng thái bình thường: Tất cả Led tắt.
trạng thái tưới: Led xanh sáng.
trạng thái độ ẩm thấp: led vàng sáng.
trạng thái hư hỏng : led đỏ sáng.( chưa có trường hợp này).

### buttons.c

Set_for_auto():

Chuyển đổi giữa MODE_AUTO và MODE_MANUAL.

Tắt bơm nếu chuyển sang MODE_MANUAL.

Set_for_manual():

Nếu ở MODE_MANUAL → tắt bơm.

watering_logic.c
Nếu đang ở MODE_AUTO, đọc cảm biến và kiểm tra:

Nếu độ ẩm thấp hơn moisture_min và đủ thời gian trễ kể từ lần tưới trước, sẽ:

Bật bơm.

Đợi đủ thời gian tưới (sử dụng sleep()).

Tắt bơm.

Mỗi lần đọc, cập nhật giá trị cảm biến và in trạng thái ra console.

## ✅ TÍNH NĂNG ĐÃ HOÀN THÀNH

Đọc cảm biến mô phỏng (sử dụng random).

Sử dụng hàm scanf để điều chỉnh giá trị/ thực tế sẽ sửa dụng Interrupt và nút nhấn để chuyển đổi .

Điều khiển bơm theo ngưỡng độ ẩm.

Chuyển chế độ tự động / thủ công.

Tưới tay bằng nút mô phỏng.

Hiển thị LED trạng thái.

Thông báo rõ ràng từng trạng thái ra console.
