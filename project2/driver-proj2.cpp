/* CSI 3334
 * Project 2 --  Word Melt Shortest-Path Solver
 * Filename: driver-proj2.cpp
 * Student name: Gabriel Choi
 * assignment: project 2
 * due date: February 17, 2023
 * version: 1.9
 *
 * This file finds the shortest path from one word to another.
 */

#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-student-proj2.h"
#include <map>
#include <stack>

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function searches through a maze, provided by the user, to find a path
 *  from the beginning word to the end word. Starting from the beginning, the
 *  function checks the neighbor words by changing a letter, inserting a
 *  letter, and deleting a letter. During this, the predecessor word is kept
 *  through a map. When all the neighbors have been added, the function checks
 *  to see if a solution has been found. If a solution has been found, the
 *  valid locations in the map that are found to be on the shortest path are
 *  added to another map for output. If a solution has not been found, then no
 *  solution is outputted.
 */

int main(int argc, char **argv){
    Location m, endLocation;
    map<Location, Location> locMap, pathMap;
    map<Location, Location>::iterator mapItr;
    ArrayQueue<Location> locationQueue;
    Maze userMaze;
    bool solutionFound = false;
    stack<Location>sPath;

    cin >> userMaze;

    m = userMaze.getStartLocation();
    locationQueue.add(m);
    locMap[m] = m;

    if(userMaze.isEndLocation(locationQueue.getFront())){
        solutionFound = true;
        endLocation = m;
    }

    while(locationQueue.getLength() > 0 && !solutionFound) {
        m = locationQueue.getFront();
        m.iterationBegin();
        locationQueue.remove();
        while (!m.iterationDone()) {
            Location neighbor = m.iterationCurrent();

            if(userMaze.isEndLocation(neighbor)){
                locMap[neighbor] = m;
                endLocation = neighbor;
                solutionFound = true;
            }
            else if (userMaze.isValidLocation(neighbor)) {
                if (locMap.find(neighbor) == locMap.end()) {
                    locMap[neighbor] = m;
                    locationQueue.add(neighbor);
                }
            }
            m.iterationAdvance();
        }
    }

    if(solutionFound){
        cout << "Solution found" << endl;

        while(!(endLocation == userMaze.getStartLocation())){
            sPath.push(endLocation);
            endLocation = locMap[endLocation];
        }
        sPath.push(userMaze.getStartLocation());

        while(!sPath.empty()){
            cout << sPath.top() << endl;
            sPath.pop();
        }
    }
    else{
        cout << "No solution" << endl;
    }

    return 0;
}