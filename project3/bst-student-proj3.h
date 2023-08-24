/* CSI 3334
 * Project 3 -- Tree-Based Encryption
 * Filename: bst-student-proj.h
 * Student name: Gabriel Choi
 * assignment: project 3
 * due date: March 3, 2023
 * version: 1.9
 *
 * This file holds the code for the student proj class. In this class, it
 * holds the destructor for a BSTNode, a function to print the tree in
 * preorder, a function to find the smallest or biggest node of the tree,
 * insert or delete a node into the tree, and decrypt or encrypt a message
 * based on the contents of the tree.
 */

#ifndef BST_STUDENT_PROJ3
#define BST_STUDENT_PROJ3

#include "bst-prof-proj3.h"


/* ~BSTNode
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the BSTNode class.
 */
template <class Base>
BSTNode<Base>::~BSTNode(){
    delete this->left;
    delete this->right;
    this->left = this->right = NULL;
}

/* printPreorder
 *  parameters:
 *      os: the ostream that the tree will be printed out on
 *  return value: none
 *
 *  This function prints the tree in preorder.
 */
template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << this->data << endl;
    if(this->left != NULL){
        this->left->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }
    if(this->right != NULL){
        this->right->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }

}

/* minNode
 *  parameters: none
 *  return value: the smallest node in the tree
 *
 *  This function finds the smallest node on from the given root.
 */
template <class Base>
const BSTNode<Base>* BSTNode<Base>::minNode() const{
    if(this->left == NULL){
        return this;
    }
    else{
        return this->left->minNode();
    }
}

/* maxNode
 *  parameters: none
 *  return value: the biggest node in the tree
 *
 *  This function finds the biggest node on from the given root.
 */
template <class Base>
const BSTNode<Base> * BSTNode<Base>::maxNode() const{
        if(this->right == NULL){
            return this;
        }
        else {
            return this->right->maxNode();
        }
}

/* insert
 *  parameters:
 *      item: the treeNode that will be inserted into the tree
 *  return value: none
 *
 *  This function will insert a BSTNode into the tree at its correct spot.
 */
template <class Base>
void BST<Base>::insert(const Base &item){
    bool flag = true;
    if(this->root == NULL){
        this->root = new BSTNode<Base>(item);
    }
    else {
        BSTNode<Base> *temp = this->root;
        while(flag){
            if(item < temp->data){
                if(temp->left == NULL){
                    temp->left = new BSTNode<Base>(item);
                    flag = false;
                }
                else{
                    temp = temp->left;
                }
            }
            else if(temp->data < item){
                if(temp->right == NULL){
                    temp->right = new BSTNode<Base>(item);
                    flag = false;
                }
                else{
                    temp = temp->right;
                }
            }
            else{
                flag = false;
            }
        }
    }
}

/* encrypt
 *  parameters:
 *      item: the treeNode that will be encrypted by the tree
 *  return value: the path that leads to the word in the tree
 *
 *  This function encrypt a word by recording its path. If the word is not
 *  found, then ? is returned.
 */
template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const{
    string r = "r";
    bool pathFound = false;
    const BSTNode<Base> *temp = this->root;
    while(temp != NULL){
        if(item < temp->getData()){
            r += "0";
            temp = temp->getLeft();
        }
        else if(temp->getData() < item){
            r += "1";
            temp = temp->getRight();
        }
        else{
            pathFound = true;
            temp = NULL;
        }
    }

    if(!pathFound){
        r = "?";
    }

    return r;

}

/* encrypt
 *  parameters:
 *      path: the path that leads to an encrypted word in the tree
 *  return value: the word that the path leads to
 *
 *  This function decrypts a word by following the given path. If the word is
 *  not found, then NULL is returned.
 */
template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const{
    const BSTNode<Base> *temp = this->root;
    if(temp == NULL){
        return NULL;
    }
    if(path != "r"){
        for(int i = 1; i < path.length() && temp != NULL; ++i){
            if(path[i] == '0'){
                temp = temp->getLeft();
            }
            else{
                temp = temp->getRight();
            }
        }
    }


    return &temp->getData();
}

/* remove
 *  parameters:
 *      item: the treeNode that will be removed from the tree
 *  return value: none
 *
 *  This function will remove a BSTNode from the tree. If the root is removed,
 *  then the leftmost right node will replace the root.
 */
template <class Base>
void BST<Base>::remove(const Base &item){
    BSTNode<Base> *toRemove = this->root;
    BSTNode<Base> *parent = NULL;
    bool found = false;
    while(toRemove != NULL && !found){
        if(!(item < toRemove->data || toRemove->data < item)){
            found = true;
        }
        else if(item < toRemove->data){
            parent = toRemove;
            toRemove = toRemove->left;
        }
        else if(toRemove->data < item){
            parent = toRemove;
            toRemove = toRemove->right;
        }
    }
    if(found){
        if(toRemove->left != NULL && toRemove->right != NULL){
            BSTNode<Base> *leftMost = toRemove->right;
            BSTNode<Base> *leftMostParent = toRemove;
            if(leftMost->left != NULL){
                while(leftMost->left != NULL){
                    leftMostParent = leftMost;
                    leftMost = leftMost->left;
                }
                leftMostParent->left = leftMost->right;
                leftMost->right = toRemove->right;
            }
            leftMost->left = toRemove->left;
            if(parent != NULL){
                if(parent->left == toRemove){
                    parent->left = leftMost;
                }
                else{
                    parent->right = leftMost;
                }
            }
            else {
                this->root = leftMost;
            }

            toRemove->right = toRemove->left = NULL;
            leftMostParent = NULL;
            delete toRemove;
        }
        else if(toRemove->left != NULL || toRemove->right != NULL){
            BSTNode<Base> *child = NULL;
            if (toRemove->left != NULL) {
                child = toRemove->left;
                toRemove->left = NULL;
            }
            else{
                child = toRemove->right;
                toRemove->right = NULL;
            }
            if(parent != NULL){
                if (parent->left == toRemove) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            }
            else {
                this->root = child;
            }

            delete toRemove;
        }
        else{
            if(parent != NULL){
                if(parent->left == toRemove){
                    parent->left = NULL;
                }
                else{
                    parent->right = NULL;
                }
            }
            delete toRemove;
            if(parent == NULL){
                this->root = NULL;
            }
        }
    }
}

#endif
