//
// Created by ernesto on 4/27/15.
//

#include "markandsweep.h"
#include <stdlib.h>

#ifndef GC_DOJO_MARKANDREALLOCATE_H
#define GC_DOJO_MARKANDREALLOCATE_H

#endif //GC_DOJO_MARKANDREALLOCATE_H
#define HEAP_SIZE_STD ( 1024*1024) //1Mb
#define HEAP_MIN_SIZE 16*sizeof(CObject_str)
#define HEAP_EXTRAROOMFACTOR 2

struct CObject_str : public Object_str {
    void *addrDest;
    ObjectType type;
    unsigned int mark;
    CObject_str *next;
    union {
        int value;
        struct { //tuple case
            CObject_str *left, *right;
        };
    };
};
typedef CObject_str *CObject;

//TODO: decouple the allocator into a secondary object
class GCEnviromentWithRealloc : public GCEnviroment {
    typedef GCEnviroment super;

    GCEnviromentWithRealloc(CObject root, unsigned int stackSize, unsigned int numObjects, unsigned int capacity) :
            GCEnviroment(NULL, stackSize, numObjects, capacity) {
        this->root = root;
        this->heap = malloc(HEAP_MIN_SIZE);
        this->heapSize = HEAP_MIN_SIZE;
    };

    virtual ~GCEnviromentWithRealloc();

    void garbageCollect();

    size_t recalculateHeapLocations();

    void expandHeap(size_t extraSize);

    CObject newObject(ObjectType type);

private:
    //Heap attributes
    void *heap;
    void *nextChunk;
    size_t heapSize;

    CObject stack[STACK_MAX];
    CObject root;
    unsigned int stackSize;
    unsigned int numObjects;
    unsigned int threshold;

};

class MemAllocator {
    MemAllocator(size_t initialSize) {
        this->heap = malloc(initialSize);
        this->heapSize = initialSize;
        this->next = heap;
    }

    virtual ~MemAllocator();

    void incrementHeap(size_t increment);

    void shrinkHeap(size_t decrement);

private:
    void *heap;
    void *next;
    size_t heapSize;
};