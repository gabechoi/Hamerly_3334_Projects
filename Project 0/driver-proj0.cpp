/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Gabriel Choi
 * assignment: project 0
 * due date: January 20, 2023
 * version: 1.2
 *
 * This file contains the code for the typing, undo, and redo functions.
 */

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

const int MAX = 10000;
const int MIN = 0;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function takes in a number of commands determined by the user. With
 *  each command, either undo, redo, or type, it will undo a word the user has
 *  inputted, redo an undo the user has done, or write a word to the stack.
 *  Then the typing stack and undo stack will be outputted on two different
 *  lines.
 */

int main(int argc, char **argv) {
    // these are the two stacks used to store the typed words and the undone
    // words
    stack<string> typing, undo;
    // these are two stacks used to reverse the orders of the other two stacks
    stack<string> typingRev, undoRev;
    int n;
    char command;
    string word;
    string space = " ";

    cin >> n;
    //this checks to make sure that amount of commands is less than the maximum
    // amount
    assert(n < MAX);
    for(int i = 0; i < n; ++i){
        cin >> command;
        assert(command == 't' || command != 'u' || command != 'r');
        if(command == 't'){
            cin >> word;
            typing.push(word);
        }
        else if(command == 'u'){
            if(typing.empty()){
                cout << "nothing to undo on command " << i + 1 << endl;
            }
            else {
                undo.push(typing.top());
                typing.pop();
            }

        }
        else{
            if(undo.empty()){
                cout << "nothing to redo on command " << i + 1 << endl;
            }
            else{
                typing.push(undo.top());
                undo.pop();
            }

        }
    }
    while(!typing.empty()){
        typingRev.push(typing.top());
        typing.pop();
    }
    while(!undo.empty()){
        undoRev.push(undo.top());
        undo.pop();
    }
    //this outputs the typing stack in reverse order
    while(!typingRev.empty()){
        cout << typingRev.top();
        typingRev.pop();
        if(!typingRev.empty()){
            cout << " ";
        }
    }
    cout << endl;
    //this outputs the undo stack in reverse order
    while(!undoRev.empty()){
        cout << undoRev.top();
        undoRev.pop();
        if(!undoRev.empty()){
            cout << " ";
        }
    }
    cout << endl;
    return 0;
}
