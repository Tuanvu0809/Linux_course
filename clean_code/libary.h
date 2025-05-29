#ifndef LIBARY_H
#define LIBARY_H
    #define Max_tittle_arthour     100
    #define Max_name         100
    #define Max_borrowed     1000
    #define Max_book         100
    #define Max_user        100

/*enum*/
    /*case*/
    typedef enum{
        Exit =0 ,
        Add_book,
        Remove_book,
        List_book,
        Add_user,
        Remove_user,
        List_User,
        Borrowed_book,
        Return_book,
        List_Borrow_book,
        Menu,
    }choice;

    

    typedef enum{
        Available,
        Borrower,
    }Bookstatus;


    // Error codes
    typedef enum {
        SUCCESS  = 0 ,
        ERROR_INVALID_ID,
        ERROR_INVALID_NAME,
        ERROR_LIBRARY_FULL,
        ERROR_USER_FULL,
        ERROR_BOOK_NOT_FOUND,
        ERROR_USER_NOT_FOUND,
        ERROR_BOOK_ALREADY_BORROWED,
        ERROR_BOOK_NOT_BORROWED,
    } ErrorCode;

/*struct */    
    /*libary*/
    typedef struct{
        int ID_book;
        char Tittle[Max_tittle_arthour];
        char Arthour[Max_tittle_arthour];
        Bookstatus Status;
    }Book;

    /*user*/
    typedef struct{
        int ID_user;
        char Name_User[Max_name];
        int Borrowedbook[Max_borrowed];
        int Borrowedcount;
    }User;

    /*libary*/
    typedef struct{
        Book Books_lib[Max_book];
        int Bookcount;
        User user_libary[Max_user];
        int Usercount;
   }Libary;




    void initlib(Libary *libary);


    void printMenu() ;
    void Add_book_function(Libary *libary);
    void Remove_book_function(Libary *libary);
    void List_book_function(Libary *libary);
    void Add_user_function(Libary *libary);
    void Remove_user_fucnction(Libary *libary);
    void List_user_fucntion(Libary *libary);
    void Borrowed_book_fucntion(Libary *libary);
    void Return_book_fucntion(Libary *libary);
    void List_borrow_book_fucntion(Libary *libary);


   
    void Exit_function();


   static char *Status_of_book(Bookstatus status);
   static ErrorCode Fault_add_book(Libary *libary,int ID,char *Tittle, char * arthour);
   static ErrorCode Fault_remove_user(Libary *libary, int ID);
   static ErrorCode Fault_borrowed_book(Libary *libary, int ID_book, int ID_user);
   static ErrorCode Fault_return_book(Libary *libary, int ID_book, int ID_user);

   static char* Fault(ErrorCode Fault);
   static ErrorCode Fault_remove_book(Libary *libary, int ID_remove);
   static ErrorCode Fault_borrowed_book(Libary *libary, int ID_book, int ID_user);






#endif