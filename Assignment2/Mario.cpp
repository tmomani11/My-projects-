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
    srand(time(nullptr));

    lives = 0;
    coins = 0;
    powerLevel = 0;
    enemiesDefeatedCounter = 0;
    totalSteps = 0;
    currentLevel = 0;
    numLevels = 0;
    alive = false;
    pos = nullptr;
    nextMove[0] = 0;
    nextMove[1] = 0;
    stayPut = false;
    action = "";
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
    
    this->lives = lives;
    coins = 0;
    powerLevel = 0;
    enemiesDefeatedCounter = 0;
    totalSteps = 0;
    currentLevel = 0;
    this->numLevels = numLevels;
    alive = true;
    stayPut = false;
    action = "";

    pos = new int*[numLevels];
    for(int i = 0; i < numLevels; ++i){
        pos[i] = new int[2];
        for(int j = 0; j < 2; ++j){
            pos[i][j] = 0;
        }
    }

    generateNextMove();
}

/* Mario()
 * Destructor: deallocates pos
 * Return: 
 *   n/a
 * Parameters: 
 *   n/a
 */
Mario::~Mario(){
    if(pos != nullptr){
        for(int i = 0; i < numLevels; ++i){
            delete[] pos[i];
        }
        delete[] pos;
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
    int axis = nextMove[0];
    int negOrPos = nextMove[1];

    if (axis == 0) {
        // Moving on Y axis
        newY = (pos[currentLevel][0] + negOrPos + gridDim) % gridDim;
        newX = pos[currentLevel][1];
    } else if (axis == 1) {
        // Moving on X axis
        newY = pos[currentLevel][0];
        newX = (pos[currentLevel][1] + negOrPos + gridDim) % gridDim;
    }
    int interaction = handleInteraction(level[newY][newX]);
    switch(interaction){
        case 0: //Boss defeated or warp pipe hit
            levelComplete = true;
            /* FALLTHROUGH */

        case 1: //Won the fight against an enemy, picked up an item, or landed on empty ground
            level[pos[currentLevel][0]][pos[currentLevel][1]] = 'x';
            setPos(currentLevel, newY, newX);
            level[pos[currentLevel][0]][pos[currentLevel][1]] = 'H';
            break;

        default:
            break;
    }

    totalSteps++;
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
    if(!stayPut){
        nextMove[0] = rand() % 2; // move on either the x or y axis
        nextMove[1] = (rand() % 2)? 1 : -1; // move in the positive(right) or negative(left) direction
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
//int Mario::handleInteraction(char object) {
//    int result = -1;
//
//    switch (object) {
//        case 'x':
//            action = "The position is empty";
//            result = 1;
//            break;
//
//        case 'c':
//            collectCoin();
//            action = "Mario collected a coin";
//            result = 1;
//            break;
//
//        case 'm':
//            collectMushroom();
//            action = "Mario ate a mushroom";
//            result = 1;
//            break;
//
//        case 'g':
//        case 'k':
//        case 'b':
//            action = "Mario fought ";
//            if (object == 'g') action += "a Goomba ";
//            else if (object == 'k') action += "a Koopa ";
//            else action += "the level boss ";
//
//            result = handleNPC(object) ? (object == 'b' ? 0 : 1) : -1;
//
//            action += "and ";
//            action += result == 0 ? "won" : "lost";
//            break;
//
//        case 'w':
//            action = "Mario warped";
//            result = 0;
//            break;
//
//        default:
//            action = "?";
//            break;
//    }
//
//    return result;
//}
int Mario::handleInteraction(char object) {
    int result = -1;

    if (object == 'x') {
        action = "The position is empty";
        result = 1;
    } else if (object == 'c') {
        collectCoin();
        action = "Mario collected a coin";
        result = 1;
    } else if (object == 'm') {
        collectMushroom();
        action = "Mario ate a mushroom";
        result = 1;
    } else if (object == 'g' || object == 'k' || object == 'b') {
        action = "Mario fought ";
        action += (object == 'g') ? "a Goomba " : (object == 'k') ? "a Koopa " : "the level boss ";
        result = handleNPC(object) ? (object == 'b' ? 0 : 1) : -1;
        action += result == 0 ? "won" : "lost";
    } else if (object == 'w') {
        action = "Mario warped";
        result = 0;
    } else {
        action = "?";
    }

    return result;
}
/* collectCoin()
 * Collects a coin & adds a life if it reaches 10
 */
void Mario::collectCoin(){
    coins++;
    if(coins == 10){
        lives++;
        coins = 0;
    }
}

/* collectMushroom()
 * Collects a mushroom and raises Mario's power level (capped at 0-2)
 */
void Mario::collectMushroom(){
    if(powerLevel < 2){
        powerLevel++;
    }
}

/* handleNPC()
 * Handles Mario's interaction with an NPC
 * Return: 
 *   bool: Returns if Mario is able to move on or must stay in position
 * Parameters: 
 *   char npc: The NPC Mario is interacting with
 */
bool Mario::handleNPC(char npc) {
    bool moveOn = false;

    int winPercent = 0;
    int drain = 0;

    switch (npc) {
        case 'g':
            winPercent = 80;
            drain = 1;
            break;

        case 'k':
            winPercent = 65;
            drain = 1;
            break;

        case 'b':
            winPercent = 50;
            drain = 2;
            break;

        default:
            break;
    }

    if (winPercent > 0 && drain > 0) {
        int losePercent = rand() % 100 + 1;
        if (losePercent <= winPercent) {
            moveOn = true;
            enemyDefeated();
        } else {
            decreasePL(drain);
            if (npc == 'b') {
                stayPut = true;
            }
        }
    }

    if (moveOn) {
        stayPut = false;
    }

    return moveOn;
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
    enemiesDefeatedCounter++;
    if(enemiesDefeatedCounter == 7){
        lives++;
        enemiesDefeatedCounter = 0;
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
    powerLevel -= scale;
    if(powerLevel < 0){
        powerLevel = 0;
        enemiesDefeatedCounter = 0;
        lives--;
        stayPut = true;
        if(lives <= 0){
            alive = false;
        }
    }
}

//Accessors & Mutators

/* getLives()
 * Accessor for Mario's lives attribute
 * Return: 
 *   int: lives
 */
int Mario::getLives() const{
    return lives;
}

/* getCoins()
 * Accessor for Mario's coins attribute
 * Return: 
 *   int: coins
 */
int Mario::getCoins() const{
    return coins;
}

/* getPowerLevel()
 * Accessor for Mario's powerLevel attribute
 * Return: 
 *   int: powerLevel
 */
int Mario::getPowerLevel() const{
    return powerLevel;
}

/* getTotalSteps()
 * Accessor for Mario's totalSteps attribute
 * Return: 
 *   int: totalSteps
 */
int Mario::getTotalSteps() const{
    return totalSteps;
}

/* isAlive()
 * Accessor for Mario's alive attribute
 * Return: 
 *   bool: alive
 */
bool Mario::isAlive() const{
    return alive;
}

/* getPosAtLevel()
 * Accessor for Mario's pos attribute at a given level
 * Return: 
 *   int*: Mario's position
 * Parameters: 
 *   int levelNum: the desired level to get Mario's position from
 */
int* Mario::getPosAtLevel(int levelNum){
    return pos[levelNum];
}

/* getNextMove()
 * Accessor for Mario's nextMove attribute
 * Return: 
 *   int*: nextMove
 * Parameters: 
 *   n/a
 */
int* Mario::getNextMove(){
    return nextMove;
}

/* isStaying()
 * Accessor for Mario's stayPut attribute
 * Return: 
 *   bool: stayPut
 * Parameters: 
 *   n/a
 */
bool Mario::isStaying() const{
    return stayPut;
}

/* getAction()
 * Accessor for Mario's action attribute
 * Return: 
 *   std::string: action
 * Parameters: 
 *   n/a
 */
std::string Mario::getAction(){
    return action;
}

/* setPos()
 * Mutator for Mario's action attribute
 * Return: 
 *   void
 * Parameters: 
 *   int levelNum: the level number to change Mario's position on
 *   int y: the new Y position
 *   int x: the new X position
 */
void Mario::setPos(int levelNum, int y, int x){
    pos[levelNum][0] = y;
    pos[levelNum][1] = x;
}

/* setPos()
 * Mutator for Mario's currentLevel attribute
 * Return: 
 *   void
 * Parameters: 
 *   int levelNum: the level number to change
 */
void Mario::setLevel(int levelNum){
    currentLevel = levelNum;
}