#include <stdio.h>
#include "libary.h"



int main()
{
    choice your_choice;
    Libary libary;
    initlib(&libary);
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
                Add_book_function(&libary);
                break;
            case Remove_book:
                Remove_book_function(&libary);
                break;
            case List_book:
                List_book_function(&libary);
                break;
            case Add_user: 
                Add_user_function(&libary);
                break;    
            case Remove_user:
                Remove_user_fucnction(&libary);
                break;
            case List_User:
                List_user_fucntion(&libary); 
                break;
            case Borrowed_book: 
                Borrowed_book_fucntion(&libary);
                break;
            case Return_book:
                Remove_book_function(&libary);
                break;
            case List_Borrow_book:
                List_borrow_book_fucntion(&libary);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        
        }

    }while(your_choice != Exit);


    




    return 0;

}