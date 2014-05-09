/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    //ADD CODE
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    Node *temp = &(*this);
    string rooten = "6"; //this->value.first
    bool root_thread_l = true;
    bool root_thread_r = true;

    cout << "now I will insert " << v.first  << " with root = "  << temp->value.first <<  endl;
//    1. search for the string of v -> if found counter ++ -> return false
//    1a. if v == root.value -> return false
//    if( rooten == v.first){
//        cout << "the value is already in the tree" << endl;
//        this->value.second++;
//        return false;
//    }//1b. if v < root.value, continue in the left subtree
//    else if (rooten > v.first){
//            cout << rooten << " > " << v.first << endl;
//        does this have any flags to the left? If no --> walk to the left in the tree
//        if(root_thread_l){
//            cout << "inserts v = " << v.first << " as left child of " << rooten << endl;
//            If yes --> insert to the left
//            HÄR PASSAR BARNET IN!
//            Node *child = new Node(v, this, this->right);
//            Node *child = new Node(v, nullptr, nullptr);
//            child->r_thread = true;
//            child->l_thread = true;
//            this->left = child;
//            this->l_thread = false; //this has a left child ->is_thread? == false
//        }
//        else{
//            cout << "passed vidare" << endl;
//            this->left->insert(v);
//        }
//
//    }//1c. if v > root.value, continue in the right subtree
//    else if (rooten < v.first){
//            cout << rooten << " < " << v.first << endl;
//        does this have any flags to the right? If no --> walk to the right in the tree
//        if(root_thread_r){
//            cout << "inserts v = " << v.first << " as right child of " << rooten << endl;
//            If yes --> insert to the right
//            här passar barnet in!
//            Node *child = new Node(v, this->left, this);
//            Node *child = new Node(v, nullptr, nullptr);
//            child->r_thread = true;
//            child->l_thread = true;
//            this->right = child;
//            this->r_thread = false; //this has a right child ->is_thread? == false
//        }
//        else {
//            cout << "passed vidare" << endl;
//            this->right->insert(v);
//        }
//    }

    return false;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
   //ADD CODE
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //ADD CODE
    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    //ADD CODE
    return nullptr;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    return nullptr;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
