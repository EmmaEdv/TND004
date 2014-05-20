/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
using namespace std;


//
bool isNotAlpha(char c)
{
    //Gör en egen sån hära där vissa tecken är tillåtna. t ex - ´'
    return ispunct(c);
}

/*******************************
* 2. Main function             *
********************************/


int main()
{
    MAP table;

    string name;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile(name.c_str());

    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        return 0;
    }

    string word;
    int nWords = 0;

    while(textFile >> word)
    {
        nWords++;
        //remove non-alpha chars
        word.erase(remove_if(word.begin(), word.end(), isNotAlpha), word.end());
        //convert to lower-case letters
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word == "") continue;

        ELEMENT e = make_pair(word,1);
        cout << word << endl;
        table.BST_threaded::insert(e);
    }

    textFile.close();

    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/
    //number of words in the text
    cout << "The number of words in the text file is: " << nWords << endl;
    cout << "Number of unique words in the file: " << table.size() << endl;

    cout << "\n\nTable sorted alphabetically:"
         << endl << endl;

    BiIterator it = table.begin();

    cout << "  \tKEY" << "\tCOUNTER" << endl;
    cout << "==============================\n";
    for( ; it != table.end(); it++)
    {
         cout << setw(15) << it->first
              << setw(15) << it->second << endl;
    }


    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    it = table.begin();
    cout << endl << endl << "nya coola saker!!!!!" << endl << endl;
    for( ; it != table.end(); it++){
        if(it->second == 1){
           // cout << "I am removing " << it->first << " which occurs " << it->second << " times" << endl;
            table.remove(it->first);

        }
    }


    cout << "Number of words after remove: " << table.size() << endl;

    cout << "Un-unique table sorted alphabetically:" << endl;

    cout << "  \tKEY" << "\tCOUNTER" << endl;
    cout << "==============================\n";
    for(it = table.begin(); it != table.end(); it++) {
         cout << setw(15) << it->first
              << setw(15) << it->second << endl;
    }


    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

//    string wait;
//    getline(cin, wait);

    //ADD CODE



    return 0;
}
