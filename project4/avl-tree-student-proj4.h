/* CSI 3334
 * Project 4 -- Balanced tree-based encryption and decryption
 * Filename: avl-tree-student-proj.h
 * Student name: Gabriel Choi
 * assignment: project 4
 * due date: March 24, 2023
 * version: 1.9
 *
 * This file holds the code for the student proj class. In this class, it
 * holds the destructor for a AVLNode, a function to print the tree in
 * preorder and level order, a function to find the smallest or biggest node
 * of the tree insert or delete a node into the tree, rebalance the tree,
 * and decrypt or encrypt a message based on the contents of the tree.
 */

#ifndef AVL_TREE_STUDENT_PROJ4
#define AVL_TREE_STUDENT_PROJ4

#include "avl-tree-prof-proj4.h"
#include <queue>

/* ~AVLNode
 *  parameters: none
 *  return value: none
 *
 *  This is the destructor for the AVLNode class.
 */
template <class Base>
AVLNode<Base>::~AVLNode(){
    delete this->left;
    delete this->right;
}

/* printPreorder
 *  parameters:
 *      os: the ostream that the tree will be printed out on
 *  return value: none
 *
 *  This function prints the tree in preorder.
 */
template <class Base>
void AVLNode<Base>::printPreorder(ostream &os, string indent) const{
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
const AVLNode<Base> *AVLNode<Base>::minNode() const{
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
const AVLNode<Base> * AVLNode<Base>::maxNode() const{
    if(this->right == NULL){
        return this;
    }
    else {
        return this->right->maxNode();
    }
}

/* singleRotateLeft
 *  parameters: none
 *  return value: the node that has the highest height
 *
 *  This function rotates a group of nodes to the left.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateLeft() {
    AVLNode<Base> *rightChild = this->right;

    this->right = rightChild->left;
    rightChild->left = this;
    this->updateHeight();
    rightChild->updateHeight();
    //parent->updateHeight();
    return rightChild;
}

/* singleRotateRight
 *  parameters: none
 *  return value: the node that has the highest height
 *
 *  This function rotates a group of nodes to the right.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateRight() {
    AVLNode<Base> *leftChild = this->left;

    this->left = leftChild->right;
    /*if(parent->right == node){
    parent->right = leftChild;
    }
    else{
    parent->left = leftChild;
    }*/
    leftChild->right = this;
    this->updateHeight();
    leftChild->updateHeight();
    //parent->updateHeight();
    return leftChild;
}

/* doubleRotateLeftRight
 *  parameters: none
 *  return value: the node that has the highest height
 *
 *  This function rotates a group of nodes to the left, then to the right.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateLeftRight(){
    this->left = this->left->singleRotateLeft();
    return this->singleRotateRight();
}

/* doubleRotateRightLeft
 *  parameters: none
 *  return value: the node that has the highest height
 *
 *  This function rotates a group of nodes to the right, then to the left.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateRightLeft(){
    this->right = this->right->singleRotateRight();
    return this->singleRotateLeft();
}

/* rebalancePathToRoot
 *  parameters:
 *      path: a vector that holds the path from the insertion/removal back
 *            to the root
 *  return value: none
 *
 *  This function checks each node in the path to see if there is an imbalance,
 *  and rotates the sub-tree accordingly to fix the imbalance.
 */
template <class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path){
    for(int i = path.size() - 1; i >= 0; --i){
        AVLNode<Base> *node = path.at(i);
        AVLNode<Base> *pNode;
        if(0 < i){pNode = path.at(i - 1);}
        //if child left has higher height than child right
        if(node->getHeight(node->left) -
         node->getHeight(node->right) > 1){
            //if gchild left has lower height than gchild right
            if(node->getHeight(node->left->left) -
             node->getHeight(node->left->right) < 0) {
                //if node is root
                if(i == 0){
                    this->root = node->doubleRotateLeftRight();
                }
                else{
                    if(pNode->right == node){
                        pNode->right = node->doubleRotateLeftRight();
                    }
                    else{
                        pNode->left = node->doubleRotateLeftRight();
                    }
                }
            }
            else{
                //if node is root
                if(i == 0){
                    this->root = node->singleRotateRight();
                }
                else{
                    if(pNode->right == node){
                        pNode->right = node->singleRotateRight();
                    }
                    else{
                        pNode->left = node->singleRotateRight();
                    }
                }
            }
        }
        else if(node->getHeight(node->right) -
         node->getHeight(node->left) > 1){
            //if gchild left has higher height than gchild right
            if(node->getHeight(node->right->left) -
             node->getHeight(node->right->right) > 0) {
                //if node is root
                if(i == 0){
                    this->root = node->doubleRotateRightLeft();
                }
                else{
                    if(pNode->right == node){
                        pNode->right = node->doubleRotateRightLeft();
                    }
                    else{
                        pNode->left = node->doubleRotateRightLeft();
                    }
                }
            }
            else{

                //if node is root
                if(i == 0){
                    this->root = node->singleRotateLeft();
                }
                else{
                    if(pNode->right == node){
                        pNode->right = node->singleRotateLeft();
                    }
                    else{
                        pNode->left = node->singleRotateLeft();
                    }
                }
            }
        }
        node->updateHeight();
    }
}

/* insert
 *  parameters:
 *      item: the tree node that will be inserted into the tree
 *  return value: none
 *
 *  This function will insert a AVLNode into the tree at its correct spot,
 *  then rebalance the tree if need be.
 */
template <class Base>
void AVLTree<Base>::insert(const Base &item){
    //cout << "DEBUG: inserting word '" << item << "'" << endl;
    vector<AVLNode<Base>*> nodeVec;
    bool flag = true;
    if(this->root == NULL){
        this->root = new AVLNode<Base>(item);
    }
    else {
        AVLNode<Base> *temp = this->root;
        while(flag){
            nodeVec.push_back(temp);
            if(item < temp->data){
                if(temp->left == NULL){
                    temp->left = new AVLNode<Base>(item);
                    nodeVec.push_back(temp->left);
                    flag = false;
                }
                else{
                    temp = temp->left;
                }
            }
            else if(temp->data < item){
                if(temp->right == NULL){
                    temp->right = new AVLNode<Base>(item);
                    nodeVec.push_back(temp->right);
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
        this->rebalancePathToRoot(nodeVec);
    }
}

/* remove
 *  parameters:
 *      item: the treeNode that will be removed from the tree
 *  return value: none
 *
 *  This function will remove a AVLNode from the tree. If the root is removed,
 *  then the leftmost right node will replace the root. Then the function will
 *  rebalance the tree if need be.
 */
template <class Base>
void AVLTree<Base>::remove(const Base &item){
    //cout << "DEBUG: removing word '" << item << "'" << endl;
    vector<AVLNode<Base>*> nodeVec;
    if(this->root != NULL){
        AVLNode<Base> *toRemove = this->root;
        AVLNode<Base> *parent = toRemove;
        bool found = false;
        while(toRemove != NULL && !found){
            nodeVec.push_back(toRemove);
            if(!(item < toRemove->data || toRemove->data < item)){
                found = true;
            }
            else if(item < toRemove->data){
                parent = toRemove;
                //nodeVec.push_back(toRemove);
                toRemove = toRemove->left;
            }
            else if(toRemove->data < item){
                parent = toRemove;
                //nodeVec.push_back(toRemove);
                toRemove = toRemove->right;
            }
        }
        if(found){
            if(toRemove->left != NULL && toRemove->right != NULL){
                AVLNode<Base> *leftMost = toRemove->right;
                AVLNode<Base> *leftMostParent = toRemove;
                int index = nodeVec.size() - 1;

                if(leftMost->left != NULL){
                    while(leftMost->left != NULL){
                        nodeVec.push_back(leftMost);
                        leftMostParent = leftMost;
                        leftMost = leftMost->left;
                    }
                    leftMostParent->left = leftMost->right;
                    leftMost->right = toRemove->right;
                }

                leftMost->left = toRemove->left;
                nodeVec.at(index) = leftMost;
                if(parent != toRemove){
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
            }
            else if(toRemove->left != NULL || toRemove->right != NULL){
                AVLNode<Base> *child = NULL;
                if (toRemove->left != NULL) {
                    child = toRemove->left;
                    toRemove->left = NULL;
                }
                else{
                    child = toRemove->right;
                    toRemove->right = NULL;
                }
                if(parent != toRemove){
                    if (parent->left == toRemove) {
                        parent->left = child;
                    } else {
                        parent->right = child;
                    }
                }
                else {
                    this->root = child;
                }
            }
            else{
                if(parent != toRemove){
                    if(parent->left == toRemove){
                        parent->left = NULL;
                    }
                    else{
                        parent->right = NULL;
                    }
                }
                else{
                    this->root = NULL;
                }
            }
            this->rebalancePathToRoot(nodeVec);
            delete toRemove;
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
    const AVLNode<Base> *temp = this->root;
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

/* decrypt
 *  parameters:
 *      path: the path that leads to an encrypted word in the tree
 *  return value: the word that the path leads to
 *
 *  This function decrypts a word by following the given path. If the word is
 *  not found, then NULL is returned.
 */
template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const{
    const AVLNode<Base> *temp = this->root;
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

/* printLevelOrder
 *  parameters:
 *      os: the ostream that the tree will be printed out on
 *  return value: none
 *
 *  This function prints the tree in level order.
 */
template <class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const{
    if(this->root != NULL){
        queue<AVLNode<Base>*> path;
        int max = 20;
        int nCount = 0;
        path.push(this->root);
        while(!path.empty()){
            AVLNode<Base>* temp = path.front();
            path.pop();
            ++nCount;
            if(temp != NULL){
                os << temp->data;
                path.push(temp->left);
                path.push(temp->right);
            }
            else{
                os << "NULL";
            }
            //break loop if empty
            if(!path.empty()){
                if(nCount >= max){
                    os << endl;
                    nCount = 0;
                }
                else{
                    os << ' ';
                }
            }
        }
        os << endl;
    }
    else {
        os << "NULL" << endl;
    }
}

#endif
