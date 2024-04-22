#include <iostream>
#include "Window.h"
#include "Office.h"

using namespace std;

/**
 * @brief Construct a new Office object
 * @param size The size of the office
 * @param type The type of the office
 */
Office::Office(int size, char type) {
    this->type = type;
    this->line = new ListQueue<Customer*>();
    this->finished = new ListQueue<Customer*>();
    this->office = new DblList<Window*>();
    for (int i = 0; i < size; i++) {
        office->addBack(new Window(type));
    }
    totalIdle = 0;
    maxWindows = size;
    occupWindows = 0;
    totalWait = 0;
    numStudents = 0;
}

/**
 * @brief Destroy the Office object
 */
Office::~Office() {
    delete line;
    delete finished;
    delete office;
}

/**
 * @brief Get the Finished object
 * @return ListQueue<Customer*>*& The finished queue
 */
ListQueue<Customer*>*& Office::getFinished() {
    return finished;
}

/**
 * @brief Print the finished list
 */
void Office::printFinishedList() {
    if (finished->isEmpty()) cout << "Finished is Empty" << endl;
    else {
        cout << "Finished List" << endl;
        for (int i = 0; i < finished->size(); i++) {
            cout << "Index " << i << ": Student" << endl;
        }
    }
}

/**
 * @brief Print the windows
 */
void Office::printWindows() {
    int occupied = 0;
    for (int i = 0; i < office->getSize(); i++) {
        if (office->get(i)->isOccupied()) {
            occupied++;
        }
    }
}

/**
 * @brief Attend to a student
 */
void Office::attendStudent() {
    if (occupWindows == maxWindows) return;
    occupWindows++;
    totalWait += line->peek()->getCurWait();
    if (line->peek()->getCurWait() > longestWait) {
        longestWait = line->peek()->getCurWait();
    }
    for (int i = 0; i < office->getSize(); i++) {
        if (!office->get(i)->isOccupied()) {
            office->get(i)->setStudent(line->remove());
            return;
        }
    }
}

/**
 * @brief Line up a student
 * @param student The student to be lined up
 */
void Office::lineUp(Customer *student) {
    line->add(student);
    if (occupWindows < maxWindows) {
        attendStudent();
    }
    numStudents++;
}

/**
 * @brief Pass the time
 */
void Office::passMin()  {
    for (int i = 0; i < office->getSize(); i++) {
        office->get(i)->passTime();
        if (!office->get(i)->isOccupied()) {
            if (!line->isEmpty()) {
                office->get(i)->setStudent(line->remove());
            }
            if (office->get(i)->finished) {
                finished->add(office->get(i)->getStudent());
                office->get(i)->finished = false;
            }
        }
    }
}

/**
 * @brief Get the Mean Wait time
 * @return double The mean wait time
 */
double Office::getMeanWait() {
    return totalWait / numStudents;
}

/**
 * @brief Get the Longest Wait time
 * @return int The longest wait time
 */
int Office::getLongestWait() {
    return longestWait;
}

/**
 * @brief Get the Mean Idle time
 * @return double The mean idle time
 */
double Office::getMeanIdle() {
    double total = 0;
    for (int i = 0; i < office->getSize(); i++) {
        total += office->get(i)->getIdle();
    }
    return total / maxWindows;
}

/**
 * @brief Get the Longest Idle time
 * @return int The longest idle time
 */
int Office::getLongestIdle() {
    double max = 0;
    for (int i = 0; i < office->getSize(); i++) {
        if (office->get(i)->getIdle() > max) {
            max = office->get(i)->getIdle();
        }
    }
    return max;
}

/**
 * @brief Get the Idle Over5 count
 * @return int The count of idle over 5
 */
int Office::getIdleOver5() {
    int idleOver5 = 0;
    for (int i = 0; i < office->getSize(); i++) {
        if (office->get(i)->getIdle() >= 5) idleOver5++;
    }
    return idleOver5;
}