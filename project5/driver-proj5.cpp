/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: driver-proj5.cpp
 * Student name: Gabriel Choi
 * assignment: project 5
 * due date: April 14, 2023
 * version: 1.0
 *
 * This file holds the code for the driver class. In this class, act as a
 * batch os system, taking in processes from the user and either running
 * or skipping them based on if their they can complete their process
 * before or by the deadline. Then, it will print out the amount of
 * processes run, skipped, and the amount of time taken to finish.
 */

#include "arrayheap-student-proj5.h"
#include "process-proj5.h"

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function first gets the amount of processes that will be inputed.
 *  The current time will be set to 0 and increases when a process is either
 *  skipped or ran. The function will not immediately place each processinto
 *  the heap, but only after its submission time has been reached. Then the
 *  driver will place it into a high priority heap, and will run the process
 *  if can complete before the deadline or skip if it cannot. Then at the end,
 *  the final time, amount run, and amount skipped will output to the screen.
 */

int main(){
    int n = 0, readIn = 0;
    int time = 0;
    ArrayHeap<Process> procHeap;
    int numSkip = 0;
    int numRun = 0;
    Process *proc = new Process();
    Process currProc;
    int procId = 0;
    bool input = true;

    cin >> n;
    cin >> *proc;

    readIn = n;

    while(n > 0){
        while(proc->getSubmissionTime() <= time && /*input*/readIn > 0){
            //cout << "DEBUG: inserting process ID " << proc->getId() << " into heap" << endl;
            procHeap.insert(*proc);
            readIn--;
            //n--;
            procId++;
            delete proc;
            proc = new Process(procId);
            if(readIn > 0){
                cin >> *proc;
            }
            //if(!(cin >> *proc)){input = false;}

        }
        //cout << "DEBUG: heap has " << procHeap.getNumItems() << " items;";
        //cout << " top priority is ID " << procHeap.getMinItem().getId() << endl;
        //delete proc;
        if(procHeap.getNumItems() == 0){
            ++time;
        }
        else{
            currProc = procHeap.getMinItem();
            procHeap.removeMinItem();
            n--;
            if(currProc.canComplete(time)){
                time = currProc.run(time);
                numRun++;
            }
            else{
                cout << "skipping process id " << currProc.getId() << " at ";
                cout << time << endl;
                numSkip++;
                time++;
            }
        }


    }
    delete proc;

    cout << "final clock is                 " << time << endl;
    cout << "number of processes run is     " << numRun << endl;
    cout << "number of processes skipped is " << numSkip << endl;

    return 0;
}
