#include <stdio.h>
#include "inc/queue.h"
int main()
{
    printf("Array and pointer \n");

    queue_add_task("task 1");
    queue_add_task("task 2");
    queue_add_task("task 3");
    queue_add_task("task 4");

    print_task_queue();

    queue_get_next_task();
    queue_get_next_task();
    queue_get_next_task();

    print_task_queue();

    printf("end of program\n");
    return 0;
}