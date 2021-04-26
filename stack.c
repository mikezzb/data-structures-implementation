#include <stdio.h>
#include <stdlib.h>
#define ERROR -1

typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct stack {
    struct node* head;
} stack;
 
node* init_node(int val) {
    node* n = (node*)malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    return n;
}

stack* init_stack() {
    stack* s = (stack*)malloc(sizeof(stack));
    s->head = init_node(-1);
    return s;
}

void push(stack* s, int val) {
    node* n = init_node(val);
    n->next = s->head->next;
    s->head->next = n;
}

int is_empty(stack* s) {
    return s->head->next == NULL;
}

void pop(stack* s) {
    if(is_empty(s))
        return;
    node* n = s->head->next; // current first node (to be poped)
    s->head->next = s->head->next->next; // set the second last node to be the first
    free(n);
}

int top(stack* s) {
    if(is_empty(s))
        return ERROR;
    return s->head->next->val;
}

void clear_stack(stack* s) {
    node* n = s->head;
    while (n) { // if still have uncleared node
        node* next = n->next; // next node to be cleared
        free(n);
        n = next;
    }
    free(s);
}

void print_stack(stack* s) {
    node* n = s->head->next;
    while (n) {
        printf("%d ", n->val);
        n = n->next;
    }
}

int main(void) {
    stack *s = init_stack();
    push(s, 0);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    pop(s);
    print_stack(s);
    putchar('\n');
    printf("stack: %p with top value %d\n", s, top(s));
    clear_stack(s);
    return 0;
}
