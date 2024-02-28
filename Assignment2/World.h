#ifndef WORLD_H
#define WORLD_H

#include "Mario.h"
#include "FileIO.h"

class World{
    private:
        //Attributes
        Mario* m_player; //The player in the world
        FileIO* m_worldLog; //The log of every event that took place in the world
        int m_numLevels; //The number of levels in the world
        int m_gridDim; //The dimension of every level
        int m_marioLives; //How many lives Mario has
        int m_cP, m_nP, m_gP, m_kP, m_mP;
        char* m_outputFileName; //The filename of the log
        char*** m_world; //The 3D array that holds the world

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