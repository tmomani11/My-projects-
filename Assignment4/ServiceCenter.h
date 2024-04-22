#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <iostream>
#include "Office.h"
#include <fstream>
#include "Office.h"

using namespace std;

/**
 * @class ServiceCenter
 * @brief A class that represents a service center
 */
class ServiceCenter {
public:
    /**
     * @brief Constructor that takes an input filename and initializes variables
     * @param filename The name of the file to read from
     */
    ServiceCenter(string filename);

    /**
     * @brief Destructor for the ServiceCenter class
     */
    ~ServiceCenter();

    /**
     * @brief Function that handles File I/O for reading from the txt file.
     * @param filename The name of the file to read from
     */
    void readFile(string filename);

    /**
     * @brief Simulates a single minute passing in the Service Center.
     */
    void passMin();

    /**
     * @brief Takes a string line and returns a Customer created from that line
     * @param line The line to read from
     * @return A pointer to the created Customer
     */
    Customer* readLine(string line);

    /**
     * @brief Prints the simulation results
     */
    void printResult();

    /**
     * @brief Assigns time to the respective office
     * @param office The office to assign time to
     * @param time The time to assign
     * @param finAid The financial aid time
     * @param registrar The registrar time
     * @param cash The cash time
     */
    void assignTime(char office,int time,int& finAid,int& registrar,int& cash);

    /**
     * @brief Prints the number of students waiting over 10 minutes total across all offices
     */
    void printWaitOver10();

    /**
     * @brief Prints the number of windows idle for over 5 minutes across all offices
     */
    void printIdleOver5();

    /**
     * @brief Prints the finished list
     */
    void printFinished();

private:
    Office *cashier; ///< Pointer to the cashier office
    Office *finAid; ///< Pointer to the financial aid office
    Office *registrar; ///< Pointer to the registrar office
    int numStudents; ///< Number of students
    ListQueue<Customer*> *studentLine; ///< Queue of students
    DblList<Customer*> *finished; ///< List of finished students
    int time; ///< Current time
};

#endif