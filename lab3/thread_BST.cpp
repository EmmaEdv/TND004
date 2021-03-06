/********************************************************
* File: threaded_BST.cpp *
* Author: Aida Nordman *
* Course: TND004, Lab 3 *
* Date: VT2, 2014 *
* Description: class BST_threaded representing *
* a threaded binary search tree *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    ELEMENT temp = std::make_pair("", 0);
    root = new Node(temp);
}

//destructor
//Delete all nodes in the BST, including the dummy node.
BST_threaded::~BST_threaded()
{
    counter = 0;
    root->~Node();

}


//Test if the tree is empty
bool BST_threaded::empty() const
{
    if(root->left == NULL){
       return true;
    }
    return false;
}

//Return number of keys (elements) stored in the tree
int BST_threaded::size() const
{
    return counter;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST as a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;
        counter = 1;
    }
    else{
        counter += root->left->insert(v);
    }
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
    bool isRemoved = root->left->remove(key, root, false);

    if(isRemoved)
        counter--;
}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then behaviour is undefined
ELEMENT& BST_threaded::operator[](string key)
{
    ELEMENT e("", 0);

    Node *temp = root->left->find(key);
    if(temp!= nullptr){
        return temp->value;
    }
    return e;
}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().
BiIterator BST_threaded::find(string key) const
{
     Node *temp = root->left->find(key);
     if(temp != nullptr){
         BiIterator dis(temp);
         return dis;
     }
    return end();
}


//Return an iterator referring to the first node in the inorder traversal of the BST
BiIterator BST_threaded::begin() const
{
    Node *temp = root->left->findMin();
    BiIterator it(temp);
    return it;
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);
    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
