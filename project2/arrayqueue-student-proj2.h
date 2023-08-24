/* CSI 3334
 * Project 2 --  Word Melt Shortest-Path Solver
 * Filename: arrayqueue-student-proj2.h
 * Student name: Gabriel Choi
 * assignment: project 2
 * due date: February 17, 2023
 * version: 1.9
 *
 * This file holds the code for ArrayQueue class.
 */

#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

/* ArrayQueue
 *  parameters: none
 *  return value: none
 *
 *  This is the constructor for the ArrayQueue class, initializing all values.
 */
template <class Base>
ArrayQueue<Base>::ArrayQueue(){
    this->length = 0;
    this->capacity = 5;
    this->front = 0;
    this->data = new Base[this->capacity];
}

/* ArrayQueue
 *  parameters:
 *      q: an ArrayQueue object that this ArrayQueue will copy
 *  return value: none
 *
 *  This is the copy constructor for the ArrayQueue class, initializing all
 *  values.
 */
template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q){
    this->front = 0;
    this->length = q.length;
    this->capacity = q.capacity;
    this->data = new Base[this->capacity];
    for(int i = 0; i < this->length; ++i){
        this->data[i] = q.data[(q.front + i) % this->capacity];
    }
}

/* ~ArrayQueue
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the ArrayQueue class, initializing all values.
 */
template <class Base>
ArrayQueue<Base>::~ArrayQueue(){
    delete[] this->data;
    this->length = 0;
    this->capacity = 0;
    this->front = 0;
}

/* add
 *  parameters:
 *      item: a value of Base type that will be added to the front of the
 *      queue.
 *  return value: none
 *
 *  This function adds a value of Base type to the front of the queue.
 */
template <class Base>
void ArrayQueue<Base>::add(const Base &item){
    if(this->length >= this->capacity){
        this->doubleCapacity();
    }
    this->data[(this->length + this->front) % this->capacity] = item;
    this->length++;
}

/* remove
 *  parameters: none
 *  return value: none
 *
 *  This function removes the front value from the queue.
 */
template <class Base>
void ArrayQueue<Base>::remove(){
    assert(this->length > 0);
    this->length--;
    //delete this->data[this->front];
    this->front = (this->front + 1) % this->capacity;

}

/* getFront
 *  parameters: none
 *  return value: the front value of the queue
 *
 *  This function returns the first value of the queue.
 */
template <class Base>
const Base &ArrayQueue<Base>::getFront() const{
    return this->data[this->front];
}

/* getLength
 *  parameters: none
 *  return value: the length of the queue
 *
 *  This function returns the length of the queue.
 */
template <class Base>
int ArrayQueue<Base>::getLength() const{
    return this->length;
}

/* operator=
 *  parameters:
 *      q: an ArrayQueue object that this ArrayQueue will be set to
 *  return value: none
 *
 *  This function creates a deep copy of q for this ArrayQueue.
 */
template <class Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q){
    if(this != &q){
        delete[] this->data;
        this->front = 0;
        this->length = q.length;
        this->capacity = q.capacity;
        this->data = new Base[this->capacity];
        for(int i = 0; i < this->length; ++i){
            this->data[i] = q.data[(q.front + i) % this->capacity];
        }
    }
    return *this;
}

/* doubleCapacity
 *  parameters: none
 *  return value: none
 *
 *  This function doubles the capacity of the queue if the current capacity
 *  is unable to hold all the values.
 */
template <class Base>
void ArrayQueue<Base>::doubleCapacity(){
    Base *temp = this->data;
    this->capacity *= 2;
    this->data = new Base[this->capacity];
    for(int i = 0; i < this->length; ++i){
        this->data[i] = temp[(this->front + i)% this->length];
    }
    delete[] temp;
    this->front = 0;
}

#endif
