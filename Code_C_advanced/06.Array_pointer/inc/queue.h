#ifndef QUEUE_H
#define QUEUE_H

typedef struct TaskNode{
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

int Task_queue_init(TaskNode_t **task);
void print_task_queue(TaskNode_t *task);
void queue_add_task(TaskNode_t **task,const char* description);
void queue_get_next_task(TaskNode_t **task);


#endif