#include "../inc/Library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Library *manage = NULL;
extern ErrorCode Fault_display;

int Init_library()
{

    manage = (Library *)malloc(sizeof(Library));

    if (manage == NULL){
        Fault_display = ERROR_INIT_LIBRARY;
        return -1;
    }    
    else{
        manage->Store_book = 0;
        manage->person_users = 0;
        printf("Library init success");
    }

    return 0;
}

Library *Libary_manage()
{
    return manage;
}

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
/*Logic Fuction*/
char *Fault(ErrorCode Fault)
{
    switch (Fault)
    {
        case SUCCESS:
            return "Success\n";
        case ERROR_INIT_LIBRARY:
            return "Fail init library\n";
        case ERROR_INVALID_ID:
            return "Invalid ID\n";
        case ERROR_INVALID_NAME:
            return "Invalid name\n";
        case ERROR_LIBRARY_FULL:
            return "Library is full\n";
        case ERROR_USER_FULL:
            return "User full\n";
        case ERROR_BOOK_NOT_FOUND:
            return "Book not found\n";
        case ERROR_USER_NOT_FOUND:
            return "User not found\n";
        case ERROR_BOOK_ALREADY_BORROWED:
            return "Book already borrowed\n";
        case ERROR_BOOK_NOT_BORROWED:
            return "Book not borrowed by this user\n";
        case Empty:
            return "Empty book \n";
        default:
            return "Unknown error\n";
    }
}

void print_error(ErrorCode error)
{
    printf("\n %s", Fault(error));
}

static ErrorCode Can_add_book()
{
    if (manage->Store_book >= BOOK_CAN_STORE)
        return ERROR_LIBRARY_FULL;

    Book book_want_add;

    printf("\nEnter ID: ");
    if (scanf("%d", &book_want_add.id) == 1)
    {
        if ((book_want_add.id < 0) || (book_want_add.id > BOOK_CAN_STORE))
            return ERROR_INVALID_ID;
    }
    else
    {

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return ERROR_INVALID_ID;
    }
    getchar();

    printf("\nEnter title: ");
    fgets(book_want_add.title, MAX_LENGTH_TITLE, stdin);
    book_want_add.title[strcspn(book_want_add.title, "\n")] = 0;

    printf("\nEnter author: ");
    fgets(book_want_add.author, MAX_LENGTH_AUTHOR, stdin);
    book_want_add.author[strcspn(book_want_add.author, "\n")] = 0;

    for (int i = 0; i < manage->Store_book; i++)
    {
        if ((book_want_add.id == manage->Book_at_library[i].id))
            return ERROR_INVALID_ID;
        if ((strcmp(book_want_add.title, manage->Book_at_library[i].title) == 0) && (strcmp(book_want_add.author, manage->Book_at_library[i].author) == 0))
            return ERROR_INVALID_NAME;
    }

    book_want_add.status = Available;
    manage->Book_at_library[manage->Store_book++] = book_want_add;
    return SUCCESS;
}
static ErrorCode Can_remove_book()
{
    int id;
    printf("\nEnter ID: ");
    if (scanf("%d", &id) == 1)
    {
        if ((id < 0) || (id > BOOK_CAN_STORE))
            return ERROR_INVALID_ID;
    }
    else
    {
        int c;
        while (( c = getchar()) != '\n' && c != EOF) ;
        return ERROR_INVALID_ID;
    }
    getchar();

    for (int i = 0; i < manage->Store_book; i++)
    {
        if (id == manage->Book_at_library[i].id)
        {
            for (int j = i; j <= manage->Store_book - 1; j++)
            {
                manage->Book_at_library[j] = manage->Book_at_library[j + 1];
            }
            manage->Store_book--;
            return SUCCESS;
        }
    }
    return ERROR_BOOK_NOT_FOUND;
}
static ErrorCode Can_add_user()
{
    if (manage->person_users >= PERSON_USER_MAX)
        return ERROR_USER_FULL;

    Person person_want_add;
    printf("\nEnter ID: ");
    if (scanf("%d", &person_want_add.id) == 1)
    {
        if ((person_want_add.id < 0) || (person_want_add.id > PERSON_USER_MAX))
            return ERROR_INVALID_ID;
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return ERROR_INVALID_ID;
    }
    getchar();

    printf("\nEnter name: ");
    fgets(person_want_add.name, MAX_LENGTH_NAME, stdin);
    person_want_add.name[strcspn(person_want_add.name, "\n")] = 0;

    for (int i = 0; i < manage->Store_book; i++)
    {
        if ((person_want_add.id == manage->person_user[i].id))
            return ERROR_INVALID_ID;
        if ((strcmp(person_want_add.name, manage->person_user[i].name) == 0))
            return ERROR_INVALID_NAME;
    }

    person_want_add.nums_book = 0;
    manage->person_user[manage->person_users] = person_want_add;

    return SUCCESS;
}

static ErrorCode Can_return_book()
{
    int ID_name;
    int Position_person = -1;
    int Position_book = -1;

    printf("\nEnter ID name: ");
    if (scanf("%d", &ID_name) == 1)
    {
        if ((ID_name < 0) || (ID_name > PERSON_USER_MAX))
            return ERROR_INVALID_ID;
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
        return ERROR_INVALID_ID;
    }

    int ID_book;
    printf("\nEnter ID book: ");
    if (scanf("%d", &ID_book) == 1)
    {
        if ((ID_book < 0) || (ID_book > BOOK_CAN_STORE))
            return ERROR_INVALID_ID;
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
        return ERROR_INVALID_ID;
    }

    for (int i = 0; i < manage->person_users; i++)
    {
        if (ID_name == manage->person_user[i].id)
        {
            Position_person = i;
            break;
        }
      
    }

    if (Position_person == -1)
        return ERROR_USER_NOT_FOUND;

    for (int i = 0; i <= manage->Store_book; i++)
    {
        if (manage->Book_at_library[i].id == ID_book)
        {
            Position_book = i;
            break;
        }
    }

    if (Position_person == -1)
        return ERROR_USER_NOT_FOUND;
    if (Position_book == -1)
        return ERROR_BOOK_NOT_FOUND;

    if (manage->Book_at_library[Position_book].status == Available)
        return ERROR_BOOK_NOT_BORROWED;
    else
        manage->Book_at_library[Position_book].status = Available;

    if (manage->person_user[Position_person].nums_book == 0)
    {
        return Empty;
    }
    else
    {
        manage->person_user[Position_person].nums_book--;
    }

    return SUCCESS;
}
static ErrorCode Can_borrow_book()
{
    int ID_name;
    int Position_person = -1;
    int Position_book = -1;

    printf("\nEnter ID name: ");
    if (scanf("%d", &ID_name) == 1)
    {
        if ((ID_name < 0) || (ID_name > PERSON_USER_MAX))
            return ERROR_INVALID_ID;
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return ERROR_INVALID_ID;
    }

    int ID_book;

    printf("\nEnter ID book: ");
    if (scanf("%d", &ID_book) == 1)
    {
        if ((ID_book < 0) || (ID_book > BOOK_CAN_STORE))
            return ERROR_INVALID_ID;
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
        return ERROR_INVALID_ID;
    }

    for (int i = 0; i < manage->person_users; i++)
    {
        if (ID_name == manage->person_user[i].id)
        {
            Position_person = i;
            break;
        }
 
    }

    if (Position_person == -1)
        return ERROR_USER_NOT_FOUND;

    for (int i = 0; i <= manage->Store_book; i++)
    {
        if (manage->Book_at_library[i].id == ID_book)
        {
            Position_book = i;
            break;
        }
    }
    if (Position_person == -1)
        return ERROR_USER_NOT_FOUND;
    if (Position_book == -1)
        return ERROR_BOOK_NOT_FOUND;

    if (manage->Book_at_library[Position_book].status == Unavailable)
        return ERROR_BOOK_NOT_BORROWED;
    else
        manage->Book_at_library[Position_book].status = Unavailable;

    manage->person_user[Position_person].nums_book++;

    return SUCCESS;
}
static char *Display_status_of_book(Book_status status)
{
    switch(status)
    {
        case Available:
            return "Available";
        case Unavailable:
            return "Unavailable";
    }
}
/*Handle Fuction*/
void Add_that_book()
{
    printf("Add book:\n ");

    Fault_display = Can_add_book();
}
void Remove_that_book()
{
    printf("Remove book: \n");

    Fault_display = Can_remove_book();
}
void List_all_book()
{
    printf("List book:\n ");

    if (manage->Store_book == 0)
        Fault_display = Empty;
    for (int i = 0; i < manage->Store_book; i++)
    {
        printf("\n%02d\t %20s\t %20s\t %20s ", manage->Book_at_library[i].id, manage->Book_at_library[i].title, manage->Book_at_library[i].author, Display_status_of_book(manage->Book_at_library[i].status));
    }
}
void Add_user_for()
{
    printf("Add user: \n");

    Fault_display = Can_add_user();
}
void List_user_for()
{

    printf("List user : \n");
    if (manage->person_users == 0)
        Fault_display = Empty;
    for (int i = 0; i < manage->person_users; i++)
    {
        printf("\n%02d\t %20s\t", manage->person_user[i].id, manage->person_user[i].name);
    }
}

void Borrowed_that_book()
{
    printf("Borrowed book:\n  ");

    Fault_display = Can_borrow_book();
}
void Return_that_book()
{
    printf("Return book : \n");

    Fault_display = Can_return_book();
}
void List_borrow_that_book()
{
    printf("List_borrow book:\n ");

    for (int i = 0; i < manage->Store_book; i++)
    {
        if (manage->Book_at_library[i].status == Unavailable)
            printf("\n%02d\t %20s\t %20s\t %02s ", manage->Book_at_library[i].id, manage->Book_at_library[i].title, manage->Book_at_library[i].author, Display_status_of_book(manage->Book_at_library[i].status));
    }
}
void Exit_library()
{
    free(manage);

    printf("Close program \n Good bye !!");
}
void Display_all_users()
{
    printf("display user \n");
    for(int i=0; i< manage->person_users; i++)
    {
        printf("\n %d %s %d",manage->person_user[i].id,manage->person_user[i].name,manage->person_user[i].nums_book);
    }
}