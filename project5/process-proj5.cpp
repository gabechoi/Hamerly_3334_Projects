/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: process-proj5.cpp
 * Student name: Gabriel Choi
 * assignment: project 5
 * due date: April 14, 2023
 * version: 1.0
 *
 * This file holds the code for the process class.
 */

#include "process-proj5.h"

/* Process
 *  parameters:
 *      theId: the id number for the process
 *  return value: none
 *
 *  This is the default constructor for the Process class.
 */
Process::Process(int theId){
    this->id = theId;
    this->submissionTime = 0;
    this->deadline = 0;
    this->requiredTime = 0;
    this->information = "";
}

/* run
 *  parameters:
 *      currentSystemTime: the current time the system is at
 *  return value: the time at which the process will finish running
 *
 *  This function runs the process and returns the time at which the process
 *  finishes running.
 */
int Process::run(int currentSystemTime) const{
    cout << "running process id " << this->id << " at " << currentSystemTime;
    cout << '\n' << information << endl;
    return currentSystemTime + this->requiredTime;
}

/* canComplete
 *  parameters:
 *      currentSystemTime: the current time the system is at
 *  return value: returns if the process is able to finish before its deadline
 *
 *  This function determines if the process is able to finish before its
 *  deadline.
 */
bool Process::canComplete(int currentSystemTime) const{
    return (currentSystemTime + this->requiredTime) <= this->deadline;
}

/* getId
 *  parameters: none
 *  return value: returns the id of the process
 *
 *  This function returns the id of the process
 */
int Process::getId() const{
    return this->id;
}

/* getSubmissionTime
 *  parameters: none
 *  return value: returns the submission time of the process
 *
 *  This function returns the submission time of the process
 */
int Process::getSubmissionTime() const{
    return this->submissionTime;
}

/* operator<
 *  parameters:
 *      p: the process that is being compared to this process
 *  return value: if this process is less than that process in terms of its
 *                deadline, required time, and id
 *
 *  This function returns if this process is less than that process in terms of
 *  its deadline, required time, and id.
 */
bool Process::operator<(Process const &p) const{
    if(this->deadline < p.deadline){
        return true;
    }
    else if(this->deadline == p.deadline){
        if(this->requiredTime < p.requiredTime){
            return true;
        }
        else if(this->requiredTime == p.requiredTime){
            if(this->id < p.id){
                return true;
            }
        }
    }
    return false;
}

/* operator>>
 *  parameters:
 *      is: the istream that will read in the process
 *      p: the address of the Process that will read into
 *  return value: the istream that will be read in from
 *
 *  This function reads in the process's submission time, deadline, required
 *  time, and information.
 */
istream &operator>>(istream &is, Process &p){
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    //getline(is, p.information, ' ');
    getline(is >> ws, p.information);
    //cout << "DEBUG: reading in " << p.submissionTime << " "
    // << p.deadline << " " << p.requiredTime;
    //cout << " " << p.information << endl;
    return is;
}
