#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../inc/queue.h"

int Task_queue_init(TaskNode_t **task)
{
    *task = malloc(sizeof(TaskNode_t));
    *task = NULL;
    if(*task != NULL)
    {
        return -1;
    }
    printf("init queue success\n");
    return 0;
}
void print_task_queue(TaskNode_t *task)
{
    printf("-------Print task----------\n");
    printf("Task remain: ");
    if(task == NULL)
    {
        printf("empty \n");
        return;
    }
    
    TaskNode_t *head;
    head = task;
     
    do {
        printf(" %s ->", head->task_description);
        head = (head->next);
    } while(head != NULL);

    printf("\n");
}

void queue_add_task(TaskNode_t **task,const char* description)
{
   
    TaskNode_t *newTask = malloc(sizeof(TaskNode_t));
    strcpy(newTask->task_description, description);
    newTask->next = NULL;

    if (*task == NULL) {
        *task = newTask;
        return;
    }

    TaskNode_t *head = *task;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = newTask;
   
}
void queue_get_next_task(TaskNode_t **task)
{
    TaskNode_t *handle;
    printf("handle task:");
    if(*task == NULL)
    {
        printf("-*-Empty task-*-\n");
        return;
    }
    handle = *task;
    printf("%s\n ", handle->task_description);
    *task = handle->next;
    
    free(handle);
}






