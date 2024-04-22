#include <iostream>
#include "Window.h"
#include "Customer.h"

using namespace std;

/**
 * @brief Constructor for the Window class
 * @param type The type of the window
 */
Window::Window(char type) {
    this->type = type;
    this->students = 0;
    this->idle = 0;
    this->timeNeeded = 0;
    this->occupied = false;
    currTime = 0;
    finished = false;
}

/**
 * @brief Destructor for the Window class
 */
Window::~Window() {
    delete curStudent;
}

/**
 * @brief Sets the current student for the window
 * @param student The student to be set
 */
void Window::setStudent(Customer *student) {
    this->curStudent = student;
    curStudent->attend();
    switch (type) {
        case 'C':
            timeNeeded = student->getCash();
            break;
        case 'F':
            timeNeeded = student->getFinAid();
            break;
        case 'R':
            timeNeeded = student->getRegist();
            break;
    }
    occupied = true;
}

/**
 * @brief Returns the idle time of the window
 * @return The idle time
 */
int Window::getIdle() {
    return idle;
}

/**
 * @brief Returns the current student of the window
 * @return The current student
 */
Customer* Window::getStudent() {
    return curStudent;
}

/**
 * @brief Checks if the window is occupied
 * @return True if the window is occupied, false otherwise
 */
bool Window::isOccupied() {
    return occupied;
}

/**
 * @brief Simulates the window finishing a student
 */
void Window::finish() {
    curStudent->finish();
    occupied = false;
    currTime = 0;
    finished = true;
}

/**
 * @brief Simulates one minute passing in the window
 */
void Window::passTime() {
    // is idle
    if (!occupied) {
        idle++;
    }
        // occupied
    else {
        curStudent->passTime();

        currTime++;
        if (currTime >= timeNeeded) finish();
    }
}