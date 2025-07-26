#include <stdio.h>
#include "inc/Library.h"

ErrorCode Fault_display;

Choice_fuction action[] =
    {
        {Add_book, Add_that_book},
        {Exit, Exit_library},
        {Menu, print_menu},
        {Remove_book, Remove_that_book},
        {List_book, List_all_book},
        {Borrowed_book, Borrowed_that_book},
        {Add_user, Add_user_for},
        {List_User, List_user_for},
        {List_Borrow_book, List_borrow_that_book},
        {Return_book, Return_that_book},
};
void choose_fuction(Choice already_choice)
{
    for (int i = 0; i < (sizeof(action) / sizeof(action[0])); i++)
    {
        if (action[i].choose == already_choice)
        {
            action[i].Function_use();
            return;
        }
    }
}

int main()
{
    /*Initialize Library*/
    if (Init_library() == -1)
    {
        printf ("fail library\n");
        return -1 ;
    }
    print_menu();
    
    Choice Your_choice;
    do
    {
        Fault_display = SUCCESS;
        printf ("\n Enter Your Choice :");
        scanf("%d", &Your_choice);
        choose_fuction(Your_choice);
        printf ("\n %s", Fault(Fault_display));
    } while (Your_choice != Exit);


    return 0;
}