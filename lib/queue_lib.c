#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue_lib.h"

queue* queue_add(void* item, queue* head){
    queue* new = malloc(sizeof(queue));
    queue* out = head;
    new->i = item;
    new->next = NULL;
    
    if(head == NULL){
        return new;
    }

    while(head->next != NULL){
        head = head->next;
    }

    head->next = new;

    return out;
}

queue* queue_pop(queue* head){
    queue* out = head->next;
    free(head);
    return out;
}