/* CSI 3334
 * Project 6 -- Network Broadcasting
 * Filename: arrayheap-student-proj6.h
 * Student name: Gabriel Choi
 * assignment: project 6
 * due date: May 5, 2023
 * version: 1.0
 *
 * This file holds the code for the Array Heap class.
 */

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

#ifndef PROJECT_6_ARRAYHEAP_STUDENT_PROJ6_H
#define PROJECT_6_ARRAYHEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>
using namespace std;

/* ArrayHeap Constructor
 * parameters: none
 * return: none
 *
 * Initializes data members with default values and
 * allocates memory for data, dataToHeap and heapAndFreeStack arrays.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for(int i = 0; i < capacity; ++i){
        heapAndFreeStack[i] = i;
    }

}

/* ArrayHeap Copy Constructor
 * parameters: h - ArrayHeap object to be copied
 * return: none
 *
 * Initializes data members with parameter's values and
 * allocates memory for data, dataToHeap and heapAndFreeStack arrays.
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    this->capacity = h.capacity;
    this->numItems = h.numItems;

    data = new T[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];

    for(int i = 0; i < this->capacity; ++i) {
        this->data[i] = h.data[i];
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
        this->dataToHeap[i] = h.dataToHeap[i];
    }

}

/* ArrayHeap Destructor
 * parameters: none
 * return: none
 *
 * Resets data members to default values and
 * deallocates memory.
 */
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    numItems = 0;
    capacity = 10;
    delete[] data;
    delete[] heapAndFreeStack;
    delete[] dataToHeap;
}

/* = Operator
 * parameters: ah - ArrayHeap object to be copied
 * return: none
 *
 * Sets data members with parameter's values and
 * and copies its data, dataToHeap and heapAndFreeStack arrays.
 */
template <typename T>
ArrayHeap<T> const & ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if(&ah != this){
        delete[] this->data;
        delete[] this->heapAndFreeStack;
        delete[] this->dataToHeap;

        this->capacity = ah.capacity;
        this->numItems = ah.numItems;

        this->data = new T[capacity];
        this->heapAndFreeStack = new int[capacity];
        this->dataToHeap = new int[capacity];

        for(int i = 0; i < capacity; ++i){
            this->data[i] = ah.data[i];
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            this->dataToHeap[i] = ah.dataToHeap[i];
        }
    }
    return *this;
}

/* Insert
 * parameters: item - Value to be inserted
 * return:  The "key" which is the index where the
 *          new item is inserted into the data array.
 *
 * Doubles capacity if necessary, then inserts the
 * value at the end and bubbles it up to the correct
 * place.
 */
template <typename T>
int ArrayHeap<T>::insert(T const &item){
    if(capacity <= numItems){
        doubleCapacity();
    }

    int ndx = heapAndFreeStack[numItems];

    data[heapAndFreeStack[numItems]] = item;
    dataToHeap[heapAndFreeStack[numItems]] = numItems;
    bubbleUp(numItems);
    numItems++;

    return ndx;
}

/* removeMinItem
 * parameters: none
 * return: none
 *
 * Swaps the highest priority item with the end of the array
 * and bubbles that value down.
 */
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    swap(dataToHeap[heapAndFreeStack[0]], dataToHeap[heapAndFreeStack[numItems - 1]]);
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems - 1]);
    numItems--;
    bubbleDown(0);
}

/* getMinItem
 * parameters: none
 * return: Highest priority item
 *
 * returns the highest priority item
 */
template <typename T>
T const & ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

/* getNumItems
 * parameters: none
 * return: Total number of items
 *
 * returns the total number items in the heap
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

/* isOnHeap
 * parameters: key - index of object to check
 * return: none
 *
 * Checks if key is a valid location on the heap
 */
template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const{
    if (0 <= key && key < this->capacity) {
        if (0 <= dataToHeap[key] && dataToHeap[key] < numItems) {
            if (heapAndFreeStack[dataToHeap[key]] == key) {
                return true;
            }
        }
    }
    return false;
}

/* changeItemAtKey
 * parameters: key - index of object to change
 *             newItem - item to replace old item
 * return: none
 *
 * Checks if key is a valid location on the heap. If valid,
 * replaces the item then shifts item to correct location on
 * the heap.
 */
template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem){
    if(isOnHeap(key)){
        data[key] = newItem;
        bubbleUp(dataToHeap[key]);
        bubbleDown(dataToHeap[key]);
    }
}

/* doubleCapacity
 * parameters: none
 * return: none
 *
 * Doubles the capacity of the heap
 */
template <typename T>
void ArrayHeap<T>::doubleCapacity(){

    T* dataTemp = new T[capacity * 2];
    int* heapTemp = new int[capacity * 2];
    int* dataToHTemp = new int[capacity * 2];


    for(int i = 0; i < capacity; ++i){
        dataTemp[i] = data[i];
        heapTemp[i] = heapAndFreeStack[i];
        dataToHTemp[i] = dataToHeap[i];
    }
    for(int i = capacity; i < capacity * 2; ++i){
        heapTemp[i] = i;
        //dataToHeap[i] = i;
    }

    capacity *= 2;
    delete[] data;
    delete[] heapAndFreeStack;
    delete[] dataToHeap;
    data = dataTemp;
    heapAndFreeStack = heapTemp;
    dataToHeap = dataToHTemp;
}

/* bubbleUp
 * parameters: ndx - index of object to bubble up
 * return: none
 *
 * Bubble up an item to its correct place in the heap.
 */
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    if(ndx <= 0) {
        return;
    }
    int parent = (ndx - 1)/2;

    if (data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
        swap(dataToHeap[heapAndFreeStack[ndx]], dataToHeap[heapAndFreeStack[parent]]);
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);

        bubbleUp(parent);
    }
}

/* bubbleDown
 * parameters: ndx - index of object to bubble down
 * return: none
 *
 * Bubble down an item to its correct place in the heap.
 */
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1 = (2 * ndx) + 1,
            child2 = (2 * ndx) + 2;

    if(child1 < numItems) {
        int lesserChild = child1;
        if ((child2 < numItems)
            && (data[heapAndFreeStack[child2]] < data[heapAndFreeStack[child1]])){
            lesserChild = child2;
        }
        if (data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]){
            swap(dataToHeap[heapAndFreeStack[ndx]], dataToHeap[heapAndFreeStack[lesserChild]]);
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

#endif //PROJECT_6_ARRAYHEAP_STUDENT_PROJ6_H