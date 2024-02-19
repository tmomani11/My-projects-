/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-01
 * Assignment 1: Robber Language Translation
 */

#include "Translator.h"
#include <string>
#include <cctype>
using namespace std;

Translator::Translator(){}
Translator::~Translator(){}

/* translateEnglishWord()
 * Takes an English word and translates it based of model class
 * Return: A string encoded based on requirements
 * Parameters: 
 *  string word: the word to be translated
 */
string Translator::translateEnglishWord(string word){
    string result;
    for(char i : word){
        char let = tolower(i);
        if(isalpha(let)){
            if(Translator::isVowel(let)){
                result += Model::translateSingleVowel(i);
            }
            else{
                result += Model::translateSingleConsonant(i);
            }
        }
        else{
            //character not changed if not vowel or Constant
            result += i;
        }
    }
    return result;
}

/* translateEnglishSentence()
 * translates a sentence or multiple based on model class
 * Return: A string containing the translated sentence
 * Parameters: 
 *  string sent: the sentence to be translated
 */
string Translator::translateEnglishSentence(string sentence){
    string result;
    string word;
    //keep adding letters until non letter is detected \n or !
    for(char i : sentence){  // same thing as for (int i =0 ; i<sentence.length();i++)
        if(isalpha(i)){
            word.push_back(i);
        }
        else{
            result += translateEnglishWord(word) + i;
            word.clear();
        }
    }
    if(isalpha(sentence[sentence.length() - 1])){
        result += translateEnglishWord(word);
    }
    return result;
}

bool Translator::isVowel(char c) {
    // Check if the character is a vowel ,checks both lower and uppercase
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ||
            c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}


