#include <iostream>
#include "Customer.h"

using namespace std;


Customer::Customer(int finAid, int regist, int cash, ListQueue<char> *order, int num) {
    this->finAid = finAid;
    this->regist = regist;
    this->cash = cash;
    this->order = order;
    
    this->attendTime = 0;
    this->curWait = 0;
    this->totalWait = 0;
    this->waiting = true;

    this->num = num;
}

/*
~Customer() - deconstructor
*/
Customer::~Customer() {
    delete order;
}

int Customer::getCurWait() {
    return curWait;
}

int Customer::getTotalWait() {
    return totalWait;
}

int Customer::getFinAid() {
    return finAid;
}

int Customer::getRegist() {
    return regist;
}

int Customer::getCash() {
    return cash;
}

char Customer::getDest() {
    return order->peek();
}

int Customer::getAttendTime() {
    return attendTime;
}

ListQueue<char>*& Customer::getOrder() {
    return order;
}

/*
void attend() - simulates the student being attended by an office; sets waiting to false
*/
void Customer::attend() {
    waiting = false;

}

/*
void finish() - simulates a student finishing at an office; adds the current wait to total wait, sets current wait to 0, pops the front value
off order, sets attendTime to 0, and sets waiting to true
*/
void Customer::finish() {
    totalWait += curWait;
    curWait = 0;
    order->remove();
    attendTime = 0;
    waiting = true;
}

/*
void passTime() - simulates one min passed; if the student is waiting then it iterates currWait; if the student is being attended it iterates 
attendTime
*/
void Customer::passTime() {
    if (waiting) {
        curWait++;
        cout << "Student " << num << " is Waiting" << endl;
    }
    else {
        attendTime++;
        cout << "Student " << num << " is being Attended To at Window " << order->peek() << endl;
    }
}