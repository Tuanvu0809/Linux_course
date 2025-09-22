#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/queue.h"

static TaskNode_t *task;

int Task_queue_init()
{
    task = malloc(sizeof(TaskNode_t));

    if(task == NULL)
    {
        return -1;
    }

    strcpy((task) -> task_description , "INIT QUEUE");
    (task) -> next = NULL;
    printf("init queue success\n");

   // queue_get_next_task();
    return 0;
}
void print_task_queue(void)
{
    if(task== NULL)
    {
        printf("fail \n");
        return;
    }
    
    TaskNode_t *head = malloc(sizeof(TaskNode_t));
    head = task;
     printf("Task remain\n");
    do {
        printf(" %s ->", head->task_description);
        head = (head->next);
    }while(head != NULL);
    printf("\n");

    //free(head);

}

void queue_add_task(const char* description)
{
    static int init = 0;
    if(task == NULL)
    {
        if(Task_queue_init()== -1)
            {
                printf("init fail");
            } 
    }
    TaskNode_t *newTask = malloc(sizeof(TaskNode_t));

    strcpy(newTask->task_description,description);
    newTask->next = NULL;

    TaskNode_t *head = malloc(sizeof(TaskNode_t));
    head = task;
    do {
       
        if(head->next != NULL){
            head = (head->next);
        }

    }while(head->next != NULL);

    head->next = newTask;
    if(init == 0)
    {
        init ++;
        queue_get_next_task();
    }

}
void queue_get_next_task(void)
{
    TaskNode_t *handle;
    handle = task;
    printf("handle task: %s\n ", handle->task_description);
    task = handle->next;
    free(handle);
}


