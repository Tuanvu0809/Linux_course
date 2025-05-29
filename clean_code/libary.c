#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "libary.h"

void initlib(Libary *libary)
{
    libary->Bookcount = 0;
    libary->Usercount = 0; 
}
static char* Fault(ErrorCode Fault)
{
    switch (Fault) {
        case SUCCESS: 
            return "Success\n";
        case ERROR_INVALID_ID: 
            return "Invalid ID\n";
        case ERROR_INVALID_NAME: 
            return "Invalid name\n";
        case ERROR_LIBRARY_FULL: 
            return "Library is full\n";
        case ERROR_BOOK_NOT_FOUND: 
            return "Book not found\n";
        case ERROR_USER_NOT_FOUND: 
            return "User not found\n";
        case ERROR_BOOK_ALREADY_BORROWED: 
            return "Book already borrowed\n";
        case ERROR_BOOK_NOT_BORROWED: 
            return "Book not borrowed by this user\n";
        default: 
            return "Unknown error\nn";
    }

}
void printMenu() {
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

static bool Check_ID(int ID)
{
    return ID > 0;
}
static bool Check_Tittle_arthour(char *tittle_or_authour)
{
    return (tittle_or_authour != NULL) && (strlen(tittle_or_authour) >0) ;
}
static ErrorCode Fault_add_book(Libary *libary,int  ID,char *Tittle, char * arthour)
{
    if( Check_ID(ID) == false  )
        return ERROR_INVALID_ID;
    if( Check_Tittle_arthour(Tittle) == false || Check_Tittle_arthour(arthour) == false)
        return ERROR_INVALID_NAME;
    if(libary->Bookcount >= Max_book )
        return ERROR_LIBRARY_FULL;
    for (int i = 0; i<= libary->Bookcount; i++)
    {
        if(ID == libary[i].Books_lib->ID_book)  
            return ERROR_INVALID_ID;
    }
    Book *newbook = (Book*) malloc(sizeof(Book)) ;

    newbook->ID_book = ID;

    strncpy(newbook->Tittle,Tittle,Max_tittle_arthour - 1);
    newbook->Tittle[Max_tittle_arthour - 1] ='\0';

    strncpy(newbook->Arthour,arthour, Max_tittle_arthour - 1);
    newbook->Arthour[Max_tittle_arthour - 1] = '\0';

    newbook->Status = Available;

    libary->Books_lib[libary->Bookcount] = *newbook;

    libary->Bookcount ++ ;

    return SUCCESS;

}



void Add_book_function(Libary *libary)
{
    int ID_new;
    char Tittle_new[Max_tittle_arthour];
    char Arthour_new[Max_tittle_arthour];

    printf("Enter ID: ");
    scanf("%d", &ID_new);
    getchar();

    printf("Enter titile: ");
    fgets(Tittle_new,Max_tittle_arthour,stdin);
    Tittle_new[strcspn(Tittle_new,"\n")] = 0;

     printf("Enter arthour: ");
    fgets(Arthour_new,Max_tittle_arthour,stdin);
    Arthour_new[strcspn(Arthour_new,"\n")] = 0;
    ErrorCode fault_add = Fault_add_book(libary,ID_new,Tittle_new,Arthour_new);
    printf("%s\n", Fault(fault_add) );
    

}
static ErrorCode Fault_remove_book(Libary *libary, int ID_remove){
    if(Check_ID(ID_remove) == false)
        return ERROR_INVALID_ID;
    int find = -1;
    for( int i=0; i<= libary->Bookcount ; i++ )
    {
        if(ID_remove == libary->Books_lib[i].ID_book)
            find = i;
    }

    if(find == -1 )
        return ERROR_BOOK_NOT_FOUND;

    for( int i = find; i <= libary->Bookcount - 1; i++ ){
        libary->Books_lib[i]    =   libary->Books_lib[i+1];

    }
    libary->Bookcount --;
    
    return SUCCESS;

}
void Remove_book_function(Libary *libary)
{
    int ID_remove;
    printf("Enter ID need remove: ");
    scanf("%d",&ID_remove);
    getchar();

    ErrorCode fault_remove = Fault_remove_book(libary,ID_remove);

    printf("%s\n",Fault(fault_remove));


    
}
static char *Status_of_book(Bookstatus status)
{
    if(status == Available )    return "Available";
    return "Borrower";
}
void List_book_function(Libary *libary)
{
    for ( int i= 0 ; i <= libary->Bookcount-1 ;i++)
    {
        printf("%3d %10s %10s %s\n",libary->Books_lib[i].ID_book,libary->Books_lib[i].Tittle,libary->Books_lib[i].Arthour,Status_of_book(libary->Books_lib[i].Status));

    }
}

static bool Check_name(char *name)
{
    return name != NULL && strlen(name) >0;
}
static ErrorCode Fault_add_user(Libary *libary,int ID, char *name)
{
    if(Check_ID(ID) == false)
        return ERROR_INVALID_ID;
    if(Check_name(name)  != true )
        return ERROR_INVALID_NAME;
    if(libary->Usercount >= Max_user)
        return ERROR_USER_FULL;
    
    User newuser;
    newuser.ID_user = ID;
    strcpy(newuser.Name_User,name);

    libary->user_libary[libary->Usercount ] = newuser;
    libary->Usercount++;

    return SUCCESS;
    
    
   
} 
void Add_user_function(Libary *libary)
{
    char name_new[Max_name];
    int ID_new;

    
    printf("Enter ID: ");
    scanf("%d", &ID_new);
    getchar();


    printf("Enter name: ");
    fgets(name_new,Max_name,stdin);
    name_new[strcspn(name_new,"\n")] =0 ;

    ErrorCode fault_new_user = Fault_add_user(libary,ID_new,name_new);

    printf("%s\n",Fault(fault_new_user));
}
static ErrorCode Fault_remove_user(Libary *libary, int ID)
{
    if (Check_ID(ID)==false)
        return ERROR_INVALID_ID;
    int index_id = -1;
    for ( int i = 0; i<=libary->Usercount;i++ )
    {
        if(ID == libary->user_libary[i].ID_user){
            index_id = i;
            break;
        }    
    }
    if(index_id  == -1 )
        return ERROR_USER_NOT_FOUND;
    
    for( int i =index_id ;i<= libary->Usercount ; i++)
    {
        libary->user_libary[i] = libary->user_libary[i + 1];
    }

    libary->Usercount -- ;

    return SUCCESS;
    

}
void Remove_user_fucnction(Libary *libary)
{
    int ID_need_remove;

    printf("Enter ID need remove:");
    scanf("%d", &ID_need_remove);
    getchar();

    ErrorCode fault_remove_user = Fault_remove_user(libary,ID_need_remove);

    Fault(fault_remove_user);
 

}
void List_user_fucntion(Libary *libary)
{
    for (int i= 0; i< libary->Usercount ;i++)
    {
        printf("%3d %20s %3d %3d \n",libary->user_libary[i].ID_user,libary->user_libary[i].Name_User,libary->user_libary[i].Borrowedbook,libary->user_libary[i].Borrowedcount);
    }
}
static ErrorCode Fault_borrowed_book(Libary *libary, int ID_book, int ID_user)
{
    if (Check_ID(ID_book)==false || Check_ID(ID_user) == false)
        return ERROR_INVALID_ID;

    int index_id_book = -1;
    for ( int i = 0; i<=libary->Bookcount;i++ )
    {
        if(ID_book == libary->Books_lib[i].ID_book){
            index_id_book = i;
            if(libary->Books_lib[i].Status == Borrower)
                return ERROR_BOOK_ALREADY_BORROWED;
            break;
        }    
    }
     int index_id_user = -1;
    for ( int i = 0; i<=libary->Usercount;i++ )
    {
        if(ID_book == libary->user_libary[i].ID_user){
            index_id_user = i;
            break;
        }    
    }
    if(index_id_book  == -1 )
        return ERROR_BOOK_NOT_FOUND;
    if (index_id_user == -1)
        return ERROR_USER_NOT_FOUND;
    
    libary->Books_lib[index_id_book].Status = Borrower;
    libary->user_libary[index_id_user].Borrowedbook[libary->user_libary[index_id_user].Borrowedcount] = index_id_book;
    libary->user_libary[index_id_user].Borrowedcount ++;

    return SUCCESS;

}
void Borrowed_book_fucntion(Libary *libary)
{
    int Id_book;
    int Id_user;

    
    printf("Enter ID book:");
    scanf("%d", &Id_book);
    getchar();

    
    printf("Enter ID useruser:");
    scanf("%d", &Id_user);
    getchar();


    ErrorCode fault_borrowed_book = Fault_borrowed_book(libary,Id_book,Id_user);

    printf("%s",Fault(fault_borrowed_book));

}
static ErrorCode Fault_return_book(Libary *libary, int ID_book, int ID_user)
{
    if (Check_ID(ID_book)==false || Check_ID(ID_user) == false)
        return ERROR_INVALID_ID;

    int index_id_book = -1;
    for ( int i = 0; i<=libary->Bookcount;i++ )
    {
        if(ID_book == libary->Books_lib[i].ID_book){
            index_id_book = i;
            if(libary->Books_lib[i].Status == Available)
                return ERROR_BOOK_NOT_BORROWED;
            break;
        }    
    }
     int index_id_user = -1;
    for ( int i = 0; i<=libary->Usercount;i++ )
    {
        if(ID_book == libary->user_libary[i].ID_user){
            index_id_user = i;
            break;
        }    
    }
    if(index_id_book  == -1 )
        return ERROR_BOOK_NOT_FOUND;
    if (index_id_user == -1)
        return ERROR_USER_NOT_FOUND;
    
    libary->Books_lib[index_id_book].Status = Available;
 
    for( int i = index_id_book; i <= libary->Bookcount - 1; i++ ){
        libary->user_libary[i]   =   libary->user_libary[i+1];
    }
    libary->user_libary->Borrowedcount --;

    
    return SUCCESS;

}
void Return_book_fucntion(Libary *libary)
{
    int Id_book;
    int Id_user;

    
    printf("Enter ID book:");
    scanf("%d", &Id_book);
    getchar();

    
    printf("Enter ID useruser:");
    scanf("%d", &Id_user);
    getchar();

    ErrorCode fault_return_book= Fault_return_book(libary,Id_book,Id_user);

    Fault(fault_return_book);

}
void List_borrow_book_fucntion(Libary *libary)
{
    for ( int i= 0 ; i <= libary->Bookcount-1 ;i++)
    {

        if(libary->Books_lib[i].Status == Borrower){
             printf("%3d %10s %10s %s\n",libary->Books_lib[i].ID_book,libary->Books_lib[i].Tittle,libary->Books_lib[i].Arthour,Status_of_book(libary->Books_lib[i].Status));
        }    
    }
     
}
void Exit_function()
{
    printf(" Thank you use this program\n");
}


