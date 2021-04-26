#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

typedef struct queue_node {
    int val;
    struct queue_node *next;
} queue_node;

typedef struct queue {
    queue_node *head;
    queue_node *rear;
} queue;

queue *init_queue() {
    queue *q = (queue *) malloc(sizeof(queue));
    q->head = (queue_node *) malloc(sizeof(queue_node));
    q->rear = q->head;
    return q;
}

void push(queue *q, int val) {
    queue_node *n = (queue_node *) malloc(sizeof(queue_node));
    n->val = val;
    n->next = NULL;

    q->rear->next = n;
    q->rear = n;
}

int isEmpty(queue *q) {
    if (q->head == q->rear)
        return 1;
    return 0;
}

int front(queue *q) {
    if (isEmpty(q)) {
        puts("Empty Queue, cannot front\n");
        return ERROR;
    }
    return q->head->next->val;
}

void pop(queue *q) {
    if (isEmpty(q)) {
        puts("Empty Queue,  cannot pop\n");
        return;
    }

    if (q->head->next == q->rear)
        q->rear = q->head;

    queue_node *temp = q->head->next;
    q->head->next = temp->next;
    free(temp);
}

void free_queue(queue *q) {
    queue_node *n = q->head;
    while (n) {
        queue_node *temp = n->next;
        free(n);
        n = temp;
    }
    free(q);
}

int main(void) {
    return 0;
}
