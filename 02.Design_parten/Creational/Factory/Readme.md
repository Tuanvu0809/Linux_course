# Mô phỏng hệ thống cảm biến sử dụng Factory Pattern
## 1.Cấu trúc các thư mục.    
    
    Factory
    ├── inc                   
    │   ├── factory.h          
    │   ├── sensor.h           
    │   ├── light.h            
    │   └── temp.h            
    │
    ├── src                 
    │   ├── factory.c          
    │   ├── light.c           
    │   ├── temp.c             
    │
    ├── main.c                
    │
    ├── Makefile             
    │
    └── Readme.md              

## 2.  Tổng quan:
- Chương trình mô phỏng quá trình khởi tạo và sử dụng các cảm biến (sensor) như cảm biến nhiệt độ và ánh sáng thông qua Factory Design Pattern (mẫu thiết kế nhà máy).
 - Mẫu thiết kế này cho phép tạo ra các đối tượng cảm biến khác nhau mà không cần biết rõ lớp cụ thể nào đang được tạo ra.

## 3.Các thành phần chính:
**sensor (Struct/Interface chính):**
- Chứa các con trỏ hàm:
- init(): khởi tạo cảm biến.
- data(): lấy dữ liệu cảm biến dưới dạng float.
- CreatSensor(sensor_type) (Hàm factory):**Nhận vào loại cảm biến (temp hoặc light).**

**Cấp phát bộ nhớ và khởi tạo đối tượng phù hợp với loại cảm biến yêu cầu.**
- Trả về con trỏ đến đối tượng sensor.

**Các loại cảm biến:**

- Temperature_sensor: cảm biến nhiệt độ, mô phỏng trả về một giá trị nhiệt độ.
- Light_sensor: cảm biến ánh sáng, mô phỏng trả về độ sáng.

## 4. Diễn biến chương trình:

- Khởi tạo và sử dụng cảm biến nhiệt độ:
  - Gọi CreatSensor(temp) để tạo sensor nhiệt độ.
- Nếu thành công:
  - Gọi init() để mô phỏng khởi tạo cảm biến.
  - Gọi data() để lấy dữ liệu nhiệt độ và in ra màn hình.
- Giải phóng bộ nhớ cấp phát.
- Khởi tạo và sử dụng cảm biến ánh sáng:
- Gọi CreatSensor(light) để tạo sensor ánh sáng.
- Nếu thành công:
  - Gọi init() để mô phỏng khởi tạo cảm biến.
  - Gọi data() để lấy dữ liệu ánh sáng và in ra màn hình.
- Giải phóng bộ nhớ cấp phát.