# Middle Project
# <Chương trình quản lí máy ảo ubutu>

## 1. cấu truc thư 
    file
        console.txt
    inc
        cpu.h
        Handle_function.h
        Log.h
        network_parameter.h
        RAM.h
        Storetage.h
    src
        CPU_parameter.c
        Handle_function.c
        log.c
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
### d. cpu.h / CPU_parameter.c
- *Kiểm tra phần trăm sử dụng tổng thể và của từng core*
- *Kiểm tra tần số chạy của từng core*
- *Kiểm tra ứng dụng sủ dụng nhiều tài nguyên CPU nhất*
### e.Handle_function.c/Handle_function.h
- *Tạo hàm để người dùng lựa chọn kiểm tra*
### f. Logger.c/ Logger.h
- *Ghi lại những cảnh báo*
- *Tất cả các cảnh báo đều được ghi mới trong file/console.txt*
## 3.Chương trình chính:

- Khởi tạo file cảnh báo console.txt.
- In ra menu ở console và cho người dùng nhập lựa chọn để kiểm tra máy ảo Ubutu. 

    MENU
    
            ------------------------
           0.Check CPU
           1. Check Ram
           2. Check Storetage
           3. Check Network
           4. Exit
            ------------------------
- Nhập các số từ 0 -4 để kiểm tra các Parameter.

## 4. Chạy chương trình
- Sử dụng Makefile build chương trình.

        make
- Chạy chương trình. 
    
        ./Mid_project

- Xóa Target

        make clean
