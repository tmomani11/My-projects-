/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-01
 * Assignment 1: Robber Language Translation
 */

#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include "Model.h"
#include <string>
class Translator{
    public:
        Translator();           //constructor
        virtual ~Translator();  //destructor

        //Public methods
        static std::string translateEnglishWord(std::string word);
        static std::string translateEnglishSentence(std::string sentence);

private:
    static bool isVowel(char c);


};
#endif