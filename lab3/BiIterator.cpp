/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {

 }


//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
    return this->current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    ELEMENT *e = &(this->current->value);
    return e;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    ELEMENT v1 = this->current->value;
    ELEMENT v2 = *it;
    if(v1 == v2){
        return true;
    }
    return false;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
    ELEMENT v1 = this->current->value;
    ELEMENT v2 = *it;
    if(v1 != v2){
        return true;
    }
    return false;
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
    this->current = this->current->right;

    return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
    if(!this->current->r_thread){
        this->current = this->current->right->findMin();
    }
    else {
        this->current = this->current->right;
    }
    return *this;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
    this->current = this->current->left;
    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
    if(!this->current->l_thread){
        this->current = this->current->left->findMax();
    }
    else {
        this->current = this->current->left;
    }
    return *this;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
