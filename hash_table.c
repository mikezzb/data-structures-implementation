#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define ERROR -1

enum Type { EMPTY, ACTIVE, DELETED };

typedef struct Entry {
    int key;
    int val;
    enum Type type;
} Entry;

typedef struct HashMap {
    int size;
    int capacity;
    Entry* arr;
} HashMap;

void insert(HashMap* hm, int key, int val);

HashMap* initHashMap(int capacity){
    HashMap *hm = (HashMap*) malloc(sizeof(HashMap));
    hm->size = 0;
    hm->capacity = capacity;
    hm->arr = (Entry*)malloc(sizeof(Entry) * capacity);
    for(int i=0; i<capacity; i++){
        hm->arr[i].type = EMPTY;
    }
    return hm;
}

int hash(int key, int capacity, int probes){
    if(key == INT_MIN){
        return 0;
    }
    return (abs(key) % capacity + probes * probes) % capacity;
}

int find(HashMap* hm, int key){
    int probes = 0;
    int hashKey = hash(key, hm->capacity, probes);
    while (hm->arr[hashKey].type == DELETED || (hm->arr[hashKey].type == ACTIVE && hm->arr[hashKey].key != key)){
        probes++;
        hashKey = hash(key, hm->capacity, probes);
    }
    if (hm->arr[hashKey].type == EMPTY || hm->arr[hashKey].type == DELETED){
        return ERROR;
    }
    return hashKey;
}

int hasKey(HashMap* hm, int key){
    return find(hm, key) != ERROR;
}

void freeHashMap(HashMap *hm){
    free(hm->arr);
    free(hm);
}

void ExpandHashMap(HashMap *hm){
    int oldCapacity = hm->capacity;
    Entry* oldArr = hm->arr;
    hm->size = 0;
    hm->capacity = hm->capacity * 2;
    hm->arr = (Entry*)malloc(sizeof(Entry) * hm->capacity);

    for(int i=0; i<hm->capacity; i++)
        hm->arr[i].type = EMPTY;

    for(int i=0; i<oldCapacity; i++){
        if(oldArr[i].type == ACTIVE)
            insert(hm, oldArr[i].key, oldArr[i].val);
    }

    free(oldArr);
}

void insert(HashMap* hm, int key, int val){
    int probes = 0;
    int hashKey = hash(key, hm->capacity, probes);
    while (hm->arr[hashKey].type == ACTIVE){
        probes++;
        hashKey = hash(key, hm->capacity, probes);
    }
    hm->arr[hashKey].key = key;
    hm->arr[hashKey].type = ACTIVE;
    hm->arr[hashKey].val = val;

    hm->size++;

    if(hm->size * 2 >= hm->capacity)
        ExpandHashMap(hm);
}

void insertWithReplacement(HashMap* hm, int key, int val){
    int found = find(hm, key);
    if(found == ERROR){
        insert(hm, key, val);
    } else {
        hm->arr[found].val = val;
        if(hm->size * 2 >= hm->capacity)
            ExpandHashMap(hm);
    }
}

void delete(HashMap *hm, int key){
    int hash = find(hm, key);
    if(hash != ERROR){
        hm->arr[hash].type = DELETED;
    }
}

int main(void){
	HashMap* hs = initHashMap(3); // 3 is to test expand heap
	insert(hs, 10, 1);
	insert(hs, 123, 1);
	insert(hs, 345, 1);
	insert(hs, 64, 1);
	insert(hs, 8127, 1);
	insert(hs, 234, 1);
	insert(hs, 678, 1);
	if (hasKey(hs, 64))
	    puts("YES 1");
	if (!hasKey(hs, 100))
	    puts("YES 2");
	if (hasKey(hs, 678))
	    puts("YES 3");
	delete(hs, 123);
	delete(hs, 8127);
	delete(hs, 678);
	if (!hasKey(hs, 678))
	    puts("YES 4");
	if (hasKey(hs, 10))
	    puts("YES 5");
	return 0;
}
