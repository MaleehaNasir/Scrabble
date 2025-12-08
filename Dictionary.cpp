#include "Dictionary.h"
#include <fstream>
#include <iostream>
using namespace std;

Dictionary::Dictionary() {
    maxWords = 2000000; 
    words = new string[maxWords];
    wordCount = 0;
}

Dictionary::~Dictionary() {
    delete[] words;
} 

bool Dictionary::loadDictionary(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    string word;
    wordCount = 0;
    while (getline(file, word) && wordCount < maxWords) {
        for (int i = 0; i < word.length(); i++) {
            if (word[i] >= 'a' && word[i] <= 'z') {
                word[i] = word[i] - 32;  
            }
        }
        
        words[wordCount] = word;
        wordCount += 1;
    }
    
    file.close();
    return true;
}

bool Dictionary::ValidWord(string word) { 
    if (wordCount <2) {
        return false;
    }
    if (word.empty() || word.length() > 15) { 
        return false;
    }
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - 32;
        }
    }

    int left = 0;
    int right = wordCount - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (words[mid] == word) {
            return true;  
        }
        else if (words[mid] < word) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    
    return false; 
}

int Dictionary::getWordCount() {
    return wordCount;
}

