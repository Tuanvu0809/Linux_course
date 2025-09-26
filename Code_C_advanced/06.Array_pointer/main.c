#include <stdio.h>
#include "inc/queue.h"

TaskNode_t *task;

int main()
{
    printf("Array and pointer \n");

    if(Task_queue_init(&task)== -1)
    {
        printf("init fail");
    } 

    print_task_queue(task);

    queue_add_task(&task, "task 1");
    queue_add_task(&task,"task 2");
    queue_add_task(&task,"task 3");
    queue_add_task(&task,"task 4");

    print_task_queue(task);

    queue_get_next_task(&task);
    queue_get_next_task(&task);
    queue_get_next_task(&task);

    print_task_queue(task);
    queue_get_next_task(&task);

    print_task_queue(task);
    queue_get_next_task(&task);
    printf("end of program\n");
    return 0;
}