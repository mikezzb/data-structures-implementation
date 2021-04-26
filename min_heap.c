#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Heap {
    int capacity;
    int size;
    int *arr;
} Heap;

int isEmpty(Heap *h) {
    return h->size == 0;
}

int isFull(Heap *h) {
    return h->size == h->capacity;
}

Heap *initHeap(int capacity) {
    Heap *h = (Heap *) malloc(sizeof(Heap));
    h->arr = (int *) malloc(sizeof(int) * (capacity + 1));
    h->arr[0] = INT_MIN;
    h->capacity = capacity;
    h->size = 0;
    return h;
}

void freeHeap(Heap *h) {
    free(h->arr);
    free(h);
}

void insertHeap(Heap *h, int val) {
    if (isFull(h)) {
        printf("Heap already full\n");
        return;
    }
    h->size++;
    int hole = h->size;
    for (; hole > 1 && h->arr[hole / 2] > val; hole /= 2) {
        h->arr[hole] = h->arr[hole / 2];
    }
    h->arr[hole] = val;
}

void percolateDown(Heap *h, int hole) {
    int val = h->arr[hole];
    int child;
    for (; hole * 2 <= h->size; hole = child) {
        child = hole * 2;
        if (child != h->size && h->arr[child + 1] < h->arr[child])
            child++;
        if (h->arr[child] < val)
            h->arr[hole] = h->arr[child];
        else break;
    }
    h->arr[hole] = val;
}

void removeMin(Heap *h) {
    h->arr[1] = h->arr[h->size--];
    percolateDown(h, 1);
}

int getMin(Heap *h) {
    return h->arr[1];
}
