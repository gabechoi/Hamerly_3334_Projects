/* CSI 3334
 * Project 2 --  Word Melt Shortest-Path Solver
 * Filename: location-proj2.cpp
 * Student name: Gabriel Choi
 * assignment: project 2
 * due date: February 17, 2023
 * version: 1.9
 *
 * This file holds the code for Location class.
 */

#include "location-proj2.h"

//const char START = 96;

/* Location
 *  parameters: none
 *  return value: none
 *
 *  This is the constructor for the Location class, initializing all values.
 */
Location::Location(){
    this->word = "";
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
}

/* iterationBegin
 *  parameters: none
 *  return value: none
 *
 *  This function initializes the iteration capability of the Location object.
 */
void Location::iterationBegin(){
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
    if(this->word[this->indexToChange] == 'a'){
        this->nextLetter++;
    }
}

/* iterationCurrent
 *  parameters: none
 *  return value: the neighbor location
 *
 *  This function creates a copy of the current Location object, modifies the
 *  copy so that it represents a different word, and it returns the
 *  neighbor it created.
 */
Location Location::iterationCurrent() const{
    Location neighbor;
    neighbor.word = this->word;
    if(this->iterationMode == CHANGE_LETTER) {
        neighbor.word[this->indexToChange] = this->nextLetter;
    }
    else if (this->iterationMode == INSERT_LETTER){
        neighbor.word.insert(this->indexToChange, 1, this->nextLetter);
    }
    else{
        neighbor.word.erase(this->indexToChange, 1);
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
void Location::iterationAdvance(){
    //delete letter does not need to run through every letter
    if(this->iterationMode == DELETE_LETTER){
        this->indexToChange++;
        if(this->indexToChange >= word.size()){
            this->iterationMode++;
            this->indexToChange = 0;
        }
    }
    else if(this->iterationMode == INSERT_LETTER) {
        if (this->nextLetter != 'z') {
            this->nextLetter++;
        } else if (this->word.length() >= this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
        }

        if (this->indexToChange > word.size()) {
            this->iterationMode++;
            this->indexToChange = 0;
            this->nextLetter = 'a';
        }
    }
    else{
        if (this->nextLetter != 'z') {
            this->nextLetter++;
        } else if (this->word.length() > this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
            if(this->word[this->indexToChange] == this->nextLetter){
                this->nextLetter++;
            }
        }
        if(this->word[indexToChange] == this->nextLetter){
            if(this->nextLetter >= 'z'){
                this->indexToChange++;
                this->nextLetter = 'a';
                if(this->word[this->indexToChange] == 'a'){
                    this->nextLetter++;
                }
            }
            else{
                this->nextLetter++;
            }
        }
        if(this->indexToChange >= word.size()){
            this->iterationMode++;
            this->indexToChange = 0;
            this->nextLetter = 'a';
        }
    }
}

/* iterationDone
 *  parameters: none
 *  return value: if the all the neighbors have been checked
 *
 *  This function returns true when the all the neighbors of a Location have
 *  been iterated over.
 */
bool Location::iterationDone() const{
    return this->iterationMode == DONE;
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
    return this->word == loc.word;
}

/* &operator<<
 *  parameters:
 *  os: the ostream that will stream out the location
 *  loc: the location object that will into the ostream
 *  return value: the ostream with the row and col
 *
 *  This function provide a means of streaming a Location object out.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/* &operator>>
 *  parameters:
 *  is: the istream that will stream in the location to this
 *  loc: the Location object that will be streamed into this Location
 *  return value: the istream with the row and col
 *
 *  This function provide a means of streaming a Location object in.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}

/* operator<
 *  parameters:
 *  loc: the Location object that will be compared to this Location
 *  return value: if this Location's word is less than loc's word
 *
 *  This function provide a comparing two Location objects together.
 */
bool Location::operator<(const Location &loc) const{
    return this->word < loc.word;
}
