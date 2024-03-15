#ifndef MARIO_H
#define MARIO_H
#include <string>

class Mario{
    private:
    //Attributes
        int lives;             //Mario's lives
        int coins;            //Mario's coins
        int powerLevel;           //Mario's power level
        int enemiesDefeatedCounter; //For calculating if Mario gets a free life on kill #7
        int totalSteps;       //Total steps Mario hs taken
        int currentLevel;     //The current level Mario's on
        int numLevels;      //The total number of levels in the simulation (for allocating pos)
        bool alive;           //Is Mario alive?
        int** pos;            //Mario's position ([y, x], per level)
        int nextMove[2];      //Mario's next move
        bool stayPut;         //Is Mario able to move on from his current position?
        std::string action;   //The action took by Mario in a round

        //Methods
        void generateNextMove();
        int handleInteraction(char item);
        void collectCoin();
        void collectMushroom();
        bool handleNPC(char npc);
        void enemyDefeated();
        void decreasePL(int scale);

    public:
        //Constructors & Destructor
        Mario();                         //Default constructor
        Mario(int lives, int numLevels); //overloaded Constructor
        virtual~Mario();                 //virtual Destructor

        //Methods
        bool move(char** level, int gridDim); //Move Mario

        //Getters
        int getLives() const;             //Get Mario's lives
        int getCoins() const;             //Get Mario's coins
        int getPowerLevel() const;        //Get Mario's power level
        int getTotalSteps() const;        //Get Mario's total steps
        bool isAlive() const;             //Is Mario alive?
        int* getPosAtLevel(int levelNum); //Get Mario's position at a level
        int* getNextMove();               //Get Mario's next move
        bool isStaying() const;           //Is Mario staying put?
        std::string getAction();          //Get Mario's action

        //Setters
        void setPos(int levelNum, int y, int x); //Set Mario's position
        void setLevel(int levelNum); //Set Mario's level
};

#endif