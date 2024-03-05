#include "FileIO.h"
#include <string>
#include <iostream>
using namespace std;

//Constructors & Destructor

/* FileIO()
 * Default constructor
 */
FileIO::FileIO(){
    m_outputFileName = nullptr;
}

/* FileIO()
 * Overloaded constructor: clears the log file for new data
 * Parameters:
 *   char* outputFileName: The name of the log file
 */
FileIO::FileIO(char* outputFileName){
    m_outputFileName = outputFileName;
    m_log.open(m_outputFileName, ios::trunc);
    m_log.close();

}

/* ~FileIO()
 * Destructor: closes the log if not already closed
 */
FileIO::~FileIO(){
    if(m_log.is_open()){
        m_log.close();
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
    bool success = true;
    ifstream fileIn;
    string m_line = "";
    int i = 0;
    fileIn.open(fileName, ios::in);

    if(!(fileIn.is_open())){
        success = false;
    }
    else{
        while(getline(fileIn, m_line)){
            specsHolder[i++] = stoi(m_line);
        }
        fileIn.close();
    }
    return success;
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
    m_log.open(m_outputFileName, ios::app);

    m_log << "Level Number " << lvlNum + 1 << '\n';

    for(int i = 0; i < gridDim; ++i){
        for (int j = 0; j < gridDim; ++j){
            m_log << level[i][j] << " ";
        }
        m_log << '\n';
    }
    m_log << '\n';

    m_log.close();
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
    m_log.open(m_outputFileName, ios::app);
    m_log << "=======================================\n";
    m_log << "Level Number " << lvlNum + 1 << ", \n";
    m_log << "Mario is at (" << pos[1] + 1 << "," << pos[0] + 1 << ") \n";
    m_log << "Power level " << powerLevel << " \n";
    m_log << action << ", "
          << numLives << ((numLives == 1) ? " life" : " lives") << " left, "
          << numCoins << ((numCoins == 1) ? " coin" : " coins");
    m_log << endl;



    if(numLives > 0){
        string dir = isStaying ? "STAY PUT" : ((nextDir[0] == 0) ?
                                                    ((nextDir[1] == 1) ? "DOWN" : "UP") :
                                                    ((nextDir[1] == 1) ? "RIGHT" : "LEFT"));
        m_log << "Mario's next move: " << dir << ".\n";

    }
    m_log << "=======================================\n";

    for(int i = 0; i < gridDim; ++i){
        for (int j = 0; j < gridDim; ++j){
            m_log << level[i][j] << " ";
        }
        m_log << '\n';
    }
    m_log << '\n';

    m_log.close();

}


/* writeLogEnd()
 * Writes out the state of the game after completion to the log
 * Parameters:
 *   char state: If the game was won or lost
 *   int moves: The number of moves taken by Mario during the simulation
 */
void FileIO::writeLogEnd(char state, int moves){
    m_log.open(m_outputFileName, ios::app);
    switch(state){
        case 'l':
            m_log << "Mario lost :( . ";
            break;
        case 'w':
            m_log << "Mario Won! :). ";
            break;
        default:
            m_log << "Don't know what happened";
            break;
    }
    m_log << moves << " steps" << " taken." << endl;
    m_log.close();
}
