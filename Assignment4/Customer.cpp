#include <iostream>
#include "Customer.h"

using namespace std;

/**
 * @brief Construct a new Customer:: Customer object
 *
 * @param finAid The financial aid of the customer
 * @param regist The registration of the customer
 * @param cash The cash of the customer
 * @param order The order of the customer
 * @param num The number of the customer
 */
Customer::Customer(int finAid, int regist, int cash, ListQueue<char> *order, int num) {
    this->finAid = finAid;
    this->regist = regist;
    this->cash = cash;
    this->order = order;
    this->num = num;
    this->attendTime = 0;
    this->curWait = 0;
    this->totalWait = 0;
    this->waiting = true;


}

/**
 * @brief Destroy the Customer:: Customer object
 */
Customer::~Customer() {
    delete order;
}

/**
 * @brief Get the Current Wait time
 *
 * @return int The current wait time
 */
int Customer::getCurWait() {
    return curWait;
}

/**
 * @brief Get the Total Wait time
 *
 * @return int The total wait time
 */
int Customer::getTotalWait() {
    return totalWait;
}

/**
 * @brief Get the Financial Aid
 *
 * @return int The financial aid
 */
int Customer::getFinAid() {
    return finAid;
}

/**
 * @brief Get the Registration
 *
 * @return int The registration
 */
int Customer::getRegist() {
    return regist;
}

/**
 * @brief Get the Cash
 *
 * @return int The cash
 */
int Customer::getCash() {
    return cash;
}

/**
 * @brief Get the Destination
 *
 * @return char The destination
 */
char Customer::getDest() {
    return order->peek();
}

/**
 * @brief Get the Attend Time
 *
 * @return int The attend time
 */
int Customer::getAttendTime() {
    return attendTime;
}

/**
 * @brief Get the Order
 *
 * @return ListQueue<char>*& The order
 */
ListQueue<char>*& Customer::getOrder() {
    return order;
}

/**
 * @brief Attend to the customer
 */
void Customer::attend() {
    waiting = false;
}

/**
 * @brief Finish the customer
 */
void Customer::finish() {
    totalWait += curWait;
    curWait = 0;
    order->remove();
    attendTime = 0;
    waiting = true;
}

/**
 * @brief Pass the time
 */
void Customer::passTime() {
    if (waiting) {
        curWait++;
    }
    else {
        attendTime++;
    }
}