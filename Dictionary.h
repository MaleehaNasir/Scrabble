#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
using namespace std;

class Dictionary {
private:
    string* words;        
    int wordCount;        
    int maxWords;      

public:
    Dictionary();
    ~Dictionary();
    
    bool loadDictionary(string filename);
    
    bool ValidWord(string word);

    int getWordCount();
};

#endif