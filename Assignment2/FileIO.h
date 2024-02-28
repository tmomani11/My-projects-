/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-02
 * Assignment 2: Not So Super Mario Bros.
 */
#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <fstream>

class FileIO{
    private:
        std::ofstream m_log;    //the  file to write out to
        char* m_outputFileName; //the filename used for output
        
    public:
        FileIO();
        FileIO(char* outputFileName);
        virtual ~FileIO();

        static bool readFile(char* fileName, int* specs, int numSpecs);
        void displayLevel(char** level, int lvlNum, int gridDim);
        void writeToLog(int lvlNum, int* pos, int powerLevel, std::string action, int numLives,
                        int numCoins, int* nextDir, bool isStaying, char** level, int gridDim);
        void writeLogEnd(char state, int steps);
};
#endif