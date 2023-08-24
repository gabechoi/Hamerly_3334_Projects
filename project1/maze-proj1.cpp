/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: maze-proj1.cpp
 * Student name: Gabriel Choi
 * assignment: project 1
 * due date: February 3, 2023
 * version: 1.3
 *
 * This file contains the code for the Maze class.
 */

#include "maze-proj1.h"

/* Maze
 *  parameters: none
 *  return value: none
 *
 *  This is the constructor for the Maze class, initializing all values.
 */
Maze::Maze(){
    this->validLocationCount = 0;
    this->validLocations = NULL;
}

/* ~Maze
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the Maze class.
 */
Maze::~Maze(){
    delete[] this->validLocations;
    this->validLocations = NULL;
    this->validLocationCount = 0;
}

/* getStartLocation
 *  parameters: none
 *  return value: the starting location
 *
 *  This returns the starting location of the maze.
 */
Location Maze::getStartLocation() const{
    return this->startLocation;
}

/* isValidLocation
 *  parameters:
 *      loc: the Location that will be checked to see if its in the list of
 *           valid locations of the Maze
 *  return value: if loc is a valid location in the maze
 *
 *  This checks to see if loc a valid location of the maze.
 */
bool Maze::isValidLocation(const Location &loc) const {
    for(int i = 0; i < this->validLocationCount; ++i){
        if(loc == this->validLocations[i]){
            return true;
        }
    }
    return false;
}

/* isEndLocation
 *  parameters:
 *      loc: the Location object that will be checked if its end location
 *           is the same as this Location
 *  return value: if loc is the end location in the maze
 *
 *  This checks to see if loc is the end location of the maze.
 */
bool Maze::isEndLocation(const Location &loc) const {
    return loc == this->endLocation;
}

/* &operator>>
 *  parameters:
 *  is: a reference to an istream
 *  loc: the Maze object that will be put into the ostream
 *  return value: the istream with list of valid locations
 *
 *  This function provides a means of streaming a Maze object in.
 */
istream &operator>>(istream &is, Maze &m){
    delete[] m.validLocations;
    is >> m.validLocationCount;
    m.validLocations = new Location[m.validLocationCount];
    for(int i = 0; i < m.validLocationCount; ++i){

        is >> m.validLocations[i];
    }
    is >> m.startLocation >> m.endLocation;
    return is;
}
