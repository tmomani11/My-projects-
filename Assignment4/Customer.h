
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "ListQueue.h"
using namespace std;
#include <string>
#include <cstdlib>


class Customer{
    public:
        Customer();
        Customer(string inputLine, int startTime);
        virtual ~Customer();
        int getStartTime();
        int amountLeft();
        char currentLocation();
        void nextLocation();
        int timeLeft();
        void addTime();
        bool atWindow(bool set);
        bool returnWindow();
    private:
        int totalTime;
        int currTime;
        int left;
        int timeStart;
        bool atWin;
        string characterValues;
        ListQueue<char>* locationOrder;
        ListQueue<int>* timeInOrder;
        char currLoc;
        void seperateTimeLocation(string s);
};





#endif