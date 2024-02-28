#include "Mario.h"
#include <cstdlib>
#include <ctime>

//Constructors & Destructor

/* Mario()
 * Default constructor
 * Return: 
 *   n/a
 * Parameters: 
 *   n/a
 */
Mario::Mario(){
    srand(time(0));

    m_lives = 0;
    m_coins = 0;
    m_powerLevel = 0;
    m_enemiesDefeatedCounter = 0;
    m_totalSteps = 0;
    m_currentLevel = 0;
    m_totalLevels = 0;
    m_alive = false;
    m_pos = nullptr;
    m_nextMove[0] = 0;
    m_nextMove[1] = 0;
    m_stayPut = false;
    m_action = "";
}

/* Mario()
 * Overloaded constructor: sets the number of lives Mario has & how many levels he has to play
 * Return: 
 *   n/a
 * Parameters: 
 *   int lives: Number of lives Mario will have
 *   int numLevels: Number of level Mario will have to play
 */
Mario::Mario(int lives, int numLevels){
    srand(time(0));
    
    m_lives = lives;
    m_coins = 0;
    m_powerLevel = 0;
    m_enemiesDefeatedCounter = 0;
    m_totalSteps = 0;
    m_currentLevel = 0;
    m_totalLevels = numLevels;
    m_alive = true;
    m_stayPut = false;
    m_action = "";

    m_pos = new int*[m_totalLevels];
    for(int i = 0; i < m_totalLevels; ++i){
        m_pos[i] = new int[2];
        for(int j = 0; j < 2; ++j){
            m_pos[i][j] = 0;
        }
    }

    generateNextMove();
}

/* Mario()
 * Destructor: deallocates m_pos
 * Return: 
 *   n/a
 * Parameters: 
 *   n/a
 */
Mario::~Mario(){
    if(m_pos != nullptr){
        for(int i = 0; i < m_totalLevels; ++i){
            delete[] m_pos[i];
        }
        delete[] m_pos;
    }
}

//Public Methods

/* move()
 * Handles what Mario will do when moving once in a level (with many helper functions)
 * Return:
 *   bool: If Mario has completed a given level (by defeating the boss or warping)
 * Parameters: 
 *   char** level: The level Mario is currently on
 *   int gridDim: The dimensions of the level
 */
bool Mario::move(char** level, int gridDim){
    int newY, newX;
    bool levelComplete = false;
    int axis = m_nextMove[0];
    int negOrPos = m_nextMove[1];

    if (axis == 0) {
        // Moving on Y axis
        newY = (m_pos[m_currentLevel][0] + negOrPos + gridDim) % gridDim;
        newX = m_pos[m_currentLevel][1];
    } else if (axis == 1) {
        // Moving on X axis
        newY = m_pos[m_currentLevel][0];
        newX = (m_pos[m_currentLevel][1] + negOrPos + gridDim) % gridDim;
    }

    switch(handleInteraction(level[newY][newX])){
        case 0: //Boss defeated or warp pipe hit
            levelComplete = true;
            /* FALLTHROUGH */

        case 1: //Won the fight against an enemy, picked up an item, or landed on empty ground
            level[m_pos[m_currentLevel][0]][m_pos[m_currentLevel][1]] = 'x';
            setPos(m_currentLevel, newY, newX);
            level[m_pos[m_currentLevel][0]][m_pos[m_currentLevel][1]] = 'H';
            break;

        default:
            break;
    }

    m_totalSteps++;
    generateNextMove();

    return levelComplete;
}

//Private Methods

/* generateNextMove()
 * Generates a new direction for Mario to move.
 * The actual movement will be calculated in move()
 * using these values. 25% chance of up, down, left, or right.
 * Mario will keep the same direction if he must stay put
 */
void Mario::generateNextMove(){
    if(!m_stayPut){
        m_nextMove[0] = rand() % 2; 
        m_nextMove[1] = (rand() % 2) ? 1 : -1; 
    }
}

/* handleInteraction()
 * Handles what Mario will do when he interacts with an object in the level 
 * Return: 
 *   int: Returns if Mario should move to the next position or move onto the next level
 *        If 1, fight won or item sucessfully collected (move to new pos)
 *        If 0, boss defeated or warp pipe hit (move to the next level)
 *        If -1, fight lost or error (stay in pos)
 * Parameters: 
 *   char object: The thing Mario is interacting with
 */
int Mario::handleInteraction(char object) {
    int result = -1;

    switch (object) {
        case 'x':
            m_action = "The position is empty";
            result = 1;
            break;

        case 'c':
            collectCoin();
            m_action = "Mario collected a coin";
            result = 1;
            break;

        case 'm':
            collectMushroom();
            m_action = "Mario ate a mushroom";
            result = 1;
            break;

        case 'g':
        case 'k':
        case 'b':
            m_action = "Mario fought ";
            if (object == 'g') m_action += "a Goomba ";
            else if (object == 'k') m_action += "a Koopa ";
            else m_action += "the level boss ";

            result = handleNPC(object) ? (object == 'b' ? 0 : 1) : -1;

            m_action += "and ";
            m_action += result == 0 ? "won" : "lost";
            break;

        case 'w':
            m_action = "Mario warped";
            result = 0;
            break;

        default:
            m_action = "?";
            break;
    }

    return result;
}
/* collectCoin()
 * Collects a coin & adds a life if it reaches 10
 */
void Mario::collectCoin(){
    m_coins++;
    if(m_coins == 10){
        m_lives++;
        m_coins = 0;
    }
}

/* collectMushroom()
 * Collects a mushroom and raises Mario's power level (capped at 0-2)
 */
void Mario::collectMushroom(){
    if(m_powerLevel < 2){
        m_powerLevel++;
    }
}

/* handleNPC()
 * Handles Mario's interaction with an NPC (currently only supports enemies)
 * Return: 
 *   bool: Returns if Mario is able to move on or must stay in position
 * Parameters: 
 *   char npc: The NPC Mario is interacting with
 */
bool Mario::handleNPC(char npc) {
    bool moveOn = false;

    switch (npc) {
        case 'g':
            moveOn = fightEnemy(80, 1);
            break;

        case 'k':
            moveOn = fightEnemy(65, 1);
            break;

        case 'b':
            // Special case: Even if Mario loses his fight with the boss without losing a life (i.e., at PL2, dropped to PL0), he must stay and fight
            if (!(moveOn = fightEnemy(50, 2))) {
                m_stayPut = true;
            }
            break;

        default:
            break;
    }

    if (moveOn) {  // If Mario won his fight, he can move on
        m_stayPut = false;
    }

    return moveOn;
}


/* fightEnemy()
 * Handles Mario's fights with enemies
 * Return: 
 *   bool: Returns if Mario won or lost
 * Parameters: 
 *   int winPercent: The percent chance that Mario will win the fight against a certain enemy
 *   int drain: How many power levels will be drained from Mario if he loses
 */
bool Mario::fightEnemy(int winPercent, int drain){
    int losePercent = rand() % 100 + 1;
    bool win = false;
    if(losePercent <= winPercent){
        win = true;
        enemyDefeated();
    }
    else{
        decreasePL(drain);
    }
    return win;
}

/* enemyDefeated()
 * Keeps track of how many enemies Mario fought and won against
 * Mario gains a life if he defeats 7 consecutively without losing a life
 * Return: 
 *   void
 * Parameters: 
 *   void
 */
void Mario::enemyDefeated(){
    m_enemiesDefeatedCounter++;
    if(m_enemiesDefeatedCounter == 7){
        m_lives++;
        m_enemiesDefeatedCounter = 0;
    }
}

/* decreasePL()
 * Decreases Mario's power level when he loses a fight
 * If he loses a life while in a fight, he must keep fighting until he wins
 * If his power level drops below zero, he loses a life and if his life drops below zero, he dies
 * Return: 
 *   void
 * Parameters: 
 *   int scale: How much to decrease his power level by
 */
void Mario::decreasePL(int scale){
    m_powerLevel -= scale;
    if(m_powerLevel < 0){
        m_powerLevel = 0;
        m_enemiesDefeatedCounter = 0;
        m_lives--;
        m_stayPut = true;
        if(m_lives <= 0){
            m_alive = false;
        }
    }
}

//Accessors & Mutators

/* getLives()
 * Accessor for Mario's m_lives attribute
 * Return: 
 *   int: m_lives
 */
int Mario::getLives(){
    return m_lives;
}

/* getCoins()
 * Accessor for Mario's m_coins attribute
 * Return: 
 *   int: m_coins
 */
int Mario::getCoins(){
    return m_coins;
}

/* getPowerLevel()
 * Accessor for Mario's m_powerLevel attribute
 * Return: 
 *   int: m_powerLevel
 */
int Mario::getPowerLevel(){
    return m_powerLevel;
}

/* getTotalSteps()
 * Accessor for Mario's m_totalSteps attribute
 * Return: 
 *   int: m_totalSteps
 */
int Mario::getTotalSteps(){
    return m_totalSteps;
}

/* isAlive()
 * Accessor for Mario's m_alive attribute
 * Return: 
 *   bool: m_alive
 */
bool Mario::isAlive(){
    return m_alive;
}

/* getPosAtLevel()
 * Accessor for Mario's m_pos attribute at a given level
 * Return: 
 *   int*: Mario's position
 * Parameters: 
 *   int levelNum: the desired level to get Mario's position from
 */
int* Mario::getPosAtLevel(int levelNum){
    return m_pos[levelNum];
}

/* getNextMove()
 * Accessor for Mario's m_nextMove attribute
 * Return: 
 *   int*: m_nextMove
 * Parameters: 
 *   n/a
 */
int* Mario::getNextMove(){
    return m_nextMove;
}

/* isStaying()
 * Accessor for Mario's m_stayPut attribute
 * Return: 
 *   bool: m_stayPut
 * Parameters: 
 *   n/a
 */
bool Mario::isStaying(){
    return m_stayPut;
}

/* getAction()
 * Accessor for Mario's m_action attribute
 * Return: 
 *   std::string: m_action
 * Parameters: 
 *   n/a
 */
std::string Mario::getAction(){
    return m_action;
}

/* setPos()
 * Mutator for Mario's m_action attribute
 * Return: 
 *   void
 * Parameters: 
 *   int levelNum: the level number to change Mario's position on
 *   int y: the new Y position
 *   int x: the new X position
 */
void Mario::setPos(int levelNum, int y, int x){
    m_pos[levelNum][0] = y;
    m_pos[levelNum][1] = x;
}

/* setPos()
 * Mutator for Mario's m_currentLevel attribute
 * Return: 
 *   void
 * Parameters: 
 *   int levelNum: the level number to change
 */
void Mario::setLevel(int levelNum){
    m_currentLevel = levelNum;
}