#  [LIBRARY MANAGMENT]

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
        ├── src
        │ └── Library.c 
        ├── inc
        │ └── Library.h 
        ├── main.c 
        ├── Makefile 
        └── eadme.md 

## Các chức năng:

=====**HỆ THỐNG QUẢN LÝ THƯ VIỆN** =====

1.  Thêm sách mới.
2.  Xóa sách.
3.  Hiển thị tất cả sách.
4.  Thêm người dùng mới.
5.  Xóa người dùng.
6.  Hiển thị tất cả người dùng.
7.  Mượn sách.
8.  Trả sách.
9.  Hiển thị sách đang được mượn.
10. Hiển thị lại menu.
11. Thoát.
    

## 📁 Cấu trúc dữ liệu chính.
### Enum.
    Các lựa chọn cho người dùng ( Choice)
            typedef enum
            {
                Exit = 0,
                Add_book,
                Remove_book,
                List_book,
                Add_user,
                List_User,
                Borrowed_book,
                Return_book,
                List_Borrow_book,
                Menu,
            } Choice;
Các lựa chọn cho **người dùng**.

    Tình trạng sách đã được mượn hay chưa (Book_status)
            typedef enum
            {
                Available = 0,
                Unavailable,
            } Book_status;
Tình trạng sách.

### Struct

**Book - Sách**.

            typedef struct {
                int id;
                char title[MAX_LENGTH_TITLE];
                char author[MAX_LENGTH_AUTHOR];
                BookStatus status; 
            } Book;

**Person - Người dùng**.

        typedef struct {
            int id;
            char name[MAX_LENGTH_NAME];
            int nums_book;
        } Person;

**Library - Thư viện**.

        typedef struct {
            Book *Book_at_library;
            int Store_book;
            Person *person_user;
            int person_users;
        } Library;

## ❗ Xử lý lỗi

Hệ thống sử dụng kiểu enum ErrorCode để quản lý trạng thái lỗi:

        typedef enum
        {
            SUCCESS = 0,
            INIT_LIBRARY_FAIL,
            ERROR_INVALID_ID,
            ERROR_INVALID_NAME,
            ERROR_LIBRARY_FULL,
            ERROR_USER_FULL,
            ERROR_BOOK_NOT_FOUND,
            ERROR_USER_NOT_FOUND,
            ERROR_BOOK_ALREADY_BORROWED,
            ERROR_BOOK_NOT_BORROWED,
            Empty,
        } ErrorCode;

## Mỗi thao tác đều in ra thông báo tương ứng.

🔧 Định hướng phát triển

- Lưu và tải dữ liệu từ file

- Thêm giao diện đồ họa hoặc giao diện web

- Hỗ trợ phân loại sách, thời hạn mượn, thống kê

- Tối ưu hóa nhập dữ liệu từ người dùng

# 📄 Mô tả File `main.c` .

## 🔰 Giới thiệu

File `main.c` là chương trình chính của hệ thống quản lý thư viện, viết bằng ngôn ngữ C. Tệp này thực hiện vai trò:

- Khởi tạo hệ thống quản lý thư viện.
- Hiển thị menu các chức năng cho người dùng.
- Nhận lựa chọn từ người dùng thông qua bàn phím.
- Gọi các hàm xử lý tương ứng dựa trên lựa chọn.
- Thoát chương trình khi người dùng chọn “Exit”.

---
***Hàm Main (int main())***
#### a. Khởi tạo thư viện.

            if (Init_library() == -1)
            {
                printf("fail library\n");
                return -1 ;
            }

Khởi tạo thư viện và trả về mã lỗi.

Biến **Your_choice** để chứa lựa chọn của người dùng. 

            Choice Your_choice;

#### b. Vòng lặp xử lý lựa chọn

            do {
                scanf("%d", &Your_choice);
                choose_fuction(Your_choice);
            } while (Your_choice != Exit);

Nhập lựa chọn từ người dùng.
Gọi hàm choose_fuction() để thực hiện chức năng tương ứng.
Lặp lại cho đến khi người dùng chọn **Exit**.
#### b.Hàm choose_fuction()

            void choose_fuction(Choice already_choice);

Duyệt qua mảng ánh xạ action[] để tìm đúng hàm xử lý.
Nếu lựa chọn chưa được hỗ trợ, in ra thông báo.

## 🧩 Cấu trúc hoạt động

### Khởi tạo các biến quản lí trong thư viện

    static Library *manage = NULL;
    extern ErrorCode Fault_display;
Biến ***manage** chứa cấu trúc dữ liệu của Struct **Library** và được dùng nội bộ chỉ trong **Library.c**.

Biến **Fault_display** được chia sẻ từ file **Main.c** để xuất ra các thông báo lỗi, cũng như việc chức năng có thành công hay không.  


### 1. Khởi tạo thư viện 

**int Init_library()**.

            int Init_library()
            {

            manage = (Library *)malloc(sizeof(Library));

            if (manage == NULL){
                Fault_display = INIT_LIBRARY_FAIL;
                return -1;
            }    
            else{
                manage->Store_book = 0;
                manage->person_users = 0;
                printf("Library init success");
            }

            return 0;
            }

Gọi hàm Init_library() để cấp phát bộ nhớ và chuẩn bị dữ liệu.

Thoát chương trình nếu khởi tạo thất bại.

### 2. Hiển thị menu

 **void print_menu()**.
   
        void print_menu()
        {
            printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
            printf("1. Add new book\n");
            printf("2. Remove book\n");
            printf("3. Display all books\n");
            printf("4. Add new user\n");
            printf("5. Remove user\n");
            printf("6. Display all users\n");
            printf("7. Borrow book\n");
            printf("8. Return book\n");
            printf("9. Display user's borrowed books\n");
            printf("10.Print Menu\n");
            printf("0. Exit\n");
        }

In ra danh sách các lựa chọn mà người dùng có thể thao tác.

### 3. Các hàm xử lí logic (thêm, xóa, hiện thị).


