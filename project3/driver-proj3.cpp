/* CSI 3334
 * Project 3 -- Tree-Based Encryption
 * Filename: driver-proj3.cpp
 * Student name: Gabriel Choi
 * assignment: project 3
 * due date: March 3, 2023
 * version: 1.9
 *
 * This file holds the code for the driver class. In this class, it will take
 * input from the user and either insert or remove a word into the binary tree,
 * encrypt or decrypt a message from the user, or print out tree in preorder.
 */

#include <iostream>
#include "bst-student-proj3.h"

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function gets a command from the user. i is to insert a word into the
 *  tree, r is to remove a word from the tree, e is to encrypt the word, d is
 *  to decrypt the word, p is to print out the tree in PreOrder, and q is to
 *  stop the program. For the encrypt and decrypt commands, the program will
 *  output ? if the word is not on the tree.
 */

int main(){
    string buffer;
    const string *message;
    EncryptionTree<string> t;
    t.printPreorder();
    cin >> buffer;

    while(buffer != "q"){
        if(buffer == "i"){
            cin >> buffer;
            t.insert(buffer);
        }
        else if(buffer == "r"){
            cin >> buffer;
            t.remove(buffer);
        }
        else if(buffer == "e"){
            getline(cin, buffer, '\'');
            getline(cin, buffer, '\'');
            cin.ignore();
            int beg = 0;
            int length = buffer.length();
            for(int i = 0; i < length; ++i){
                if(buffer[i] == ' '){
                    cout << t.encrypt(buffer.substr(beg, i - beg)) << " ";
                    beg = i + 1;
                }
            }
            cout << t.encrypt(buffer.substr(beg, buffer.length()-beg)) << endl;
        }
        else if(buffer == "d"){
            getline(cin, buffer, '\'');
            getline(cin, buffer, '\'');
            cin.ignore();
            int beg = 0;
            for(int i = 0; i < buffer.length(); ++i){
                if(buffer[i] == ' '){
                    message = t.decrypt(buffer.substr(beg, i - beg));
                    beg = i + 1;
                    if(message != NULL){
                        cout << *message << " ";
                    }
                    else{
                        cout << "? ";
                    }
                }
            }
            message = t.decrypt(buffer.substr(beg, buffer.length()-beg));
            if(message == NULL){
                cout << "?" << endl;
            }
            else{
                cout << *message << endl;
            }
        }
        else if(buffer == "p"){
            t.printPreorder();
        }
        cin >> buffer;
    }

    return 0;
}
