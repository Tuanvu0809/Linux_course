# Middle Project
# <Chương trình quản lí máy ảo ubutu>

## 1. cấu truc thư 
    file
        console.txt
    inc
        cpu_monitor.h
        log.h
        network_monitor.h
        ram_monitor.h
        disk_monitor.h
    src
        cpu_monitor.c
        log.c
        network_monitor.c
        ram_monitor.c
        disk_monitor.c
    main.c
    Makefile
    Readme.h
## 2. Các file mã nguồn        
### a.         ram_monitor.c
- *Tính toán ra lượng Ram sử dụng*
- *Tính toán Swap Ram*    
- *Kiểm tra xem những ứng dùng xài lượng ram cao*
### b.        disk_monitor.c
- *Tính toán dung lượng đĩa* 
- *Tính toán dung lượng đĩa i/o* (trong 1s)
### c.        network_monitor.c
- *Tính toán tốc độ băng thông* (trong 1s)
- *Kiểm tra địa chỉ IP của máy ảo*
### d.         cpu_monitor.c
- *Kiểm tra phần trăm sử dụng tổng thể và của từng core*
- *Kiểm tra tần số chạy của từng core*
- *Kiểm tra ứng dụng sủ dụng nhiều tài nguyên CPU nhất*
### e.          log.c
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
