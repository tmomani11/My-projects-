/*
 * Tyler Momani
 * 2455776
 * momani@chapman.edu
 * CPSC 350-02
 * Assignment 2: Not So Super Mario Bros.
 */
#ifndef MARIO_H
#define MARIO_H
#include <string>

class Mario{
    private:
        //Attributes
        int m_lives;                //Mario's lives
        int m_coins;        //Mario's coins
        int m_powerLevel;           //Mario's power level
        int m_enemiesDefeatedCounter; //For calculating if Mario gets a free life on kill #7
        int m_totalSteps;       //Total steps Mario hs taken
        int m_currentLevel;      //The current level Mario's on
        int m_totalLevels;      //The total number of levels in the simulation (for allocating m_pos)
        bool m_alive;           //Is Mario alive?
        int** m_pos;            //Mario's position ([y, x], per level)
        int m_nextMove[2];      //Mario's next move
        bool m_stayPut;         //Is Mario able to move on from his current position?
        std::string m_action; //The action took by Mario in a round

        //Methods
        void generateNextMove();
        int handleInteraction(char item);
        void collectCoin();
        void collectMushroom();
        bool handleNPC(char npc);
        bool fightEnemy(int winPercent, int drain);
        void enemyDefeated();
        void decreasePL(int scale);

    public:
        //Constructors & Destructor
        Mario();
        Mario(int lives, int numLevels);
        virtual~Mario();

        //Methods
        bool move(char** level, int gridDim);

        //Accessors
        int getLives();
        int getCoins();
        int getPowerLevel();
        int getTotalSteps();
        bool isAlive();
        int* getPosAtLevel(int levelNum);
        int* getNextMove();
        bool isStaying();
        std::string getAction();

        //Mutators
        void setPos(int levelNum, int y, int x); 
        void setLevel(int levelNum);
};

#endif