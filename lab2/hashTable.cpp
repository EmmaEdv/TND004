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
 : h(f), MAX_LOAD(ml) //MAX_LOAD is the limit of items in the collision list!
{
    nItems = 0;
    for (int i = 0; i<nextPrime(tableSize); i++){
        list<Item*> temp;
        theLists.push_back(temp);
    }
}


//Empty the table
//The Items stored in the collison lists are deleted and the lists are emptied
//TO IMPLEMENT
void HashTable::makeEmpty()
{
    for (int i = 0; i < theLists.size(); i ++) {
        //Aida: it leaks memory
        //walk through the lists and delete teh items
        while(!theLists[i].empty()){
            theLists[i].pop_front();
        }

    }
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
    return (double) nItems/theLists.size();
}


//Rehashing function
//TO IMPLEMENT


void HashTable::reHash()
{
    cout << "** Re-hashing ..." << endl;
    cout << "Hash table load factor = "
        << fixed << setprecision(2)
        << loadFactor() << endl;

    //1. copy the old vector
    std::vector<list<Item*>> temp = theLists;
    //2. clear the old vector, assign the nItems to zero
    makeEmpty();
    nItems = 0;
    theLists.resize(nextPrime(2*temp.size()));
    for (int i=0; i < temp.size(); i++){
        //while there are more values in the copy, insert in the new and delete from the temporary
        while(!temp[i].empty()){
            auto itr = temp[i].front();
            this->insert(itr->word, itr->counter);
            temp[i].pop_front();
        }
    }

    //3. destruct the old, assign the new table as this(in some weird way)

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
    const list<Item*> whichList = theLists[h(x, theLists.size())];
    auto it = whichList.begin();

    while( it != whichList.end() )
    {
        Item* p = *it;
       if (p->word == x) return p;

       it++;
    }

    return nullptr;
}


//Insert item w with counter i into the hash table
//Return a pointer to the inserted item
//Assumes w is not in the table
//TO IMPLEMENT
Item* HashTable::insert(string w, short i)
{
    if(loadFactor() >= MAX_LOAD) {
        reHash();
    }
    Item *word = new Item(w,i);
    int number = h(w, theLists.size());

    theLists[number].push_front(word);

    ++nItems;
    return word;
}


//Remove item w from the hash table
//If w belongs to the table then return true,
//otherwise, return false
//TO IMPLEMENT
bool HashTable::remove(string w)
{
     Item* itr = find(w);
     if (!itr){
         return false;
     }
     theLists[h(w,theLists.size())].list::remove(itr);

     delete itr;
     --nItems;

     return true;
 }


//Overloaded operator<<: outputs all items to stream os
//TO IMPLEMENT
ostream& operator <<(ostream& os, const HashTable& T)
{
    os << "Size = " << T.theLists.size() << endl <<
    "Number of items in the table = " << T.nItems << endl << endl;

    for (int i=0; i < T.theLists.size(); i++){
       auto itr = T.theLists[i].begin();
       os << "**List[" << i << "]" << endl;
        while (itr != T.theLists[i].end()){
            const Item *p = *itr;
            operator<<(os, *p);// call the ostream operator for Item
            itr++;
        }
    }
    os << endl << endl;
    return os;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

