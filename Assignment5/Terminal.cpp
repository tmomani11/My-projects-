#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "Terminal.h"
#include "DataBase.h"
#include <iostream>
using namespace std;

Terminal::Terminal(){
}

Terminal::~Terminal(){
}

DataBase database;

bool MainMenu(){
  string Selection;
  bool ChoiceMade = false;
cout << " 1 = Print all students and their information" <<endl;
cout << " 2 = Print all faculty and their information" <<endl;
cout << " 3 = Find and display student information given the student id" <<endl;
cout << " 4 = Find and display faculty information given the faculty id" <<endl;
cout << " 5 = Add a new student" <<endl;
cout << " 6 = Delete a student given the id" <<endl;
cout << " 7 = Add a new faculty member" <<endl;
cout << " 8 = Delete a faculty member given the id." <<endl;
cout << " 9 = Change a student’s advisor given the student id and the new faculty id." <<endl;
cout << " 10 = Remove an advisee from a faculty member given the ids" <<endl;
cout << " 11 = Exit" << endl;
cin >> Selection;

  if (Selection == "1"){
    database.StudentPrint();
    return true;
  }
  if (Selection == "2"){
    database.FacultyPrint();
    return true;
  }
  if (Selection == "3"){
    database.PrintaStudent();
    return true;
  }
  if (Selection == "4"){
    database.PrintaFaculty();
    return true;
  }
  if (Selection == "5"){
    database.StudentInput();
    return true;
  }
  if (Selection == "6"){
    database.DeleteaStudent();
    return true;
  }
  if (Selection == "7"){
    database.FacultyInput();
    return true;
  }
  if (Selection == "8"){
    database.DeleteaFaculty();
    return true;
  }
  if (Selection == "9"){
    database.ChangeAdvisor();
    return true;
  }
  if (Selection == "10"){
    database.RemoveAdvisee();
    return true;
  }
  if (Selection == "11"){
    database.WriteFile();
    return false;
  }
  else{
    cout << "Invaid input, please enter a valid number." << endl;
    return true;

  }
}
