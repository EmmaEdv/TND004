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
//IMPLEMENTED - works fine!
SpellChecker::SpellChecker(string fileName, int n)
{
    //1. create a hashtable with the given number of slots
    dictionary = new HashTable(n, my_hash, 2);

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

    nWords = n;
}


//Destructor
//TO IMPLEMENT
SpellChecker::~SpellChecker()
{
    //destroy the dictionary
    delete dictionary;

     misspellings.clear();
     addedWords.clear();

    //empty the misspellings
//    for(int i = 0; i < misspellings.size(); i++){
//        while(!misspellings.empty()){
//            misspellings.pop_front();
//        }
//    }



    //empty the addedWords
//    for(int i = 0; i < addedWords.size(); i++){
//        while(!addedWords.empty()){
//            addedWords.pop_front();
//        }
//    }
    nWords = 0;

    cout << "** Spell Checker Destructor" << endl;
}


//Test whether word w is in the dictionary
//If w is a correct word (belongs to the dictionary) then return true, else return false
//If w is a misspelling then the dictionary and
//the misspeling list might need to be updated
//TO IMPLEMENT - unsuref...
bool SpellChecker::testSpelling(string w)
{
    //remove non-alpha chars
    w.erase(remove_if(w.begin(), w.end(), isNotAlpha), w.end());

    //convert to lower-case letters
    transform(w.begin(), w.end(), w.begin(), ::tolower);
    if (w == "") return true; //case of a word consisting only of punctuation signs

    //1. if the word exist in the dictionary -> return true
    //error is right here
    Item *h = dictionary->find(w);
    //cout << "get here" << endl;

    if(h){

        return true;
    }
    //2. if it does not exists in the dictionary -> check if it exists in the misspellings
    //3. if the word exists in the misspellings, ++ their counter -> return false
    else{

        auto itr = misspellings.begin();

        while( itr != misspellings.end()){
            Item* p = *itr;
            if (p->word == w) {
                p->counter+=1;
                //cout << p->word << " "<< p->counter << endl;
                return false;
            }
            itr++;
        }
        misspellings.push_front(new Item(w,1));
        cout << "added new misspelling: " << w << endl;
        return false;
    }


    return false;
}


//Add a new word w to the dictionary
//The list of addedWords is also updated
//TO IMPLEMENT - unsure.........
void SpellChecker::addWord(string w)
{
    //remove non-alpha chars
    w.erase(remove_if(w.begin(), w.end(), isNotAlpha), w.end());

    //convert to lower-case letters
    transform(w.begin(), w.end(), w.begin(), ::tolower);
    //1. check if the word exists in the dictionary
    Item *h = dictionary->find(w);
    //2. if it does not exists: add the word to the dictionary with counter 0
    //3. and add the word and the counter 0 to addedWords, increase the nWords
    if(!h){
        dictionary->insert(w,0);
        Item *p = dictionary->HashTable::insert(w,0); //returns nullptr?
        this->addedWords.push_back(new Item(w, 0));
        cout << "added " << w << endl;
        ++nWords;
    }
}


//Remove all extra added words from the dictionary
//This function can be called before starting to spell check a new text file
//TO IMPLEMENT - might work
void SpellChecker::clean()
{
    //loop trough the addedWords list and remove them from the dictionary by using
    //iterators to access the key for the item to be removed (word)
   auto itr = addedWords.begin();
   while(itr!=addedWords.end()){
        Item* p = *itr;
        dictionary->HashTable::remove(p->word);
        addedWords.pop_front(); //crash!
        itr++;
    }
    //addedWords.clear();
}


//1. Create the log file with the misspellings
//2. Empty the misspellings list
//YAY -> this works fine
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
