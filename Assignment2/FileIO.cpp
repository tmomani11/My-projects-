#include "FileIO.h"
#include <string>
#include <iostream>
using namespace std;

//Constructors & Destructor

/* FileIO()
 * Default constructor
 */
FileIO::FileIO(){
    outputFile = nullptr;
}

/* FileIO()
 * Overloaded constructor: clears the log file for new data
 * Parameters:
 *   char* outputFileName: The name of the log file
 */
FileIO::FileIO(char* outputFile){
    this->outputFile = outputFile;
    log.open(outputFile, ios::trunc);
    log.close();

}

/* ~FileIO()
 * Destructor: closes the log if not already closed
 */
FileIO::~FileIO(){
    if(log.is_open()){
        log.close();
    }
}


/* readFile()
 * Reads a file with integer specifications seperated by line breaks for the Mario simulation
 * Return:
 *   bool: Returns if reading the file was successful or not
 * Parameters:
 *   char* fileName: The name of the file to read from
 *   int* specsHolder: The memory address of the array to populate with the int specs
 *   int numOfSpecs: The number of specifications in the file
 */
bool FileIO::readFile(char* fileName, int* specsHolder){
    ifstream fileIn;
    string line = "";
    int i = 0;
    fileIn.open(fileName, ios::in);

    if(!(fileIn.is_open())){
        throw std::runtime_error("Failed to open file");
    }
    else{
        while(getline(fileIn, line)){
            specsHolder[i++] = stoi(line);
        }
        fileIn.close();
    }
    return true;
}

//Public Methods

/* displayLevel()
 * Writes out an NxN grid of chars representing a level to the log
 * Parameters:
 *   char** level: The level to display
 *   int lvlNum: The number of the level being displayed
 *   int gridDim: The dimensions of the level
 */
void FileIO::displayLevel(char** level, int lvlNum, int gridDim){
    log.open(outputFile, ios::app);
    log << "*=======================================*\n";
    log << "*              Level Number " << lvlNum  << "         *" <<'\n';
    log << "*=======================================*\n";

    for(int i = 0; i < gridDim; ++i){
        for (int j = 0; j < gridDim; ++j){
            log << level[i][j] << " ";
        }
        log << '\n';
    }
    log << '\n';
    log.close();
}

/* writeToLog()
 * Writes out the state of a round to the log
 * String is used for action due to its variable size (the various actions Mario takes have different string lengths)
 * Parameters:
 *   int lvlNum: The number of the level being played
 *   int* pos: Mario's position
 *   int powerLevel: Mario's power level
 */
void FileIO::writeToLog(int lvlNum, int* pos, int powerLevel, const string& action, int numLives,
                        int numCoins, const int* nextDir, bool isStaying, char** level, int gridDim){
    log.open(outputFile, ios::app);
    log << "=======================================\n";
    log << "Level Number " << lvlNum  << ", \n";
    log << "Mario is at (" << pos[1] + 1 << "," << pos[0] + 1 << ") \n";
    log << "Power level " << powerLevel << " \n";
    log << action << ", "
          << numLives << ((numLives == 1) ? " life" : " lives") << " left, "
          << numCoins << ((numCoins == 1) ? " coin" : " coins");
    log << endl;



    if(numLives > 0){
        string dir = isStaying ? "STAY PUT" : ((nextDir[0] == 0) ?
                                                    ((nextDir[1] == 1) ? "DOWN" : "UP") :
                                                    ((nextDir[1] == 1) ? "RIGHT" : "LEFT"));
        log << "Mario's next move: " << dir << ".\n";

    }
    log << "=======================================\n";

    for(int i = 0; i < gridDim; ++i){
        for (int j = 0; j < gridDim; ++j){
            log << level[i][j] << " ";
        }
        log << '\n';
    }
    log << '\n';

    log.close();

}

/* writeLogEnd()
 * Writes out the state of the game after completion to the log
 * Parameters:
 *   char state: If the game was won or lost
 *   int moves: The number of moves taken by Mario during the simulation
 */
void FileIO::writeLogEnd(string state, int moves){
    log.open(outputFile, ios::app);
    if(state == "lost"){
        log << "Mario lost :( . ";
    } else if(state == "win"){
        log << "Mario Won! :). ";
    } else {
        log << "Don't know what happened";
    }
    log << moves << " steps" << " taken." << endl;
    log.close();
}