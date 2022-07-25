#ifndef QUEUE_H
#define QUEUE_H

    typedef struct queue_s {
        void* i;
        struct queue_s* next;
    } queue;

    queue* queue_add(void* item, queue* head);
    queue* queue_pop(queue* head);

#endif