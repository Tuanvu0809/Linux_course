#include <stdio.h>
#include "libary.h"

int main()
{
    choice your_choice;
    Libary library;
    initlib(&library);
    printMenu();
    
    do{
        printf("Enter choice: ");
        scanf("%d",&your_choice);

        switch (your_choice)
        {
            case Menu:
                printMenu();
                break;
            case Exit:
                Exit_function();
                break;
            case Add_book:
                Add_book_function(&library);
                break;
            case Remove_book:
                Remove_book_function(&library);
                break;
            case List_book:
                List_book_function(&library);
                break;
            case Add_user: 
                Add_user_function(&library);
                break;    
            case Remove_user:
                Remove_user_function(&library);
                break;
            case List_User:
                List_user_function(&library); 
                break;
            case Borrowed_book: 
                Borrowed_book_function(&library);
                break;
            case Return_book:
                Remove_book_function(&library);
                break;
            case List_Borrow_book:
                List_borrow_book_function(&library);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        
        }

    }while(your_choice != Exit);

    return 0;
}