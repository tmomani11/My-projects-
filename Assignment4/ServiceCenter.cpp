
#include <iostream>
#include "ServiceCenter.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/**
 * @brief Constructs a new Service Center object.
 *
 * Initializes queues, sets up office windows, and processes input data from a specified file to set up the simulation environment.
 * @param filename Name of the file from which to read the initialization data.
 */
ServiceCenter::ServiceCenter(string filename) {
    studentLine = new ListQueue<Customer*>();
    finished = new DblList<Customer*>();
    numStudents = 0;
    readFile(filename);
    time = 0;
}

/**
 * @brief Destroys the Service Center object.
 *
 * Cleans up dynamically allocated memory to prevent memory leaks.
 */
ServiceCenter::~ServiceCenter() {
    delete cashier;
    delete finAid;
    delete registrar;
    delete studentLine;
    delete finished;
}

/**
 * @brief Reads and processes data from the specified file.
 *
 * Sets up the initial configuration of service offices and processes arriving students and their service requests.
 * @param filename Name of the file to read from.
 */
void ServiceCenter::readFile(string filename) {
    ifstream read(filename);
    cout << "----------------------------------------------------------------";

    string line;
    int windows;

    getline(read, line);
    windows = stoi(line);
    registrar = new Office(windows, 'R');

    getline(read, line);
    windows = stoi(line);
    cashier = new Office(windows, 'C');

    getline(read, line);
    windows = stoi(line);
    finAid = new Office(windows, 'F');
    cout << "----------------------------------------------------------------";

    int target = 0;
    while (getline(read, line)) {
        target = stoi(line);
        while (time < target) {
            passMin();
        }
        getline(read, line);
        int addStudents = stoi(line);

        for (int i = 0; i < addStudents; i++) {
            getline(read, line);
            Customer* student = readLine(line);
            switch (student->getDest()) {
                case 'F':
                    finAid->lineUp(student);
                    break;
                case 'R':
                    registrar->lineUp(student);
                    break;
                case 'C':
                    cashier->lineUp(student);
                    break;
            }
            numStudents++;
        }
        cout << "----------------------------------------------------------------";
    }
    read.close();

    while (finished->getSize() != numStudents) {
        passMin();
    }
    cout << "----------------------------------------------------------------";
}

/**
 * @brief Parses a line of input to create a new Customer object.
 *
 * @param line A string containing the customer's required times at each office and the order of the offices.
 * @return Customer* A pointer to the newly created Customer object.
 */
Customer* ServiceCenter::readLine(string line) {
    stringstream fullLine(line);
    int a, b, c;
    fullLine >> a >> b >> c;

    int finAid = 0, regist = 0, cash = 0;
    char first, second, third;
    fullLine >> first >> second >> third;

    ListQueue<char>* order = new ListQueue<char>();
    order->add(first);
    order->add(second);
    order->add(third);

    assignTime(first, a, finAid, regist, cash);
    assignTime(second, b, finAid, regist, cash);
    assignTime(third, c, finAid, regist, cash);

    Customer* student = new Customer(finAid, regist, cash, order, numStudents);

    return student;
}

/**
 * @brief Assigns the required time for each office based on the office identifier.
 *
 * @param office Character representing the office (F, R, C).
 * @param time Time required at the specified office.
 * @param finAid Reference to Financial Aid time.
 * @param registrar Reference to Registrar time.
 * @param cash Reference to Cashier time.
 */
void ServiceCenter::assignTime(char office, int time, int &finAid, int &registrar, int &cash) {
    switch (office) {
        case 'F':
            finAid = time;
            break;
        case 'R':
            registrar = time;
            break;
        case 'C':
            cash = time;
            break;
    }
}

void ServiceCenter::printFinished() {
    cout << "Finished List in ServiceCenter" << endl;
    for (int i = 0; i < finished->getSize(); i++) {
        cout << "Index " << i << ": Student " << finished->get(i)->num << endl;
    }
}

/*
void passTime() - Simulates a single minute passing in the Service Center. Calls passTime() on each of the 3 offices, and if any of the offices have
finished students, it pops the student, and if the student has offices left to go to, it calls Office.lineUp() at the respective office, else if the
student is fully finished, then it adds the studet to finished
*/
void ServiceCenter::passMin() {
    time++;
    cashier->printWindows();
    finAid->printWindows();
    registrar->printWindows();
    cashier->passMin();
    finAid->passMin();
    registrar->passMin();

    while (!cashier->getFinished()->isEmpty()) {
        Customer* student = cashier->getFinished()->remove();
        if (student->getOrder()->isEmpty()) {
            finished->addBack(student);
        }
        else {
            char dest = student->getOrder()->peek();
            if (dest == 'F') finAid->lineUp(student);
            else if (dest == 'R') registrar->lineUp(student);
            else if (dest == 'C') finished->addBack(student);
        }
    }

    while (!finAid->getFinished()->isEmpty()) {
        Customer* student = finAid->getFinished()->remove();
        if (student->getOrder()->isEmpty()) {
            finished->addBack(student);
        }
        else {
            char dest = student->getOrder()->peek();
            if (dest == 'C') cashier->lineUp(student);
            else if (dest == 'R') registrar->lineUp(student);
            else if (dest == 'F') finished->addBack(student);
        }
    }

    while (!registrar->getFinished()->isEmpty()) {
        Customer* student = registrar->getFinished()->remove();
        if (student->getOrder()->isEmpty()) {
            finished->addBack(student);
        }
        else {
            char dest = student->getOrder()->peek();
            if (dest == 'F') finAid->lineUp(student);
            else if (dest == 'C') cashier->lineUp(student);
            else if (dest == 'R') finished->addBack(student);
        }
    }
}


void ServiceCenter::printResult() {
    cout << "\n==================== Simulation Results ====================\n";

    cout << "\nCashier Office Statistics:\n";
    cout << "  -> Mean Wait Time: " << cashier->getMeanWait() << " minutes\n";
    cout << "  -> Longest Wait Time: " << cashier->getLongestWait() << " minutes\n";
    cout << "  -> Mean Idle Time: " << cashier->getMeanIdle() << " minutes\n";
    cout << "  -> Longest Idle Time: " << cashier->getLongestIdle() << " minutes\n";

    cout << "\nFinancial Aid Office Statistics:\n";
    cout << "  -> Mean Wait Time: " << finAid->getMeanWait() << " minutes\n";
    cout << "  -> Longest Wait Time: " << finAid->getLongestWait() << " minutes\n";
    cout << "  -> Mean Idle Time: " << finAid->getMeanIdle() << " minutes\n";
    cout << "  -> Longest Idle Time: " << finAid->getLongestIdle() << " minutes\n";

    cout << "\nRegistrar Office Statistics:\n";
    cout << "  -> Mean Wait Time: " << registrar->getMeanWait() << " minutes\n";
    cout << "  -> Longest Wait Time: " << registrar->getLongestWait() << " minutes\n";
    cout << "  -> Mean Idle Time: " << registrar->getMeanIdle() << " minutes\n";
    cout << "  -> Longest Idle Time: " << registrar->getLongestIdle() << " minutes\n";

    cout << "\nOverall Statistics:\n";
    printWaitOver10();
    printIdleOver5();

    cout << "\n===========================================================\n";
}




/*
void printWaitOver10() - Prints the number of students waiting over 10 minutes total across all offices by iterating through finished
*/
void ServiceCenter::printWaitOver10() {
    int waitOver10 = 0;
    for (int i = 0; i < finished->getSize(); i++) {
        if (finished->get(i)->getTotalWait() >= 10) {
            waitOver10 += finished->get(i)->getTotalWait();
        }
    }
    cout << "Number of Students Waiting over 10 Min: " << waitOver10 << endl;
}



/*
void printIdleOver5() - Prints the number of windows idle for over 5 minutes across all offices by calling Office.getIdleOver5()
*/
void ServiceCenter::printIdleOver5() {
    int amount = cashier->getIdleOver5();
    amount += registrar->getIdleOver5();
    amount += finAid->getIdleOver5();
    cout << "Number of Windows Idle over 5 Min: " << amount << endl;
}



