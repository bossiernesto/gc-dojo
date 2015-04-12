//
// Created by ernesto on 4/11/15.
//

#ifndef GC_DOJO_MARKANDSWEEP_H
#define GC_DOJO_MARKANDSWEEP_H
#include <cstddef>

#define STACK_MAX 512

enum ObjectType {
    obj_int,
    obj_tuple
};

enum MarkStatus {
    unmarked,
    marked
};

struct Object_str {
    ObjectType type;
    unsigned int mark;
    Object_str* next;
    union {
        int value;
        struct { //tuple case
            Object_str *left, *right;
        };
    };
};
typedef Object_str* Object;

class GCEnviroment {
public:
    GCEnviroment(Object root, unsigned int stackSize, unsigned int numObjects, unsigned int capacity):
        root(root),
        stackSize(stackSize),
        numObjects(numObjects),
        threshold(capacity){ };
    virtual ~GCEnviroment();
    void garbageCollect();
    Object newObject(ObjectType type);
    void pushInt(int value);
    Object pushTuple();
    Object pop();
    void markAll();
    void sweep();
    bool isMarked(Object object);
    unsigned int getStackSize();
    unsigned int getNumObjects();
private:
    void checkStack();
    void push(Object object);
    void mark(Object object);
    Object stack[STACK_MAX];
    Object root;
    unsigned int stackSize;
    unsigned int numObjects;
    unsigned int threshold;
};

#endif //GC_DOJO_MARKANDSWEEP_H
