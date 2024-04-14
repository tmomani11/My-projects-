
#include "Window.h"
#include "Customer.h"
#include "ListQueue.h"
#include <cstdlib>
using namespace std;

//Default Constructor
Window::Window(){
    queueAtWindow = new ListQueue<Customer*>();
}

//Default Destructor
Window::~Window(){
    for(int i = 0; i < queueAtWindow->size(); ++i){
        queueAtWindow->remove();
    }
    delete queueAtWindow;
}

//sets the window to it's next customer
void Window::nextCustomer(){
    queueAtWindow->remove();
}

//adds the customer to a window
void Window::addCustomer(Customer* c){
    queueAtWindow->add(c);
}

//returns the line size at the window
int Window::lineSize(){
    return queueAtWindow->size();
}