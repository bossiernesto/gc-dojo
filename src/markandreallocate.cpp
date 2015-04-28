//
// Created by ernesto on 4/27/15.
//
#ifndef GC_DOJO_MARKANDREALLOCATE_H_H
#define GC_DOJO_MARKANDREALLOCATE_H_H
#include <cstddef>
#include <stdexcept>

#include "markandreallocate.h"
#include "markandsweep.h"

GCEnviromentWithRealloc::~GCEnviromentWithRealloc() {
    //Empty destructor
}

void GCEnviromentWithRealloc::garbageCollect() {
    return this->expandHeap(0);
}

void GCEnviromentWithRealloc::expandHeap(size_t extraSize) {

    size_t newLocations = this->recalculateHeapLocations();

    this->heapSize =  newLocations * HEAP_EXTRAROOMFACTOR + extraSize;

    if (this->heapSize < HEAP_MIN_SIZE) this->heapSize = HEAP_MIN_SIZE;

    void * oldHeap = this->heap;
    this->heap = realloc(this->heap, this->heapSize);


}

CObject GCEnviromentWithRealloc::newObject(ObjectType type){
    if (this->nextChunk + sizeof(Object) > this->heap + HEAP_SIZE_STD) {
        this->garbageCollect();

        if (this->nextChunk + sizeof(Object) > this->heap + HEAP_SIZE_STD) {
            throw std::range_error("Out of memory");
        }

    }

    CObject object = (CObject)this->nextChunk;
    this->nextChunk += sizeof(CObject_str);

    object->type = type;
    object->addrDest = NULL;

    return object;
}