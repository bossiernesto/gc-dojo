//
// Created by ernesto on 4/11/15.
//

#include "markandsweep.h"
#include <stdexcept>

GCEnviroment::~GCEnviroment() {
    //Empty destructor
}

//Mark and sweep algorithms
void GCEnviroment::garbageCollect() {
    unsigned int objectsBeforeSweep = this->numObjects;
    this->markAll();
    this->sweep();
}

void GCEnviroment::markAll() {
    for (unsigned int i = 0; i < this->stackSize; i++) {
        this->mark(this->stack[i]);
    }
}

void GCEnviroment::mark(Object object) {
    if (!object or !this->isMarked(object))
        return;
    object->mark = marked;
    if (object->type == obj_tuple) {
        this->mark(object->left);
        this->mark(object->right);
    }
}

void GCEnviroment::sweep() {
    Object object = this->root;
    while (object) {
        if (this->isMarked(object)) {
            object->mark = unmarked; //unmark object
            object = object->next;
        } else {
            Object unreachedObject = object;
            object = object->next;
            delete unreachedObject;
            this->numObjects--;
        }
    }

}

bool GCEnviroment::isMarked(Object object) {
    return object->mark == marked;
}

//stack usage

void GCEnviroment::push(Object object) {
    this->checkStack();
    this->stack[this->stackSize++] = object;
    this->checkStack();
}

Object GCEnviroment::pop() {
    if (this->stackSize <= 0) {
        throw std::range_error("Stack size negative or zero");
    }
    return this->stack[this->stackSize--];
}

void GCEnviroment::checkStack() {
    if (this->stackSize >= STACK_MAX)
        throw std::domain_error("Maximun stack reached");
    return;
}

//Initialization of objects
Object GCEnviroment::newObject(ObjectType type) {
    if (this->numObjects == this->threshold) {
        this->garbageCollect();
    }

    Object newObject = new Object_str;
    newObject->type = type;
    newObject->mark = unmarked;
    newObject->next = this->root;
    this->root = newObject;
    //increase counter
    this->numObjects++;

    return newObject;
}


//push methods

void GCEnviroment::pushInt(int value) {
    Object newObject = this->newObject(obj_int);
    newObject->value = value;
    this->push(newObject);
}

Object GCEnviroment::pushTuple() {
    Object newObject = this->newObject(obj_tuple);
    newObject->left = this->pop();
    newObject->right = this->pop();
}

//Getters

unsigned int GCEnviroment::getStackSize() {
    return this->stackSize;
}

unsigned int GCEnviroment::getNumObjects() {
    return this->numObjects;
}