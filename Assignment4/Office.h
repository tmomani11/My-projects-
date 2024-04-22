#ifndef OFFICE_H
#define OFFICE_H

#include <cstdlib>
#include <iostream>
#include "Window.h"
#include "DblList.h"

using namespace std;

/**
 * @class Office
 * @brief A class that represents an office.
 */
class Office {
public:
    /**
     * @brief Construct a new Office object
     * @param size The size of the office
     * @param type The type of the office
     */
    Office(int size, char type);

    /**
     * @brief Destroy the Office object
     */
    ~Office();

    /**
     * @brief Attend to a student
     */
    void attendStudent();

    /**
     * @brief Pass the time
     */
    void passMin();

    /**
     * @brief Line up a student
     * @param student The student to be lined up
     */
    void lineUp(Customer *student);

    /**
     * @brief Get the attending student
     * @return Customer* The attending student
     */
    Customer* getAttending();

    /**
     * @brief Get the Mean Wait time
     * @return double The mean wait time
     */
    double getMeanWait();

    /**
     * @brief Get the Longest Wait time
     * @return int The longest wait time
     */
    int getLongestWait();

    /**
     * @brief Get the Mean Idle time
     * @return double The mean idle time
     */
    double getMeanIdle();

    /**
     * @brief Get the Longest Idle time
     * @return int The longest idle time
     */
    int getLongestIdle();

    /**
     * @brief Get the Idle Over5 count
     * @return int The count of idle over 5
     */
    int getIdleOver5();

    /**
     * @brief Get the Office
     * @return DblList<Window*>*& The office
     */
    DblList<Window*>*& getOffice();

    /**
     * @brief Get the Finished
     * @return ListQueue<Customer*>*& The finished queue
     */
    ListQueue<Customer*>*& getFinished();

    /**
     * @brief Print the windows
     */
    void printWindows();

    /**
     * @brief Print the finished list
     */
    void printFinishedList();

private:
    char type; ///< The type of the office
    double totalIdle; ///< The total idle time
    int maxWindows; ///< The maximum number of windows
    int occupWindows; ///< The number of occupied windows
    double totalWait; ///< The total wait time
    int numStudents; ///< The number of students
    int longestWait; ///< The longest wait time

    ListQueue<Customer*> *line; ///< The line of customers
    ListQueue<Customer*> *finished; ///< The finished queue
    DblList<Window*> *office; ///< The office
};

#endif