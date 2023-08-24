/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: location-proj1.cpp
 * Student name: Gabriel Choi
 * assignment: project 1
 * due date: February 3, 2023
 * version: 1.3
 *
 * This file contains the code for the Location class.
 */

#include "location-proj1.h"

const int MAX = 10000;
const int MIN = 10000;

/* Location
 *  parameters: none
 *  return value: none
 *
 *  This is the constructor for the Location class, initializing all values.
 */
Location::Location(){
    this->row = 0;
    this->col = 0;
    this->nextDirection = RIGHT;
}

/* iterationBegin
 *  parameters: none
 *  return value: none
 *
 *  This function initializes the iteration capability of the Location object.
 */
void Location::iterationBegin(){
    this->nextDirection = RIGHT;
}

/* iterationCurrent
 *  parameters: none
 *  return value: the neighbor location
 *
 *  This function creates a copy of the current Location object, modifies the
 *  copy so that it represents a different location, and it returns the
 *  neighbor it created.
 */
Location Location::iterationCurrent() const{
    Location neighbor;
    neighbor.row = this->row;
    neighbor.col = this->col;
    if(this->nextDirection == RIGHT){
        neighbor.col++;
    }
    else if(this->nextDirection == DOWN){
        neighbor.row++;
    }
    else if(this->nextDirection == LEFT){
        neighbor.col--;
    }
    else{
        neighbor.row--;
    }
    return neighbor;
}

/* iterationAdvance
 *  parameters: none
 *  return value: none
 *
 *  This function moves the iteration forward so the next neighbor can be
 *  called.
 */
void Location::iterationAdvance() {
    this->nextDirection++;
}

/* iterationDone
 *  parameters: none
 *  return value: if the all the neighbors have been checked
 *
 *  This function returns true when the all the neighbors of a Location have
 *  been iterated over.
 */
bool Location::iterationDone() const {
    return this->nextDirection == DONE;
}

/* operator==
 *  parameters:
 *      loc: the location object that is being compared to this location
 *  return value: if the two Location objects are at the same place in the map
 *  despite its nextDirection value.
 *
 *  This function checks to see if the two Location objects have the same row
 *  and col.
 */
bool Location::operator==(const Location &loc) const{
    return this->row == loc.row && this->col == loc.col;
}

/* &operator<<
 *  parameters:
 *  os: a reference to an ostream
 *  loc: the location object that will into the ostream
 *  return value: the ostream with the row and col
 *
 *  This function provide a means of streaming a Location object out.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.row << ' ' << loc.col;
    return os;
}

/* &operator>>
 *  parameters:
 *  is: a reference to an istream
 *  loc: the Location object that will be streamed into this Location
 *  return value: the istream with the row and col
 *
 *  This function provide a means of streaming a Location object in.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.row >> loc.col;
    return is;
}
