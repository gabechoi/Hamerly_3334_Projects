/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: arrayheap-student-proj5.h
 * Student name: Gabriel Choi
 * assignment: project 5
 * due date: April 14, 2023
 * version: 1.0
 *
 * This file holds the code for the ArrayHeap class.
 */

#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include "process-proj5.h"
#include <algorithm>

using namespace std;

/* ArrayHeap
 *  parameters: none
 *  return value: none
 *
 *  This is the default constructor for the ArrayHeap class.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    this->capacity = 5;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    for(int i = 0; i < this->capacity; ++i){
        this->heapAndFreeStack[i] = i;
    }
    this->numItems = 0;
}

/* ArrayHeap
 *  parameters:
 *      h: the array heap that this will be copying
 *  return value: none
 *
 *  This is the copy constructor for the ArrayHeap class.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    this->capacity = h.capacity;
    this->numItems = h.numItems;
    this->data = new T[h.capacity];
    this->heapAndFreeStack = new int[h.capacity];

    for(int i = 0; i < this->capacity; ++i){
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
        this->data[i] = h.data[i];
    }
}

/* ~ArrayHeap
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the ArrayHeap class.
 */
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    delete[] this->data;
    delete[] this->heapAndFreeStack;
    this->numItems = 0;
    this->capacity = 5;
}

/* getItem
 *  parameters: none
 *  return value: the minimum priority item in the heap
 *
 *  This function returns the minimum priority item in the heap.
 */
template <typename T>
T const &ArrayHeap<T>::getMinItem() const{
    return this->data[this->heapAndFreeStack[0]];
}

/* getNumItems
 *  parameters: none
 *  return value: the number of items in the heap
 *
 *  This function returns the number of items in the heap.
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return this->numItems;
}

/* bubbleUp
 *  parameters:
 *      ndx: the index at which the function will start from
 *  return value: none
 *
 *  This function fixes the priority of the heap by swapping the child element
 *  with its parent if the child is smaller.
 */
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    if(ndx <= 0) {
        return;
    }
    int parent = (ndx - 1) / 2;
    if (data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
        swap(this->heapAndFreeStack[parent], this->heapAndFreeStack[ndx]);
        this->bubbleUp(parent);
    }
}

/* bubbleDown
 *  parameters:
 *      ndx: the index at which the function will start from
 *  return value: none
 *
 *  This function fixes the priority of the heap by swapping the parent element
 *  with its smaller child if the parent is larger.
 */
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1 = (2 * ndx) + 1;
    int child2 = (2 * ndx) + 2;

    if (child1 < this->numItems) {
        int lesserChild = child1;
        if ((data[heapAndFreeStack[child2]] < data[heapAndFreeStack[child1]]) &&
            (child2 < this->numItems)) {
            lesserChild = child2;
        }
        if(data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]){
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            this->bubbleDown(lesserChild);
        }
    }
}

/* operator=
 *  parameters:
 *      ah: the arrayHeap that this heap will be set to
 *  return value: the address of this heap
 *
 *  This function sets this heap to that heap.
 */
template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(this != &ah){
        delete[] this->data;
        delete[] this->heapAndFreeStack;
        this->capacity = ah.capacity;
        this->numItems = ah.numItems;
        this->data = new T[this->capacity];
        this->heapAndFreeStack = new int[this->capacity];

        for(int i = 0; i < this->capacity; ++i){
            this->data[i] = ah.data[i];
        }
        for(int i = 0; i < this->capacity; ++i){
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        }
    }
    return *this;
}

/* insert
 *  parameters:
 *      item: the element that will be inserted
 *  return value: none
 *
 *  This function inserts an item into the heap and fixes its priority.
 */
template <typename T>
void ArrayHeap<T>::insert(T const &item){
    if(this->numItems == this->capacity){
        this->doubleCapacity();
    }
    this->data[this->heapAndFreeStack[this->numItems]] = item;
    //this->heapAndFreeStack[this->numItems] = this->numItems;
    this->bubbleUp(this->numItems);
    //this->bubbleUp(this->heapAndFreeStack[this->numItems]);
    this->numItems++;
}

/* removeMinItem
 *  parameters: none
 *  return value: none
 *
 *  This function removes the min item from the heap and fixes its priority.
 */
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    int min = 0;
    this->numItems--;
    swap(this->heapAndFreeStack[min], this->heapAndFreeStack[this->numItems]);
    this->bubbleDown(min);
}

/* doubleCapacity
 *  parameters: none
 *  return value: none
 *
 *  This function doubles the capacity of the heap.
 */
template <typename T>
void ArrayHeap<T>::doubleCapacity(){
    T *tempData = new T[this->capacity*2];
    int *tempHeap = new int[this->capacity*2];
    for(int i = 0; i < this->capacity; ++i){
        tempData[i] = this->data[i];
        tempHeap[i] = this->heapAndFreeStack[i];
    }
    for(int i = this->capacity; i < this->capacity*2; ++i){
        tempHeap[i] = i;
    }
    this->capacity *= 2;
    delete[] this->data;
    delete[] this->heapAndFreeStack;
    this->data = tempData;
    this->heapAndFreeStack = tempHeap;
}

#endif
