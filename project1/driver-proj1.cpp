/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: driver-proj1.cpp
 * Student name: Gabriel Choi
 * assignment: project 1
 * due date: February 3, 2023
 * version: 1.0
 *
 * This file currently contains the code to test the driver with self-made
 * test cases.
 */

#include "maze-proj1.h"
#include "stack-proj1.h"
#include <sstream>

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function searches through a maze, provided by the user, to find a path
 *  from the beginning to the end. Starting from the beginning, the function
 *  checks the location's neighbors from right, down, left, and up for valid
 *  locations. It runs a loop to continually look for valid locations, pushing
 *  valid locations on to a stack to keep a record. Then at the end it outputs
 *  to the screen the path it followed. If there is no valid path, it outputs no
 *  solution.
 */

int main(int argc, char **argv) {
    Maze userMaze;
    Location m;
    Location neighbor;
    LocationStack locationStack;
    bool flag = false;

    cin >> userMaze;

    m = userMaze.getStartLocation();
    m.iterationBegin();
    locationStack.push(m);

    while(!flag && !userMaze.isEndLocation(locationStack.getTop())){
        m = locationStack.getTop();
        locationStack.pop();
        if(!m.iterationDone()){
            neighbor = m.iterationCurrent();
            m.iterationAdvance();
            neighbor.iterationBegin();
            locationStack.push(m);
            if(!locationStack.isOn(neighbor) &&
               userMaze.isValidLocation(neighbor)){
                locationStack.push(neighbor);
            }
        }
        else if(locationStack.isEmpty()){
            flag = true;
        }
    }
    if(flag){
        cout << "No solution" << endl;
    }
    else {
        cout << "Solution found\n" << locationStack;
    }
    return 0;
}