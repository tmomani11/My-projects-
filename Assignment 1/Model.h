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
        Model();//constructor
        virtual ~Model();//destructor

        static std::string translateSingleConsonant(char c);
        static std::string translateSingleVowel(char c);

private:
        static bool CheckConsonant(char c);
};
#endif