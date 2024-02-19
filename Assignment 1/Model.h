/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-02
 * Assignment 1: Robber Language Translation
 */

#ifndef MODEL_H
#define MODEL_H

#include <string>
class Model{
    public:
    Model(); // Default constructor
    virtual ~Model(); // Virtual destructor

    // Translates a single consonant character.
    // @param c The consonant to translate.
    // @return The translated consonant as a string.
    static std::string translateSingleConsonant(char c);

     // Translates a single vowel character.
    // @param c The vowel to translate.
    // @return The translated vowel as a string.
    static std::string translateSingleVowel(char c);

private:
    // Checks if a character is a consonant.
    // @param c The character to check.
    // @return True if the character is a consonant, false otherwise.
    static bool CheckConsonant(char c);
};
#endif