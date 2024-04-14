
#include <cstdlib>
#include <string>
#include "Customer.h"
#include "ListQueue.h"
using namespace std;

//Default Constructor
Customer::Customer(){
    characterValues = "";
    currTime = 0;
    left = -1;
    atWin = false;
}

//Overloaded Constructor (which takes in a string and the time the customer starts)
Customer::Customer(string inputLine, int startTime){
    characterValues = inputLine;
    seperateTimeLocation(characterValues);
    currTime = 0;
    left = 3;
    timeStart = startTime;
    atWin = false;
}

//Default Destructor
Customer::~Customer(){
    delete timeInOrder;
    delete locationOrder;
}

//Returns the start time of the customer
int Customer::getStartTime(){
    return timeStart;
}

//seperates the time and locations from a string into two Queue's
void Customer::seperateTimeLocation(string s){
    timeInOrder = new ListQueue<int>();
    locationOrder = new ListQueue<char>();
    int count = 0;
    int atCurrSpace = 0;
    int atNextSpace = 0;
    while(count < 6){
        if(count < 3){
            atNextSpace = s.find(' ', atCurrSpace);
            string c = s.substr(atCurrSpace, atNextSpace);
            int timeAt = stoi(c);
            timeInOrder->add(timeAt);
            count++;
            atCurrSpace = atNextSpace+1;
        } else {
            atNextSpace = s.find(' ', atCurrSpace);
            string c = s.substr(atCurrSpace, atNextSpace);
            char character = c[0];
            locationOrder->add(character);
            count++;
            atCurrSpace = atNextSpace+1;
        }
        
    }
}

//returns amount of spots the customer has left to visit
int Customer::amountLeft(){
    return left;
}

//returns the current location the customer should be
char Customer::currentLocation(){
    return locationOrder->peek();
}

//makes the customer go to the next location, making the next time go as well, and the currTime at that location being set to 0
void Customer::nextLocation(){
    locationOrder->remove();
    timeInOrder->remove();
    currTime = 0;
    left--;
}

//returns how much time is left at the current location
int Customer::timeLeft(){
    return (timeInOrder->peek() - currTime);
}

//adds time to the customer
void Customer::addTime(){
    currTime++;
}

//sets if the customer is at a window or not
bool Customer::atWindow(bool insert){
    atWin = insert;
}

//returns whether the customer is at a window or not
bool Customer::returnWindow(){
    return atWin;
}