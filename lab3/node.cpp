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
    //1. search for the string of v -> if found counter ++ -> return false
    //1a. if v == root.value -> return false
    if(this->value.first == v.first){
        this->value.second++;
        return false;
    }
    // if v < root.value, continue in the left subtree
    else if (this->value.first > v.first){
        //does this have any left child? If true --> insert to the left
        if(!this->l_thread){
            return this->left->insert(v);
        }
        else{//insert
            Node *child = new Node(v, this->left, this);
            child->l_thread = child->r_thread = true;
            this->left = child;
            this->l_thread = false; //this has a left child ->is_thread? == false
            //cout << "This is " << this->value.first << " my left child is " << this->left->value.first << " and my right flag is " << this->r_thread << " and my left flag is " << this->l_thread << endl;
            return true;
        }
    }
    //1c. if v > root.value, continue in the right subtree
    else if (this->value.first < v.first){
        //does this have any right child? If true --> insert to the right
        if(!this->r_thread){
            return this->right->insert(v);
        }
        else {
            //insert
            Node *child = new Node(v, this, this->right);
            child->l_thread = child->r_thread = true;
            this->right = child;
            this->r_thread = false; //this has a right child ->is_thread? == false
            //cout << "This is " << this->value.first << " my right child is " << this->right->value.first << " and my right flag is " << this->r_thread << " and my left flag is " << this->l_thread << endl;
            return true;
        }
    }
    //return true;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    if(key < value.first){
     //  cout << key << " < " << value.first << endl;
        if(!l_thread)
            return left->remove(key, this, false);
        else{
        //    cout << key << " was not found " << endl;
            return false;
        }

    }
    else if( key > value.first){
     //   cout << key << " > " << value.first << endl;
        if(!r_thread)
            return right->remove(key, this, true);
        else{
    //        cout << key << " was not found " << endl;
            return false;
        }
    }
    else if(key == value.first){
        //if two children
        if(!r_thread && !l_thread){
            //cout << key << " has two kids! " << endl;
            value = left->findMax()->value;
            return left->remove(value.first, this, false);
        }

        else{
          //  cout << "tjoho, nu försvinner " << key << endl;
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

   // Node *current = (isRight == true) ? parent->right : parent->left;
   // cout << "removeMe is called, yup! and this node is a ";
    if(isRight){
     //   cout << "right child" << endl;
        //1. A right child with no children -> simply remove current
        if(this->l_thread && this->r_thread){
      //      cout << "right tree has no children!" << endl;
            parent->r_thread = true;
            parent->right = this->right;
            delete this;
        }

        //2. a right child with a left child
        else if(!this->l_thread && this->r_thread){
         //   cout << "right tree has a left child!" << endl;
            parent->right = this->left;
            Node * temp = parent->right->findMax();
            temp->right = this->right;
            delete this;
        }
        //3. a right child with a right child
        else if(this->l_thread && !this->r_thread){
       //     cout << "right tree has a right child!" << endl;
            parent->right = this->right;
            Node * temp = parent->right->findMin();
            temp->left = this->left;
            delete this;
        }
    }
    else{ //(!isRight) == left child
      //  cout << "left child" << endl;
        //1. No children -> simply remove current
        if(this->l_thread && this->r_thread){
          //  cout << "left tree has no children!" << endl;
            parent->l_thread = true;
            parent->left = this->left;
            delete this;
        }

        //2. a left child with left child
        else if(!this->l_thread && this->r_thread){
         //   cout << "left tree has a left child!" << endl;
            parent->left = this->left;
            Node * temp = parent->left->findMax();
            temp->right = this->right;
            delete this;
        }
        //3. left child with a right child
        else if(this->l_thread && !this->r_thread){
          //  cout << "left tree has a right child!" << endl;
            parent->left = this->right;
            Node * temp = parent->left->findMin();
            temp->left = this->left;
            delete this;
        }
    }
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

    if(key > itr->value.first){
        if(!r_thread){
            itr = itr->right;
            return itr->find(key);
        }
        else {
            return nullptr;
        }
    }

    else if (key < itr->value.first){
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
       // cout << this->value.first << " not the smallest" << endl;
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
