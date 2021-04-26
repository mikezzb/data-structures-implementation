#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR -1

enum Type {
    EMPTY, ACTIVE, DELETED
};

typedef struct Entry {
    char *key;
    int val;
    enum Type type;
} Entry;

typedef struct HashMap {
    int size;
    int capacity;
    Entry *arr;
} HashMap;

void insert(HashMap *hm, char *key, int val);

HashMap *initHashMap(int capacity) {
    HashMap *hm = (HashMap *) malloc(sizeof(HashMap));
    hm->size = 0;
    hm->capacity = capacity;
    hm->arr = (Entry *) malloc(sizeof(Entry) * capacity);
    for (int i = 0; i < capacity; i++) {
        hm->arr[i].type = EMPTY;
    }
    return hm;
}

unsigned hash(char *key, int capacity, int probes) {
    unsigned hash_val = 0;
    while (*key != '\0') {
        hash_val += (hash_val << 5) + *key++;
    }
    return (hash_val % capacity + probes * probes) % capacity;
}

int find(HashMap *hm, char *key) {
    int probes = 0;
    unsigned hashKey = hash(key, hm->capacity, probes);
    while (hm->arr[hashKey].type == DELETED ||
           (hm->arr[hashKey].type == ACTIVE &&
            strcmp(hm->arr[hashKey].key, key) != 0)) {
        probes++;
        hashKey = hash(key, hm->capacity, probes);
    }
    if (hm->arr[hashKey].type == EMPTY || hm->arr[hashKey].type == DELETED) {
        return ERROR;
    }
    return (int) hashKey;
}

int hasKey(HashMap *hm, char *key) {
    return find(hm, key) != ERROR;
}

void freeHashMap(HashMap *hm) {
    free(hm->arr);
    free(hm);
}

void ExpandHashMap(HashMap *hm) {
    int oldCapacity = hm->capacity;
    Entry *oldArr = hm->arr;
    hm->size = 0;
    hm->capacity = hm->capacity * 2;
    hm->arr = (Entry *) malloc(sizeof(Entry) * hm->capacity);

    for (int i = 0; i < hm->capacity; i++)
        hm->arr[i].type = EMPTY;

    for (int i = 0; i < oldCapacity; i++) {
        if (oldArr[i].type == ACTIVE)
            insert(hm, oldArr[i].key, oldArr[i].val);
    }

    free(oldArr);
}

void insert(HashMap *hm, char *key, int val) {
    int probes = 0;
    unsigned hashKey = hash(key, hm->capacity, probes);
    while (hm->arr[hashKey].type == ACTIVE) {
        probes++;
        hashKey = hash(key, hm->capacity, probes);
    }
    hm->arr[hashKey].key = key;
    hm->arr[hashKey].type = ACTIVE;
    hm->arr[hashKey].val = val;

    hm->size++;

    if (hm->size * 2 >= hm->capacity)
        ExpandHashMap(hm);
}

void insertWithReplacement(HashMap *hm, char *key, int val) {
    int found = find(hm, key);
    if (found == ERROR) {
        insert(hm, key, val);
    } else {
        hm->arr[found].val = val;
        if (hm->size * 2 >= hm->capacity)
            ExpandHashMap(hm);
    }
}

void delete(HashMap *hm, char *key) {
    int hash = find(hm, key);
    if (hash != ERROR) {
        hm->arr[hash].type = DELETED;
    }
}

int main(void) {
    HashMap *hm = initHashMap(3); // 3 is to test expand heap
    insert(hm, "Hello", 1);
    insert(hm, "World", 1);
    insert(hm, "你好", 1);
    insert(hm, "世界", 1);
    if (hasKey(hm, "World"))
        puts("YES 1");
    if (!hasKey(hm, "???"))
        puts("YES 2");
    if (hasKey(hm, "你好"))
        puts("YES 3");
    delete(hm, "Hello");
    delete(hm, "世界");
    if (!hasKey(hm, "Hello"))
        puts("YES 4");
    if (hasKey(hm, "World"))
        puts("YES 5");
    freeHashMap(hm);
    return 0;
}
