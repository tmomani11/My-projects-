#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <fstream>

class FileIO{
    private:
        std::ofstream log;    //the  file to write out to
        char* outputFile; //the filename used for output

    public:
        FileIO();
        FileIO(char* outputFileName);
        virtual ~FileIO();

        bool readFile(char* fileName, int* specs);
        void displayLevel(char** level, int lvlNum, int gridDim);
        void writeToLog(int lvlNum, int* pos, int powerLevel, const std::string& action, int numLives,
                        int numCoins, const int* nextDir, bool isStaying, char** level, int gridDim);
        void writeLogEnd(std::string state, int steps);

    };
#endif