#include "World.h"
#include "Mario.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

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

    player          = nullptr;
    worldLog        = nullptr;
    numLevels       = 0;
    gridDim         = 0;
    marioLives      = 0;
    coinChance      = 0;
    nothingChance   = 0;
    goombaChance    = 0;
    koopaChance     = 0;
    mushroomChance  = 0;
    outputFileName  = nullptr;
    world           = nullptr;
}

/* World()
 * Overloaded constructor: builds the world based on specifications
 * Parameters: 
 *   int* specs: The specs given on how to build the world
 *   char* outputFileName: The filename of the log
 */
World::World(int* specs, char* outputFileName){
    srand(time(0));

    numLevels = specs[0];
    gridDim = specs[1];
    marioLives = specs[2];
    coinChance = specs[3];
    nothingChance= specs[4];
    goombaChance = specs[5];
    koopaChance = specs[6];
    mushroomChance = specs[7];
    this->outputFileName = outputFileName;

    player = new Mario(marioLives, numLevels);
    worldLog = new FileIO(outputFileName);
}

/* World()
 * Destructor: deallocated the world & player
 */
World::~World(){
    if(world != nullptr){
        for(int i = 0; i < numLevels; ++i) {
            for(int j = 0; j < gridDim; ++j){
                delete[] world[i][j];
            }
            delete[] world[i];
        }
        delete[] world;
    }
        delete player;

}

//Private Methods

/* generateWorld()
 * Creates every level of the world

 */
bool World::generateWorld(){
    bool success = true;

    if(gridDim < 2){
        std::cout << "The grid is too small to populate!" << std::endl;
        success = false;
    }
    else{
        //Initializing each level in the world
        world = new char**[numLevels];
        for(int i = 0; i < numLevels; ++i){

            world[i] = new char*[gridDim];
            for(int j = 0; j < gridDim; ++j){
                world[i][j] = new char[gridDim];

                for(int k = 0; k < gridDim; ++k){
                    world[i][j][k] = generateSquare();
                }
            }

            //After filling out the grid, add only one of each Mario, boss, and warp pipe
            int numPipes = 1;
            if(i == numLevels - 1){
                numPipes = 0;
            }
            char items[3] = {'H', 'b', 'w'};
            for(int l = 0; l < 2 + numPipes; ++l){
                int coords[2] = {rand() % gridDim, rand() % gridDim};
                while(world[i][coords[0]][coords[1]] == 'H' ||
                      world[i][coords[0]][coords[1]] == 'b' ||
                      world[i][coords[0]][coords[1]] == 'w'){
                    coords[0] = rand() % gridDim;
                    coords[1] = rand() % gridDim;
                }
                world[i][coords[0]][coords[1]] = items[l];

                if(items[l] == 'H'){
                    player->setPos(i, coords[0], coords[1]);
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

    if(spotRNG <= coinChance){
        result = 'c';
    }
    else if(spotRNG <= (coinChance + nothingChance)){
        result = 'x';
    }
    else if(spotRNG <= (coinChance + nothingChance + goombaChance)){
        result = 'g';
    }
    else if(spotRNG <= (coinChance + nothingChance + goombaChance + koopaChance)){
        result = 'k';
    }
    else if(spotRNG <= (coinChance + nothingChance + goombaChance + koopaChance + mushroomChance)){
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
    player->setLevel(levelNum);

    while (player->isAlive() && !levelComplete) {
        int powerLevelBeforeMove = player->getPowerLevel();
        levelComplete = player->move(world[levelNum], gridDim);

        worldLog->writeToLog(levelNum,player->getPosAtLevel(levelNum),powerLevelBeforeMove,
                             player->getAction(),player->getLives(),player->getCoins(),
                               player->getNextMove(),player->isStaying(),world[levelNum],
                                gridDim);
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
    if(!generateWorld()){
        std::cout << "World generation unsuccessful." << std::endl;
        success = false;
    }
    else{
        std::cout << "\n\nWORLD GENERATION SUCCESS \n   ";
        for(int i = 0; i < numLevels; ++i){
            worldLog->displayLevel(world[i], i, gridDim);
            if(!playLevel(i) && !(player->isAlive())){
                worldLog->writeLogEnd("lost", player->getTotalSteps());
                break;
            }
        }
        if(player->isAlive()){
            worldLog->writeLogEnd("win", player->getTotalSteps());
        }
        std::cout << "\n\nTerminating! " << std::endl;
    }

    return success;
}

