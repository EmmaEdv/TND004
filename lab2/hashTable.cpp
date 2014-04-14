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
        theLists[i].clear();
    }
}


//destructor
HashTable::~HashTable()
{
    makeEmpty();

    nItems = 0;

    //cout << "** Hash Table Destructor" << endl;
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
    const list<Item*> whichList = theLists[h(x, theLists.size())];
    auto it = whichList.begin();

    while( it != whichList.end() )
    {
        Item* p = *it;
       if (p->word == x) return p;

       it++;
    }

    return nullptr;

//   return (std::find(whichList.begin(), whichList.end(), x) != whichList.end());
//   unsigned int number = h(x, theLists.size());
//
//   Item *pointis = theLists[number].front();
//
//    cout << "numbah iz: " << number << " and the word iz: " << x << endl;
//
//    if(theLists[number].size() != 0){
//        while (pointis->word != ""){
//           if (pointis->word == x){
//                cout << "I found it!! " << x << endl;
//                return pointis;
//           }
//            else
//                ++pointis;
//       }
//
//    }
//    cout << "I did not find "<< x << endl;
//    return NULL;
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
   //cout << "I insert "<< w << endl;

   ++nItems;

   return word;
}


//Remove item w from the hash table
//If w belongs to the table then return true,
//otherwise, return false
//TO IMPLEMENT
bool HashTable::remove(string w)
{
    list<Item*> current = theLists[h(w, theLists.size())];
    Item* itr = find(w);

    if (!itr){
        return false;
    }

    current.list::remove(itr);  //??

    delete itr;
    --nItems;

    return true;
}


//Overloaded operator<<: outputs all items to stream os
//TO IMPLEMENT
ostream& operator <<(ostream& os, const HashTable& T)
{

    for (int i=0; i < T.theLists.size(); i++){
        Item* itr = T.theLists[i].front();
        while (itr != T.theLists[i].back()){
            //os << itr->word << " " << "counter : " << itr->counter << endl;
            //os << "hello, my name is Emma and my counter is 2" << endl;
            os << itr << endl;
            ++itr;
        }
    }
    return os;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

