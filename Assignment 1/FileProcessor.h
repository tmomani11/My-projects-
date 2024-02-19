/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-01
 * Assignment 1: Robber Language Translation
 */
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Translator.h"
#include <string>

class FileProcessor{
    public:
        FileProcessor();
        virtual~FileProcessor();
        void processFile(std::string inputFile,std::string outputFile);

    private:

};

#endif