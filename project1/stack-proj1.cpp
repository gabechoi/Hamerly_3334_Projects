/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: stack-proj1.cpp
 * Student name: Gabriel Choi
 * assignment: project 1
 * due date: February 3, 2023
 * version: 1.3
 *
 * This file contains the code for the Maze class.
 */

#include "stack-proj1.h"

/* LocationStack
 *  parameters: none
 *  return value: none
 *
 *  This is the constructor for the LocationStack class, initializing all values.
 */
LocationStack::LocationStack() {
    this->top = NULL;
}

/* ~LocationStack
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the LocationStack class.
 */
LocationStack::~LocationStack() {
    delete this->top;
    this->top = NULL;
}

/* push
 *  parameters:
 *      loc: the Location that will be pushed into the stack
 *  return value: none
 *
 *  This pushes a Location to the front of the LocationStack.
 */
void LocationStack::push(const Location &loc){
    //LocationStackNode *temp = new LocationStackNode(loc, this->top);
    //this->top = temp;
    this->top = new LocationStackNode(loc, this->top);

}

/* push
 *  parameters: none
 *  return value: none
 *
 *  This pops a Location from the front of the LocationStack.
 */
void LocationStack::pop(){
    assert(!isEmpty());
    LocationStackNode *temp = this->top;
    this->top = this->top->getNextNode();
    temp->setNextNode(NULL);
    delete temp;
}

/* getTop
 *  parameters: none
 *  return value: the first Location in the stack
 *
 *  This returns the first Location in the stack.
 */
const Location& LocationStack::getTop() const{
    return this->top->getLocation();
}

/* push
 *  parameters: none
 *  return value: if the LocationStack is empty
 *
 *  Checks if the LocationStack is empty.
 */
bool LocationStack::isEmpty() const {
    return this->top == NULL;
}

/* isOn
 *  parameters:
 *      loc: the Location that will be checked if it is in the stack
 *  return value: if loc is in the LocationStack
 *
 *  This returns true if the given Location is on the stack, otherwise returns
 *  false.
 */
bool LocationStack::isOn(const Location &loc) const{
    LocationStackNode *temp = this->top;
    while(temp != NULL){
        if(temp->getLocation() == loc){
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

/* &operator<<
 *  parameters:
 *      os: a reference to an ostream
 *      s: the LocationStack object that will be streamed into this
 *         LocationStack
 *  return value: the ostream of all the Locations from bottom to top
 *
 *  This streams out the stack from bottom to top. The first pass will
 *  traverse the stack to top->bottom, reversing the links of the nodes as it
 *  goes. The second pass will traverse from bottom->top, printing each
 *  Location as it is visited, and undoing the reversing of the node links.
 */
ostream &operator<<(ostream &os, const LocationStack &s){
    LocationStackNode *curr = s.top;
    LocationStackNode *next = NULL;
    LocationStackNode *prev = NULL;
    while(curr != NULL){
        next = curr->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }
    curr = prev;
    next = prev = NULL;
    while(curr != NULL){
        os << curr->getLocation() << endl;
        next = curr->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }
    curr = prev;
    return os;
}

/* LocationStackNode
 *  parameters:
 *      loc: the Location object that this LocationStackNode will point to
 *      next: a pointer that points to the next node in the list
 *  return value: none
 *
 *  This is the constructor for the LocationStackNode class, initializing all values.
 */
LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next) {
    this->location = loc;
    this->nextNode = next;
}

/* ~LocationStackNode
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the LocationStackNode class.
 */
LocationStackNode::~LocationStackNode() {
    delete this->nextNode;
}

/* getLocation
 *  parameters: none
 *  return value: returns the location of the LocationStackNode
 *
 *  This function returns the location of the LocationStackNode.
 */
const Location& LocationStackNode::getLocation() const{
    return this->location;
}

/* getNextNode
 *  parameters: none
 *  return value: returns the nextNode of the LocationStackNode
 *
 *  This function returns the nextNode of the LocationStackNode.
 */
LocationStackNode* LocationStackNode::getNextNode() const {
    return this->nextNode;
}

/* setNextNode
 *  parameters:
 *      next: the pointer that will point to the next node in the list
 *  return value: none
 *
 *  This function sets the nextNode of the LocationStackNode.
 */
void LocationStackNode::setNextNode(LocationStackNode *next) {
    this->nextNode = next;
}

