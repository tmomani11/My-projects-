#ifndef WORLD_H
#define WORLD_H

#include "Mario.h"
#include "FileIO.h"

class World{
    private:
        //Attributes
        Mario* player; //The player in the world
        FileIO* worldLog; //The log of every event that took place in the world
        int numLevels; //The number of levels in the world
        int gridDim; //The dimension of every level
        int marioLives; //How many lives Mario has
        int coinChance;
        int nothingChance;
        int goombaChance;
        int koopaChance;
        int mushroomChance;

        char* outputFileName; //The filename of the log
        char*** world; //The 3D array that holds the world

        //Methods
        bool generateWorld();
        char generateSquare();
        bool playLevel(int level);

    public:
        //Constructors & Destructor
        World();
        World(int* specs, char* outputFileName);
        virtual ~World();

        //Methods
        bool start();
};

#endif