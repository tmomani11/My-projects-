#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "Terminal.h"
#include "DataBase.h"
#include <iostream>
using namespace std;

int main() {
bool IsRunning = true;
while (IsRunning == true){
    IsRunning = MainMenu();
}
cout << "Program Ended" << endl;
  return 0;
}