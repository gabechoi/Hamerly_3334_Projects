/* CSI 3334
 * Project 2 --  Word Melt Shortest-Path Solver
 * Filename: maze-proj2.cpp
 * Student name: Gabriel Choi
 * assignment: project 2
 * due date: February 17, 2023
 * version: 1.9
 *
 * This file holds the code for Maze class.
 */

#include "maze-proj2.h"
#include <cassert>

/* Maze
 *  parameters: none
 *  return value: none
 *
 *  This is the constructor for the Maze class, initializing all values it can.
 */
Maze::Maze(){
    this->validLocations = set<Location>();
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
    return this->validLocations.find(loc) != this->validLocations.end();
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
 *  is: the istream that will stream in the maze to this
 *  loc: the Maze object that will be put into the ostream
 *  return value: the istream with list of valid locations
 *
 *  This function provides a means of streaming a Maze object in.
 */
istream &operator>>(istream &is, Maze &m){
    int size;
    //assert(size >= 0 && size <= 20000);
    Location buffer;
    m.validLocations.clear();
    is >> size;
    for(int i = 0; i < size; ++i){
        is >> buffer;
        m.validLocations.insert(buffer);
    }
    is >> m.startLocation >> m.endLocation;
    return is;
}
