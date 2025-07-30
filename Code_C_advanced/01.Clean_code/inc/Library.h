#ifndef LIBRARY_H
#define LIBRARY_H

        #define MAX_LENGTH_TITLE 100
        #define MAX_LENGTH_AUTHOR 80
        #define MAX_LENGTH_NAME 80
        #define MAX_BOOK_CAN_BORROWED 10
        #define BOOK_CAN_STORE 50
        #define PERSON_USER_MAX 100
        
        /*Enum*/
        typedef enum
        {
            Exit = 0,
            Add_book,
            Remove_book,
            List_book,
            Add_user,
            List_User,
            List_all_user,
            Borrowed_book,
            Return_book,
            List_Borrow_book,
            Menu,
        } Choice;

        typedef enum
        {
            SUCCESS = 0,
            ERROR_INIT_LIBRARY,
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

        typedef enum
        {
            Available = 0,
            Unavailable,
        } Book_status;

        /*information book*/
        typedef struct
        {
            Choice choose;
            void (*Function_use)();
        } Choice_fuction;
        typedef struct
        {
            int id;
            char title[MAX_LENGTH_TITLE];
            char author[MAX_LENGTH_AUTHOR];
            Book_status status;
        } Book;

        /*information person*/
        typedef struct
        {
            int id;
            char name[MAX_LENGTH_NAME];
            int id_book_already_borrowed[MAX_BOOK_CAN_BORROWED];
            int nums_book;
        } Person;

        /*information library*/
        typedef struct
        {
            Book Book_at_library[BOOK_CAN_STORE];
            int Store_book;
            Person person_user[PERSON_USER_MAX];
            int person_users;
        } Library;

        int Init_library();
        Library *Libary_manage();
        char *Fault(ErrorCode Fault);

        void print_error();
        void print_menu();
        void Add_that_book();
        void Remove_that_book();
        void List_all_book();
        void Add_user_for();
        void List_user_for();
        void Borrowed_that_book();
        void Return_that_book();
        void List_borrow_that_book();
        void Exit_library();
        void Display_all_users();

#endif