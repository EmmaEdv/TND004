#include "hashTable.h"

#include <iomanip>

#ifndef DOXYGEN_SHOULD_SKIP_THIS


/** \brief Test whether a number is a prime.
*
* \param n an integer.
* \pre true, if n is prime. Otherwise, return false.
*
*/
//function to test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


/** \brief Calculate the the next prime k such that k >= n .
*
* \param n an integer.
* \pre n is larger than zero.
* \pre a prime number larger or equal to n.
*/
//function to find a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


//constructor
//TO IMPLEMENT
HashTable::HashTable(int tableSize, HASH f, int ml)
 : h(f), MAX_LOAD(ml)
{
    nItems = 0;
    for (int i = 0; i<tableSize; i++){
        list<Item*> temp;
        theLists.push_back( temp);
    }
}


//Empty the table
//The Items stored in the collison lists are deleted and the lists are emptied
//TO IMPLEMENT
void HashTable::makeEmpty()
{
    //ADD CODE
}


//destructor
HashTable::~HashTable()
{
    makeEmpty();

    nItems = 0;

    cout << "** Hash Table Destructor" << endl;
}


//Return the load factor of the table
//TO IMPLEMENT
double HashTable::loadFactor() const
{

    return nItems/MAX_LOAD;
}


//Rehashing function
//TO IMPLEMENT
void HashTable::reHash()
{
    cout << "** Re-hashing ..." << endl;
    cout << "Hash table load factor = "
        << fixed << setprecision(2)
        << loadFactor() << endl;

    //ADD CODE

     cout << "** Re-hashing completed ..." << endl;
     cout << "Hash table load factor = "
          << fixed << setprecision(2)
          << loadFactor() << endl;
 }


//Return a pointer to the item that matches word w
//If w does not belong to the table then return nullptr
//TO IMPLEMENT
Item* HashTable::find(string x) const
{
   int number = h(x, theLists.size());
   Item *pointis = theLists[number].front();
   while (pointis != NULL){
        if(pointis->word == x){
            return pointis;
        }
        pointis++;
   }
   return NULL;
}


//Insert item w with counter i into the hash table
//Return a pointer to the inserted item
//Assumes w is not in the table
//TO IMPLEMENT
Item* HashTable::insert(string w, short i)
{
   int number = h(w, theLists.size());
   Item *word = new Item(w,i);
   theLists[number].push_back(word);

   return word;
}


//Remove item w from the hash table
//If w belongs to the table then return true,
//otherwise, return false
//TO IMPLEMENT
bool HashTable::remove(string w)
{
    int number = h(w, theLists.size());
    Item *pointis = theLists[number].front();
    while (pointis != NULL){
        if(pointis->word == w){
            pointis.erase(POSITIONEN!!!!!!!)
        }
        pointis++;
    }
    return false;
}


//Overloaded operator<<: outputs all items to stream os
//TO IMPLEMENT
ostream& operator <<(ostream& os, const HashTable& T)
{
   //ADD CODE
    return os;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

