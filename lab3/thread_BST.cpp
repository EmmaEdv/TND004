/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
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
    //ADD CODE
    ELEMENT temp = std::make_pair("", 0);
    root = new Node(temp);
}


//destructor
BST_threaded::~BST_threaded()
{
  //ADD CODE
}


//Test if the tree is empty
bool BST_threaded::empty() const
{
    //ADD CODE
    if(root->left == NULL){
       return true;
    }
    return false;
}

//Return mumber of keys (elements) stored in the tree
int BST_threaded::size() const
{
   //ADD CODE
    return 0;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST has a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;
        counter = 1;
    }
    else
        counter += root->left->insert(v); //call NODE::insert
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
   //1, find the node, their parent and if the child is a right child 
   //Vänster träd: om båda flaggorna är true -> förälder den som är minst
   //Höger träd: om båda flaggorna är true -> förälder den som är störst
    
    //1. find the parent node.
    cout << "jupp, I right at it.." << endl;
    bool isRemoved = root->left->remove(key, root, false);
    
    if(isRemoved)
        cout << "I removed " << key << " and now it is gone" << endl;
    else
        cout << "you crazy basterd, " << key << " wasn't even there... " << endl;
    
//    if(current != nullptr){
//        BiIterator pointis(current);
//        
        //if the node is a leaf
//        if(current->l_thread && current->r_thread){
//            
//            //if the value is stored in the left subtree
//            if(current->left->value.first < root->left->value.first){
//                cout << "current : "<< current->value.first << " is smaller than root: "  << root->left->value.first << endl;
//                
//                parent = (current->left->value.first < current->right->value.first && current->left != root) ? current->left : current->right;
//                cout << " current: " << current->value.first << " parent node is: " << parent->value.first << endl;
//            }
//            //if the value is stored in the right subtree
//            else {
//                cout << "current : "<< current->value.first << " is larger than root: "  << root->left->value.first << endl;
//                parent = (current->left->value.first > current->right->value.first && current->right != root) ? current->left : current->right;
//                cout << "current: " << current->value.first << " parent node is: " << parent->value.first << endl;
//            }
//        }//at least one type
//        else{
//            cout << "current has at least one child" << endl;
//            if(current->value.first < root->left->value.first){
//                if(current->right->right->left == current){
//                    parent = current->right->right;
//                    cout << "current: " << current->value.first << " parent node is: " << parent->value.first << endl;
//                }
//            }
//            else if(current->left->left->right == current){
//                parent = current->left->left;
//                cout << "current: " << current->value.first << " parent node is: " << parent->value.first << endl;
//                
//            }
//        }
//    }
    
}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then behaviour is undefined
ELEMENT& BST_threaded::operator[](string key)
{
    //ADD CODE
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
    //cout << "minimum value is: " << temp->value.first << endl;
    return it;
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);
    //cout << "end-function!" << endl;
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
