/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-02
 * Assignment 2: Not So Super Mario Bros.
 */

#include "World.h"
#include "Mario.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

//Constructors & Destructor

/* World()
 * Default constructor
 * Return: 
 *   n/a
 * Parameters: 
 *   n/a
 */
World::World(){
    srand(time(0));

    m_player = nullptr;
    m_worldLog = nullptr;
    m_numLevels = 0;
    m_gridDim = 0;
    m_marioLives = 0;
    m_cP = m_nP = m_gP = m_kP = m_mP = 0;
    m_outputFileName = nullptr;
    m_world = nullptr;
}

/* World()
 * Overloaded constructor: builds the world based on specifications
 * Parameters: 
 *   int* specs: The specs given on how to build the world
 *   char* outputFileName: The filename of the log
 */
World::World(int* specs, char* outputFileName){
    srand(time(0));

    m_numLevels = specs[0];
    m_gridDim = specs[1];
    m_marioLives = specs[2];
    m_cP = specs[3];
    m_nP = specs[4];
    m_gP = specs[5];
    m_kP = specs[6];
    m_mP = specs[7];
    m_outputFileName = outputFileName;

    m_player = new Mario(m_marioLives, m_numLevels);
    m_worldLog = new FileIO(outputFileName);
}

/* World()
 * Destructor: deallocated the world & player
 */
World::~World(){
    if(m_world != nullptr){
        for(int i = 0; i < m_numLevels; ++i) {
            for(int j = 0; j < m_gridDim; ++j){
                delete[] m_world[i][j];
            }
            delete[] m_world[i];
        }
        delete[] m_world;
    }
        delete m_player;

}

//Private Methods

/* generateWorld()
 * Creates every level of the world

 */
bool World::generateWorld(){
    bool success = true;

    if(m_gridDim < 2){
        cout << "The grid is too small to populate!" << endl;
        success = false;
    }
    else{
        //Initializing each level in the world
        m_world = new char**[m_numLevels];
        for(int i = 0; i < m_numLevels; ++i){

            m_world[i] = new char*[m_gridDim];
            for(int j = 0; j < m_gridDim; ++j){
                m_world[i][j] = new char[m_gridDim];

                for(int k = 0; k < m_gridDim; ++k){
                    m_world[i][j][k] = generateSquare();
                }
            }

            //After filling out the grid, add only one of each Mario, boss, and warp pipe
            int numPipes = 1;
            if(i == m_numLevels - 1){
                numPipes = 0;
            }
            char items[3] = {'H', 'b', 'w'};
            for(int l = 0; l < 2 + numPipes; ++l){
                int coords[2] = {rand() % m_gridDim, rand() % m_gridDim};
                while(m_world[i][coords[0]][coords[1]] == 'H' || 
                      m_world[i][coords[0]][coords[1]] == 'b' || 
                      m_world[i][coords[0]][coords[1]] == 'w'){
                    coords[0] = rand() % m_gridDim;
                    coords[1] = rand() % m_gridDim;
                }
                m_world[i][coords[0]][coords[1]] = items[l];

                if(items[l] == 'H'){
                    m_player->setPos(i, coords[0], coords[1]);
                }
            }
        }
    }

    return success;
}

/* generateSquare()
 * Generates a random character based on the percentages given in the spec file
 * Return: 
 *   char: A random character (c, x, g, k, m)
 */
char World::generateSquare(){
    int spotRNG = rand() % 100 + 1;
    char result  = '\0';

    if(spotRNG <= m_cP){
        result = 'c';
    }
    else if(spotRNG <= (m_cP + m_nP)){
        result = 'x';
    }
    else if(spotRNG <= (m_cP + m_nP + m_gP)){
        result = 'g';
    }
    else if(spotRNG <= (m_cP + m_nP + m_gP + m_kP)){
        result = 'k';
    }
    else if(spotRNG <= (m_cP + m_nP + m_gP + m_kP + m_mP)){
        result = 'm';
    }

    return result;

}

/* playLevel()
 * Plays a single level repeatedly until Mario dies or can move on
 * Return: 
 *   bool: If Mario can move onto the next level or not
 * Parameters: 
 *   int levelNum: The level to play
 */
bool World::playLevel(int levelNum) {
    bool levelComplete = false;
    m_player->setLevel(levelNum);

    while (m_player->isAlive() && !levelComplete) {
        int powerLevelBeforeMove = m_player->getPowerLevel();
        levelComplete = m_player->move(m_world[levelNum], m_gridDim);

        m_worldLog->writeToLog(levelNum,
                               m_player->getPosAtLevel(levelNum),
                               powerLevelBeforeMove,
                               m_player->getAction(),
                               m_player->getLives(),
                               m_player->getCoins(),
                               m_player->getNextMove(),
                               m_player->isStaying(),
                               m_world[levelNum],
                               m_gridDim);
    }

    return levelComplete;
}

//Public Methods

/* start()
 * Starts the Mario simulation
 * Return: 
 *   bool: If the simulation was able to start
 */
bool World::start(){
    bool success = true;
    cout << "\nWelcome to Not So Super Mario Bros! " << endl;
    if(!generateWorld()){
        cout << "World generation unsuccessful." << endl;
        success = false;
    }
    else{
        cout << "World generation successful! Beginning  simulation...\n   ";
        for(int i = 0; i < m_numLevels; ++i){
            m_worldLog->displayLevel(m_world[i], i, m_gridDim);
            if(!playLevel(i) && !(m_player->isAlive())){
                m_worldLog->writeLogEnd('l', m_player->getTotalSteps());
                break;
            }
        }
        if(m_player->isAlive()){
            m_worldLog->writeLogEnd('w', m_player->getTotalSteps());
        }
        cout << "\n\nSimulation Terminating! " << endl;
    }

    return success;
}