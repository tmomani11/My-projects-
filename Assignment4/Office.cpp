
#include "Office.h"
#include "Window.h"
#include "ListQueue.h"
#include <cstdlib>
using namespace std;
 
//Default Constructor 
Office::Office(){
   manager = new Window[0];
   nW = 0;
}

//Overloaded constructor to set number of windows
Office::Office(int numWindows){
   manager = new Window[numWindows];
   nW = numWindows;
}

//Default Destructor
Office::~Office(){
   delete[] manager;
}

//add's a customer to the window line
void Office::addCustomer(Customer* c1, int numWindow){
   manager[numWindow].addCustomer(c1);
}

//returns the window at which the shortest line is at
int Office::shortestLine(){
   int least = manager[0].lineSize();
   int returnInt = 0;
   for(int i = 0; i < nW; ++i){
      if(least > manager[i].lineSize()){
         returnInt = i;
      }
   }
   return returnInt;
}

//sets the window to it's next customer
void Office::nextCustomer(int numWindow){
   return manager[numWindow].nextCustomer();
}

//returns the line size of the specific window
int Office::queueSizeOffice(int numWindow){
   return manager[numWindow].lineSize();
}