# [LIBRARY MANAGMENT]

Đây là một dự án nhỏ viết bằng ngôn ngữ **C**, mô phỏng hệ thống quản lý thư viện cơ bản: cho phép thêm/xóa sách, người dùng, mượn/trả sách, và hiển thị thông tin.

## ✅ Tính năng

- Thêm / Xóa sách
- Thêm / Xóa người dùng
- Mượn / Trả sách
- Hiển thị:

  - Danh sách tất cả sách
  - Danh sách tất cả người dùng
  - Danh sách sách đang được mượn
  - Kiểm tra hợp lệ đầu vào và xử lý lỗi

    🧱 Cấu trúc thư mục

        LibrarySystem/
        ├── src/ # Các file mã nguồn (.c)
        │ └── Library.c # Triển khai logic chính
        ├── inc/ # Các file tiêu đề (.h)
        │ └── Library.h # Khai báo struct và hàm
        ├── main.c # Hàm main, giao diện menu chính
        ├── Makefile # (tuỳ chọn) Tự động biên dịch
        └── README.md # Tài liệu dự án

## Các chức năng:

===== HỆ THỐNG QUẢN LÝ THƯ VIỆN =====

1.  Thêm sách mới
2.  Xóa sách
3.  Hiển thị tất cả sách
4.  Thêm người dùng mới
5.  Xóa người dùng
6.  Hiển thị tất cả người dùng
7.  Mượn sách
8.  Trả sách
9.  Hiển thị sách đang được mượn
10. Hiển thị lại menu
11. Thoát

## 📁 Cấu trúc dữ liệu chính

### Book - Sách

            typedef struct {
                int id;
                char title[MAX_LENGTH_TITLE];
                char author[MAX_LENGTH_AUTHOR];
                BookStatus status; // Available | Unavailable
            } Book;

### Person - Người dùng

        typedef struct {
            int id;
            char name[MAX_LENGTH_NAME];
            int nums_book; // Số sách đang mượn
        } Person;

### Library - Thư viện

        typedef struct {
            Book *Book_at_library;
            int Store_book;
            Person *person_user;
            int person_users;
        } Library;

## ❗ Xử lý lỗi

Hệ thống sử dụng kiểu enum ErrorCode để quản lý trạng thái lỗi:

ERROR_INVALID_ID – Sai mã ID

ERROR_LIBRARY_FULL – Thư viện đầy

ERROR_BOOK_ALREADY_BORROWED – Sách đã được mượn

SUCCESS – Thao tác thành công

## Mỗi thao tác đều in ra thông báo tương ứng.

🔧 Định hướng phát triển

- Lưu và tải dữ liệu từ file

- Thêm giao diện đồ họa hoặc giao diện web

- Hỗ trợ phân loại sách, thời hạn mượn, thống kê

- Tối ưu hóa nhập dữ liệu từ người dùng

# 📄 Mô tả File `main.c`

## 🔰 Giới thiệu

File `main.c` là chương trình chính của hệ thống quản lý thư viện, viết bằng ngôn ngữ C. Tệp này thực hiện vai trò:

- Khởi tạo hệ thống quản lý thư viện.
- Hiển thị menu các chức năng cho người dùng.
- Nhận lựa chọn từ người dùng thông qua bàn phím.
- Gọi các hàm xử lý tương ứng dựa trên lựa chọn.
- Thoát chương trình khi người dùng chọn “Exit”.

---

## 🧩 Cấu trúc hoạt động

### 1. Khởi tạo thư viện

    if (Init_library() == -1) {
        printf("Khởi tạo thư viện thất bại!\n");
        return 1;
    }

Gọi hàm Init_library() để cấp phát bộ nhớ và chuẩn bị dữ liệu.

Thoát chương trình nếu khởi tạo thất bại.

### 2. Hiển thị menu

            print_menu();

    In ra danh sách các lựa chọn mà người dùng có thể thao tác.

#### a. Vòng lặp xử lý lựa chọn

            do {
                scanf("%d", &Your_choice);
                choose_fuction(Your_choice);
            } while (Your_choice != Exit);

Nhập lựa chọn từ người dùng.

Gọi hàm choose_fuction() để thực hiện chức năng tương ứng.

Lặp lại cho đến khi người dùng chọn Exit.

#### b.Hàm choose_fuction()

            void choose_fuction(Choice already_choice);

    Duyệt qua mảng ánh xạ action[] để tìm đúng hàm xử lý.

Nếu lựa chọn chưa được hỗ trợ, in ra thông báo.

### 🧠 Các kiểu dữ liệu liên quan

Choice (enum)

     typedef enum{
        Exit =0 ,
        Add_book,
        Remove_book,
        List_book,
        Add_user,
        List_User,
        Borrowed_book,
        Return_book,
        List_Borrow_book,
        Menu,
    }Choice;

Choice_fuction (struct)

    typedef struct {
    Choice choose;
    void (*Function_use)(void);
    } Choice_fuction;

## 📌 Ghi chú

Mã nguồn tổ chức rõ ràng, thuận tiện cho việc mở rộng.

Có thể dễ dàng thêm chức năng mới chỉ bằng cách thêm vào mảng action[].

Đảm bảo đầu vào hợp lệ để tránh lỗi khi nhập từ bàn phím.
