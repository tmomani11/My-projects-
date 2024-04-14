
#include "ServiceCenter.h"
#include "Office.h"
#include "Window.h"
#include "ListQueue.h"
#include <cstdlib>
using namespace std;


//Default constructor that takes in the number of windows at each location
ServiceCenter::ServiceCenter(int wRegistrar, int wCashier, int wAid){
    registrar = new Office(wRegistrar);
    cashier = new Office(wCashier);
    financialAid = new Office(wAid);
}

//Default destructor
ServiceCenter::~ServiceCenter(){
    delete registrar;
    delete cashier;
    delete financialAid;
}

//Adds a customer to it's respectic office
void ServiceCenter::addCustomer(char c, int window, Customer* c1){
    switch(c){
        case 'R':
            registrar->addCustomer(c1, window);
            break;
        case 'C':
            cashier->addCustomer(c1, window);
            break;
        case 'F':
            financialAid->addCustomer(c1, window);
            break;
        default:
            break;
    }
}

//returns the shortestline at each office
int ServiceCenter::shortestLine(char c){
    switch(c){
        case 'R':
            return registrar->shortestLine();
            break;
        case 'C':
            return cashier->shortestLine();
            break;
        case 'F':
            return financialAid->shortestLine();
            break;
        default:
            break;
    }
}

//sets the office to it's next customer at the respective location
void ServiceCenter::nextCustomer(char c, int numWindow){
    switch(c){
        case 'R':
            return registrar->nextCustomer(numWindow);
        case 'C':
            return cashier->nextCustomer(numWindow);
        case 'F':
            return financialAid->nextCustomer(numWindow);
        default:
            break;
    }
}

//returns the size of the line at it's respective office and window
int ServiceCenter::queueSizeS(char c, int numWindow){
    switch(c){
        case 'R':
            return registrar->queueSizeOffice(numWindow);
            break;
        case 'C':
            return cashier->queueSizeOffice(numWindow);
        case 'F':
            return financialAid->queueSizeOffice(numWindow);
        default:
            break;
    }
}