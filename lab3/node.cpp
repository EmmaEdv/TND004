/**********************************************
* File: node.cpp *
* Author: Aida Nordman *
* Course: TND004, Lab 3 *
* Date: VT2, 2014 *
* Description: class Node *
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
    //Left subtree
    if(!this->l_thread){
        delete left;
    }
    //Right subtree
    if(!this->r_thread){
        delete right;
    }
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    //search for the string of v

    //if the word exists, increment the counter and return false
    if(this->value.first == v.first){
        this->value.second++;
        return false;
    }
    // if v is smaller than the value of the node, continue in the left subtree
    else if (this->value.first > v.first){
        //if this has a left child, recursive call
        if(!this->l_thread){
            return this->left->insert(v);
        }
        else{//insert
            Node *child = new Node(v, this->left, this);
            child->l_thread = child->r_thread = true;
            this->left = child;
            this->l_thread = false;
            return true;
        }
    }
    //if v is larger than the value of the node, continue in the right subtree
    else if (this->value.first < v.first){
        //if this has a right child, recursive call
        if(!this->r_thread){
            return this->right->insert(v);
        }
        else {
            Node *child = new Node(v, this, this->right);
            child->l_thread = child->r_thread = true;
            this->right = child;
            this->r_thread = false;
            return true;
        }
    }
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //if key is smaller than the value
    if(key < value.first){
        //check if the node storing key has a left child, if so continue
        if(!l_thread)
            return left->remove(key, this, false);
        else{
            return false;
        }
    }
    // if the key is larger than the value
    else if(key > value.first){
        //check if the node storing key has a right child, if so continue
        if(!r_thread)
            return right->remove(key, this, true);
        else{
            return false;
        }
    }
    //if the key is found
    else if(key == value.first){
        //check if the node storing key has any children,
        //if so replace root with the largest value of the left subtree and remove the leaf
        if(!r_thread && !l_thread){
            value = left->findMax()->value;
            return left->remove(value.first, this, false);
        }
        //else remove the node
        else{
            removeMe(parent,isRight);
            return true;
        }
    }
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
void Node::removeMe(Node* parent, bool isRight){
    if(isRight){
        //2c: a right child with no children
        if(this->l_thread && this->r_thread){
            parent->r_thread = true;
            parent->right = this->right;
        }
        //2b: a right child with only a left child
        else if(!this->l_thread &&  this->r_thread){
            parent->right = this->left;
            Node *temp = parent->right->findMax();
            temp->right = this->right;
        }
        //2a: a right child with only a right child
        else if(this->l_thread && !this->r_thread){
            parent->right = this->right;
            Node *temp = parent->right->findMin();
            temp->left = this->left;
        }
    }
    else{
        //1c: a left child with no children
        if(this->l_thread && this->r_thread){
            parent->l_thread = true;
            parent->left = this->left;
        }
        //1b: a left child with only a left child
        else if(!this->l_thread && this->r_thread){
            parent->left = this->left;
            Node *temp = parent->left->findMax();
            temp->right = this->right;
        }
        //1a: a left child with only a right child
        else if(this->l_thread && !this->r_thread){
            parent->left = this->right;
            Node *temp = parent->left->findMin();
            temp->left = this->left;
        }
    }
    this->l_thread = this->r_thread = true;
    delete this;
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //compare with actual value
    Node *itr = this;

    if(key == itr->value.first){
        return itr;
    }
    //if the key is larger than this node
    if(key > itr->value.first){
        //if this has a right child, recursive call
        if(!r_thread){
            itr = itr->right;
            return itr->find(key);
        }
        else {
            return nullptr;
        }
    }
    //if the key is smaller than this node
    else if (key < itr->value.first){
        //if this has a left child, recursive call
        if(!l_thread){
            itr = itr->left;
            return itr->find(key);
        }
        else {
            return nullptr;
        }
    }
    return itr;
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin()
{
    if (!this->l_thread){
        return this->left->findMin();
    }
    return this;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    if(!this->r_thread){
        return this->right->findMax();
    }
    return this;
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
