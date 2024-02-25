#include "Translator.h"
#include <string>
#include <cctype>
using namespace std;

Translator::Translator() {
    myModel = new Model();
}  // default constructor
Translator::~Translator() {
    delete myModel;
}  // default destructor

/*
 * The translateEnglishWord function takes an English word and translates it based on the Model class.
 *
 * @param word: The word to be translated.
 * @return: A string encoded based on Rövarspråket rules.
 */
string Translator::translateEnglishWord(string word){
    string result;
    for(int i = 0; i < word.length(); ++i){
        char let = tolower(word[i]);
        if(isalpha(let)){
            if(isVowel(let)){
                result += myModel->translateSingleVowel(word[i]);
            }
            else{
                result += myModel->translateSingleConsonant(word[i]);
            }
        }
        else{
            //character not changed if not vowel or constant
            result += i;
        }
    }
    return result;
}

/*
 * The translateEnglishSentence function translates a sentence or multiple sentences based on the Model class.
 *
 * @param sentence: The sentence to be translated.
 * @return: A string containing the translated sentence.
 */
string Translator::translateEnglishSentence(string sentence){
    string result;
    string word;
    for (int i = 0; i < sentence.length(); ++i){
        if (isalpha(sentence[i])) {
            word.push_back(sentence[i]);
        } else {
            result += translateEnglishWord(word);
            result += sentence[i]; // include non-alphabetic character
            word.clear();
        }
    }
    result += translateEnglishWord(word); // include the last word
    return result;
}
/*
 * The isVowel function checks if a character is a vowel.
 *
 * @param c: The character to be checked.
 * @return: True if the character is a vowel, false otherwise.
 */
bool Translator::isVowel(char c) {
    c = tolower(c);
    // Check if the character is a vowel ,checks both lower and uppercase
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}


