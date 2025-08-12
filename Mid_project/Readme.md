# Middle Project
# <Chương trình quản lí máy ảo ubutu>

## 1. cấu truc thư mục
    inc
        CPU_parameter.h
        Handle_function.h
        network_parameter.h
        RAM.h
        Storetage.h
    src
        CPU_parameter.c
        Handle_function.c
        network_parameter.c
        RAM.c
        Storetage.c
    main.c
    Makefile
    Readme.h
## 2. Các file mã nguồn        
### a. RAM_parameter.h/ RAM_parameter.c
- *Tính toán ra lượng Ram sử dụng*
- *Tính toán Swap Ram*    
- *Kiểm tra xem những ứng dùng xài lượng ram cao*
### b. Disk_parameter.h/ Disk_parameter.c
- *Tính toán dung lượng đĩa* 
- *Tính toán dung lượng đĩa i/o* (trong 1s)
### c.Network_parameters.h/ Network_parameters.c
- *Tính toán tốc độ băng thông* (trong 1s)
- *Kiểm tra địa chỉ IP của máy ảo*
### d. CPU_parameter.h / CPU_parameter.c
- *Kiểm tra phần trăm sử dụng tổng thể và của từng core*
- *Kiểm tra tần số chạy của từng core*
- *Kiểm tra ứng dụng sủ dụng nhiều tài nguyên CPU nhất*
### e.Handle_function.c/Handle_function.h
- *Tạo hàm để nhười dùng lựa chọn kiểm tra*
