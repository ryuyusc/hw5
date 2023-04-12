#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void fillset(std::set<std::string>& words, 
            const std::string& in, 
            const std::string& floating,
            const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> ans;
    fillset(ans, in, floating, dict);
    return ans;
}

// Define any helper functions here
void fillset(std::set<std::string>& words, 
            const std::string& in, 
            const std::string& floating,
            const std::set<std::string>& dict) {
    //case in which a word is completed and 
    //added only if it exists in dict
    if (in.find('-') == string::npos) {
        if (dict.find(in) != dict.end()) {
            words.insert(in);
        }
    }
    else {
        size_t index = in.find('-');
        //recurses through floating letters first
        for (size_t i = 0; i < floating.size(); i++) {
            string newString(in);
            string s(1, floating[i]);
            newString.replace(index, 1, s);

            string newFloating(floating);
            newFloating.erase(i, 1);
            fillset(words, newString, newFloating, dict);
        }

        //recurses through the letters of the alphabet
        int numLetters = 0;
        for (size_t i = 0; i < in.size(); i++) {
            if (in[i] != '-') {
                numLetters++;
            }
        }
        if (numLetters + floating.size() < in.size()) {
            for (size_t i = 0; i < 26; i++) {
                string temp(1, 'a' + i);
                string newString(in);
                newString.replace(index, 1, temp);
                fillset(words, newString, floating, dict);
            }
        }
    }
}