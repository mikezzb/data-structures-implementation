#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define ERROR -1

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
    h->arr[0] = INT_MAX;
    h->capacity = capacity;
    h->size = 0;
    return h;
}

void insertHeap(Heap *h, int val) {
    if (isFull(h)) {
        return;
    }

    int hole = ++h->size;
    for (; h->arr[hole / 2] < val; hole /= 2) {
        h->arr[hole] = h->arr[hole / 2];
    }
    h->arr[hole] = val;
}

void percolateDown(Heap *h, int hole) {
    int val = h->arr[h->size--];
    int child;
    for (; hole * 2 <= h->size; hole = child) {
        child = hole * 2;
        if (child != h->size && h->arr[child] < h->arr[child + 1])
            child++;
        if (h->arr[child] > val)
            h->arr[hole] = h->arr[child];
        else break;
    }
    h->arr[hole] = val;
}

void removeMax(Heap *h) {
    h->arr[1] = h->arr[h->size];
    percolateDown(h, 1);
}

int getMax(Heap *h) {
    if (h->size == 0) {
        puts("Empty heap, cannot get max");
        return ERROR;
    }
    return h->arr[1];
}

void freeHeap(Heap *h) {
    free(h->arr);
    free(h);
}
