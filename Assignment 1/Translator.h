#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include "Model.h"
#include <string>

// The Translator class provides static methods for translating English words and sentences into Rövarspråket.
class Translator{
public:
    Translator();           // Default constructor
    virtual ~Translator();  // Virtual destructor

    // Translates an English word into Rövarspråket.
    // @param word The English word to translate.
    // @return The translated word in Rövarspråket.
     std::string translateEnglishWord(std::string word);

    // Translates an English sentence into Rövarspråket.
    // @param sentence The English sentence to translate.
    // @return The translated sentence in Rövarspråket.
     std::string translateEnglishSentence(std::string sentence);

private:
    // Checks if a character is a vowel.
    // @param c The character to check.
    // @return True if the character is a vowel, false otherwise.
     bool isVowel(char c);
};
#endif