#include "ServiceCenter.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char** argv){
    //Opens the readfile
    ifstream readfile(argv[1]);
    if(!readfile.is_open()){
        cout << "File not inputted correctly" << endl;
    }
    string line;
    int worldTime = 1;

    //Creates the Service Center
    int wR;
    int wC;
    int wFA;
    getline(readfile, line);
    wR = stoi(line);
    getline(readfile, line);
    wC = stoi(line);
    getline(readfile, line);
    wFA = stoi(line);
    int totalWindows = wR + wC + wFA;
    ServiceCenter* s1 = new ServiceCenter(wR, wC, wFA);

    //Putting the customer's into an array position to store the information
    Customer** arr = new Customer*[100];
    int nextTimeStudents;
    int numStudentsAdd;
    int numStudents = 0;
    while(!readfile.eof()){
        getline(readfile, line);
        nextTimeStudents = stoi(line);
        getline(readfile, line);
        numStudentsAdd = stoi(line) + numStudents;
        for(int i = numStudents; i < numStudentsAdd; ++i){
            getline(readfile, line);
            arr[i] = new Customer(line, nextTimeStudents);
            numStudents++;

        }
    }

    //Creating holding variables to store information for later
    int loopHold = numStudents;
    int* waitingTime = new int[numStudents];
    for(int i = 0; i < numStudents; ++i){
        waitingTime[i] = 0;
    }
    int* windowNumber = new int[numStudents];
    for(int i = 0; i < numStudents; ++i){
        windowNumber[i] = 0;
    }
    int* idleWindow = new int[totalWindows];
    for(int i = 0; i < numStudents; ++i){
        idleWindow[i] = 0;
    }

    // Declare separate variables for each service center
    int meanStudentCashier = 0, meanStudentFinancialAid = 0, meanStudentRegistrar = 0;
    int longestStudentCashier = 0, longestStudentFinancialAid = 0, longestStudentRegistrar = 0;
    int idleStudentsCashier = 0, idleStudentsFinancialAid = 0, idleStudentsRegistrar = 0;
    int meanWindowCashier = 0, meanWindowFinancialAid = 0, meanWindowRegistrar = 0;
    int longestWindowCashier = 0, longestWindowFinancialAid = 0, longestWindowRegistrar = 0;
    int numWindowCashier = 0, numWindowFinancialAid = 0, numWindowRegistrar = 0;

    //Start of the Simulation
    while(loopHold > 0){
        for(int i = 0; i < numStudents; i++){

            //adds the students to queues at the window with the lowest line size
            //also sets if the student is directly at the window or in line
            if(arr[i]->getStartTime() <= worldTime && arr[i]->returnWindow() == false){
                if(arr[i]->currentLocation() == 'R'){
                    int lineToAdd = s1->shortestLine('R');
                    if(s1->queueSizeS('R', lineToAdd) == 0){
                        arr[i]->atWindow(true);
                        s1->addCustomer('R', lineToAdd, arr[i]);
                        windowNumber[i] = lineToAdd;
                    } else {
                        arr[i]->atWindow(false);
                    }
                }
                else if(arr[i]->currentLocation() == 'C'){
                    int lineToAdd = s1->shortestLine('C');
                    if(s1->queueSizeS('C', lineToAdd) == 0){
                        arr[i]->atWindow(true);
                        s1->addCustomer('C', lineToAdd, arr[i]);
                        windowNumber[i] = lineToAdd;
                    } else {
                        arr[i]->atWindow(false);
                    }
                }
                else if(arr[i]->currentLocation() == 'F'){
                    int lineToAdd = s1->shortestLine('F');
                    if(s1->queueSizeS('F', lineToAdd) == 0){
                        arr[i]->atWindow(true);
                        s1->addCustomer('F', lineToAdd, arr[i]);
                        windowNumber[i] = lineToAdd;
                    } else {
                        arr[i]->atWindow(false);
                    }
                }
            }

            //checks if any students at the window are done
            //If they are done at the location and completly it'll remove one from the loophold and set the customer to default values
            //If they are just done at a location it'll send them to their next or just keep their data
            if(arr[i]->timeLeft() == 0){
                s1->nextCustomer(arr[i]->currentLocation(), windowNumber[i]);
                arr[i]->nextLocation();
                if(arr[i]->amountLeft() == 0){
                    loopHold--;
                    arr[i] = new Customer("0 0 0 X X X", -1);
                } else {
                    if(arr[i]->currentLocation() == 'R'){
                        int lineToAdd = s1->shortestLine('R');
                        if(s1->queueSizeS('R', lineToAdd) == 0){
                            arr[i]->atWindow(true);
                            s1->addCustomer('R', lineToAdd, arr[i]);
                            windowNumber[i] = lineToAdd;
                        } else {
                            arr[i]->atWindow(false);
                        }
                    } else if (arr[i]->currentLocation() == 'C'){
                        int lineToAdd = s1->shortestLine('C');
                        if(s1->queueSizeS('C', lineToAdd) == 0){
                            arr[i]->atWindow(true);
                            s1->addCustomer( 'C', lineToAdd, arr[i]);
                            windowNumber[i] = lineToAdd;
                        } else {
                            arr[i]->atWindow(false);
                        }
                    } else if (arr[i]->currentLocation() == 'F'){
                        int lineToAdd = s1->shortestLine('F');
                        if(s1->queueSizeS('F', lineToAdd) == 0){
                            arr[i]->atWindow(true);
                            s1->addCustomer('F', lineToAdd, arr[i]);
                            windowNumber[i] = lineToAdd;
                        } else {
                            arr[i]->atWindow(false);
                        }
                    }
                }
            }

            //Incrementing customer's time or waiting time
            if(arr[i]->returnWindow() == true){
                arr[i]->addTime();
            } else if (!(arr[i]->getStartTime() <= worldTime)){
                waitingTime[i]++;
            }
        }

        //Increament idle time if it needs to be
        for(int i = 0; i < (totalWindows-wC-wFA); i++){
            if(s1->queueSizeS('R', i) == 0){
                idleWindow[i]++;
            }

        }
        for(int i = wR; i < (totalWindows-wFA); i++){
            if(s1->queueSizeS('C', i-wR) == 0){
                idleWindow[i]++;

            }
        }
        for(int i = (wR+wC); i < totalWindows; i++){
            if(s1->queueSizeS('F', i-(wR+wC)) == 0){
                idleWindow[i]++;
            }
        }

        //incrementing world time
        worldTime++;

    }

    //final calculations
    for(int i = 0; i < numStudents; i++){
        if(arr[i]->currentLocation() == 'R'){
            meanStudentRegistrar += waitingTime[i];
            if(waitingTime[i] > longestStudentRegistrar){
                longestStudentRegistrar = waitingTime[i];
            }
            if(waitingTime[i] > 10){
                idleStudentsRegistrar++;
            }
        } else if(arr[i]->currentLocation() == 'C'){
            meanStudentCashier += waitingTime[i];
            if(waitingTime[i] > longestStudentCashier){
                longestStudentCashier = waitingTime[i];
            }
            if(waitingTime[i] > 10){
                idleStudentsCashier++;
            }
        } else if(arr[i]->currentLocation() == 'F'){
            meanStudentFinancialAid += waitingTime[i];
            if(waitingTime[i] > longestStudentFinancialAid){
                longestStudentFinancialAid = waitingTime[i];
            }
            if(waitingTime[i] > 10){
                idleStudentsFinancialAid++;
            }
        }
    }

    for(int i = 0; i < totalWindows; i++){
        if(i < wR){
            meanWindowRegistrar += idleWindow[i];
            if(idleWindow[i] > longestWindowRegistrar){
                longestWindowRegistrar = idleWindow[i];
            }
            if(idleWindow[i] > 5){
                numWindowRegistrar++;
            }
        } else if(i < (wR + wC)){
            meanWindowCashier += idleWindow[i];
            if(idleWindow[i] > longestWindowCashier){
                longestWindowCashier = idleWindow[i];
            }
            if(idleWindow[i] > 5){
                numWindowCashier++;
            }
        } else {
            meanWindowFinancialAid += idleWindow[i];
            if(idleWindow[i] > longestWindowFinancialAid){
                longestWindowFinancialAid = idleWindow[i];
            }
            if(idleWindow[i] > 5){
                numWindowFinancialAid++;
            }
        }
    }

    meanStudentCashier = meanStudentCashier / numStudents;
    meanStudentFinancialAid = meanStudentFinancialAid / numStudents;
    meanStudentRegistrar = meanStudentRegistrar / numStudents;

    meanWindowCashier = meanWindowCashier / totalWindows;
    meanWindowFinancialAid = meanWindowFinancialAid / totalWindows;
    meanWindowRegistrar = meanWindowRegistrar / totalWindows;

    cout << "CASHIER RESULTS" << endl;
    cout << "Average student wait time: " << meanStudentCashier << endl;
    cout << "Longest student wait time: " << longestStudentCashier << endl;
    cout << "Students waiting over 10 mins: " << idleStudentsCashier << endl;
    cout << "Average window idle time: " << meanWindowCashier << endl;
    cout << "Longest window idle time: " << longestWindowCashier << endl;
    cout << "Windows idle over 5 minutes: " << numWindowCashier << endl;

    cout << "FINANCIAL AID RESULTS" << endl;
    cout << "Average student wait time: " << meanStudentFinancialAid << endl;
    cout << "Longest student wait time: " << longestStudentFinancialAid << endl;
    cout << "Students waiting over 10 mins: " << idleStudentsFinancialAid << endl;
    cout << "Average window idle time: " << meanWindowFinancialAid << endl;
    cout << "Longest window idle time: " << longestWindowFinancialAid << endl;
    cout << "Windows idle over 5 minutes: " << numWindowFinancialAid << endl;

    cout << "REGISTRAR RESULTS" << endl;
    cout << "Average student wait time: " << meanStudentRegistrar << endl;
    cout << "Longest student wait time: " << longestStudentRegistrar << endl;
    cout << "Students waiting over 10 mins: " << idleStudentsRegistrar << endl;
    cout << "Average window idle time: " << meanWindowRegistrar << endl;
    cout << "Longest window idle time: " << longestWindowRegistrar << endl;
    cout << "Windows idle over 5 minutes: " << numWindowRegistrar << endl;

    //Deleting all data for no memory leaks
    delete[] waitingTime;
    delete[] idleWindow;
    for(int i = 0; i < loopHold; ++i ){
        delete arr[i];
    }
    delete[] arr;
    delete s1;
}
