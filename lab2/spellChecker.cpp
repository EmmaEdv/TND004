#include "spellChecker.h"

#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

/** \brief Hash function for English words
*
* \note Polynomial accumulation is used. See pag. 213 of course book.
* \param s a string (word).
* \param tableSize an integer representing the size of the hash table.
* \return unsigned int representing the hash value of s (overlow is allowed).
*
*/
//Hash function for English words
//Polynomial accumulation
//the Horner's rule is used to compute the value
//See pag. 213 of course book
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(int i= 0; i < s.length(); i++)
        hashVal= 37 * hashVal + s[i];

    hashVal %= tableSize;

    return hashVal;
}


bool isNotAlpha(char c)
{
    return !isalpha(c);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//Constructor
//Text file fileName should contain a dictionary with n words
//TO IMPLEMENT
SpellChecker::SpellChecker(string fileName, int n)
{
    //1. create a hashtable with the given number of slots
    HashTable* dictionary = new HashTable(n, my_hash, 2);

    //2. insert words from the text file into the hash table

    //open ifstream
    ifstream file(fileName.c_str());
    //cout << fileName << endl;

    if (!file){
        cerr << "Dictionary file could not be opened!!" << endl;
        exit(1);
    }

    //load the dictionary
    string w;

    while(file >> ws && getline(file, w))
    {
        dictionary->HashTable::insert(w,0);
    }
    file.close();

    list<Item *> misspellings;
    list<Item *> addedWords;
}


//Destructor
//TO IMPLEMENT
SpellChecker::~SpellChecker()
{
    dictionary->HashTable::~HashTable();
    cout << "** Spell Checker Destructor" << endl;
}


//Test whether word w is in the dictionary
//If w is a correct word (belongs to the dictionary) then return true, else return false
//If w is a misspelling then the dictionary and
//the misspeling list might need to be updated
//TO IMPLEMENT
bool SpellChecker::testSpelling(string w)
{
    //remove non-alpha chars
    w.erase(remove_if(w.begin(), w.end(), isNotAlpha), w.end());

    //convert to lower-case letters
    transform(w.begin(), w.end(), w.begin(), ::tolower);
    //cout << w << endl;
    //if (w == "") return true; //case of a word consisting only of punctuation signs
    //ADD CODE

//1. if the word exist in the dictionary -> return true

//2. if it not exists in the dictionary -> check if it exists in the misspellings

//3. if the word exists in the misspellings, ++ their counter -> return false

//4. if it not exists, add the word to misspellings and set the counter to 1. -> return false

//    return nullptr;
//
//    if(w[0] == 'a'){
//        Item* temp = new Item(w, 0);
        misspellings.push_back(new Item(w,0));
//    }
//    return (w[0] == 'a');
//    return false;

    return true;
}


//Add a new word w to the dictionary
//The list of addedWords is also updated
//TO IMPLEMENT
void SpellChecker::addWord(string w)
{
    //remove non-alpha chars
    w.erase(remove_if(w.begin(), w.end(), isNotAlpha), w.end());

    //convert to lower-case letters
    transform(w.begin(), w.end(), w.begin(), ::tolower);
    //1. check if the word  exists in the dictionary

    //2. if it not exists: add the word to the dictionary with counter 0
    //3. and add the word and the counter 0 to addedWords
    Item *p = dictionary->HashTable::insert(w,0);
    this->addedWords.push_back(new Item(w, 0));
    cout << "added " << w << " -> size of addedWords = " << addedWords.size() << endl;
}


//Remove all extra added words from the dictionary
//This function can be called before starting to spell check a new text file
//TO IMPLEMENT
void SpellChecker::clean()
{
    //loop trough the addedWords list and remove them from the dictionary by using
    //iterators to access the key for the item to be removed (word)
    for(auto itr = addedWords.front(); itr!=addedWords.back(); itr++){
        dictionary->HashTable::remove(itr->word);
    }
}


//1. Create the log file with the misspellings
//2. Empty the misspellings list
//TO IMPLEMENT -> this works fine
void SpellChecker::createLog(ostream& os)
{
    os << "*** LIST OF MISSPELLINGS" << endl;
    os << "=========================" << endl;

    //ADD CODE
    ofstream logFile("log.txt");

    while(!misspellings.empty()) {
        auto itr = misspellings.front();
        os << setw(25) << itr->word
       << "   Counter: " << itr->counter << endl;
       misspellings.pop_front();

    }
    logFile.close();

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
