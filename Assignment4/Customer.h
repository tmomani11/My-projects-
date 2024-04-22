#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <cstdlib>
#include <iostream>
#include "ListQueue.h"

using namespace std;

/**
 * @class Customer
 * @brief A class that represents a customer.
 */
class Customer {
public:
    /**
     * @brief Construct a new Customer object
     * @param finAid The financial aid of the customer
     * @param regist The registration of the customer
     * @param cash The cash of the customer
     * @param order The order of the customer
     * @param num The number of the customer
     */
    Customer(int finAid, int regist, int cash, ListQueue<char> *order, int num);

    /**
     * @brief Destroy the Customer object
     */
    ~Customer();

    /**
     * @brief Get the Current Wait time
     * @return int The current wait time
     */
    int getCurWait();

    /**
     * @brief Get the Total Wait time
     * @return int The total wait time
     */
    int getTotalWait();

    /**
     * @brief Get the Financial Aid
     * @return int The financial aid
     */
    int getFinAid();

    /**
     * @brief Get the Registration
     * @return int The registration
     */
    int getRegist();

    /**
     * @brief Get the Cash
     * @return int The cash
     */
    int getCash();

    /**
     * @brief Get the Destination
     * @return char The destination
     */
    char getDest();

    /**
     * @brief Get the Attend Time
     * @return int The attend time
     */
    int getAttendTime();

    /**
     * @brief Get the Order
     * @return ListQueue<char>*& The order
     */
    ListQueue<char>*& getOrder();

    /**
     * @brief Check if the customer is waiting
     * @return bool True if the customer is waiting, false otherwise
     */
    bool isWaiting();

    /**
     * @brief Attend to the customer
     */
    void attend();

    /**
     * @brief Finish the customer
     */
    void finish();

    /**
     * @brief Pass the time
     */
    void passTime();

    /**
     * @brief Get the number of the customer
     * @return int The number of the customer
     */
    int getNum();
int num;
private:
    int finAid; ///< The financial aid of the customer
    int regist; ///< The registration of the customer
    int cash; ///< The cash of the customer
    char office; ///< The office of the customer

    int attendTime; ///< The attend time of the customer
    int curWait; ///< The current wait time of the customer
    int totalWait; ///< The total wait time of the customer
    bool waiting; ///< The waiting status of the customer

    ListQueue<char> *order; ///< The order of the customer
};

#endif