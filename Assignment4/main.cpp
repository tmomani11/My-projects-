
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
  int meanStudent = 0;
  int longestStudent = waitingTime[0];
  int idleStudents = 0;
  int meanWindow = 0;
  int longestWindow = idleWindow[0];
  int numWindow = 0;

  for(int i = 0; i < numStudents; i++){
    meanStudent += waitingTime[i];
    if(waitingTime[i] > longestStudent){
      longestStudent = waitingTime[i];
    }
    if(waitingTime[i] > 10){
      idleStudents++;
    }
  }

  meanStudent = meanStudent / numStudents;

  for(int i = 0; i < totalWindows; i++){
    meanWindow += idleWindow[i];
    if(idleWindow[i] > longestStudent){
      longestWindow = idleWindow[i];
    }
    if(idleWindow[i] > 5){
      numWindow++;
    }
  }

  meanWindow = meanWindow / totalWindows;


  cout << "Mean student wait time " << meanStudent << endl;
  cout << "Longest student wait time: " << longestStudent << endl;
  cout << "Students waiting over 10 mins: " << idleStudents << endl;
  cout << "Mean window idle time: " << meanWindow << endl;
  cout << "Longest window idle time: " << longestWindow << endl;
  cout << "Windows idle over 5 minutes: " << numWindow << endl;


  //Deleting all data for no memory leaks
  delete[] waitingTime;
  delete[] idleWindow;
  for(int i = 0; i < loopHold; ++i ){
    delete arr[i];
  }
  delete[] arr;
  delete s1;
}