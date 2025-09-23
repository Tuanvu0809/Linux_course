#ifndef QUEUE_H
#define QUEUE_H

typedef struct TaskNode{
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

int Task_queue_init();
void print_task_queue(void);
void queue_add_task(const char* description);
void queue_get_next_task(void);


#endif