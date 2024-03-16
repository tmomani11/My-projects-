#include "FileIO.h"
#include <string>
#include <iostream>

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
    log.open(outputFile, std::ios::trunc);
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
 */
bool FileIO::readFile(char* fileName, int* specsHolder){
    std::ifstream fileIn;
    std::string line = "";
    int i = 0;
    fileIn.open(fileName, std::ios::in);

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
    log.open(outputFile, std::ios::app);
    log << "*=======================================*\n";
    log << "*              Level Number " << lvlNum  << "           *" <<'\n';
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
 * Writes the current state of the game to the log file.
 * Parameters:
 *   int lvlNum: The current level number.
 *   int* pos: A pointer to an array containing the current position of Mario.
 *   int powerLevel: The current power level of Mario.
 *   const std::string& action: The action that Mario has just performed.
 *   int numLives: The current number of lives Mario has.
 *   int numCoins: The current number of coins Mario has collected.
 *   const int* nextDir: A pointer to an array containing the next direction of Mario.
 *   bool isStaying: A boolean indicating whether Mario is staying put or not.
 *   char** level: A 2D array representing the current level.
 *   int gridDim: The dimension of the grid of the current level.
 */
void FileIO::writeToLog(int lvlNum, int* pos, int powerLevel, const std::string& action, int numLives,
                        int numCoins, const int* nextDir, bool isStaying, char** level, int gridDim){
    // Open the log file in append mode
    log.open(outputFile, std::ios::app);

    // Write the current state of the game to the log file
    log << "=======================================\n";
    log << "Level Number " << lvlNum  << " \n";
    log << "Mario is at (" << pos[1] + 1 << ','<<pos[0] + 1 << ") \n";
    log << "Power level " << powerLevel << " \n";
    log << action << " ";
    if (numLives == 1) {
        log  << std::endl << numLives << " life";
    } else {
        log << std::endl << numLives << " lives";
    }
    log << " left ";
    if (numCoins == 1) {
        log << std::endl << numCoins << " coin";
    } else {
        log << std::endl << numCoins << " coins";
    }
    log << std::endl;

    // Write Mario's next move if he still has lives
   std::string dir;
if (isStaying) {
    dir = "STAY PUT";
} else {
    if (nextDir[0] == 0) {
        if (nextDir[1] == 1) {
            dir = "DOWN";
        } else {
            dir = "UP";
        }
    } else {
        if (nextDir[1] == 1) {
            dir = "RIGHT";
        } else {
            dir = "LEFT";
        }
    }
}
        log << "Mario's next move: " << dir << "\n";
    
    log << "=======================================\n";

    // Write the current level to the log file
    for(int i = 0; i < gridDim; ++i){
        for (int j = 0; j < gridDim; ++j){
            log << level[i][j] << " ";
        }
        log << '\n';
    }
    log << '\n';

    // Close the log file
    log.close();
}


/* writeLogEnd()
 * Writes out the state of the game after completion to the log
 * Parameters:
 *   char state: If the game was won or lost
 *   int moves: The number of moves taken by Mario during the simulation
 */
void FileIO::writeLogEnd(std::string state, int moves){
    log.open(outputFile, std::ios::app);
    if(state == "lost"){
        log << "Mario lost better luck next time  ";
    } else if(state == "win"){
        log << "Mario Won! :). ";
    } else {
        log << "Don't know what happened";
    }
    log << "Total steps taken: " << moves ;
    log.close();
}