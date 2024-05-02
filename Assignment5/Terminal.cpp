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
  int Selection;
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

    switch (Selection) {
        case 1:
            database.StudentPrint();
            break;
        case 2:
            database.FacultyPrint();
            break;
        case 3:
            database.PrintaStudent();
            break;
        case 4:
            database.PrintaFaculty();
            break;
        case 5:
            database.StudentInput();
            break;
        case 6:
            database.DeleteaStudent();
            break;
        case 7:
            database.FacultyInput();
            break;
        case 8:
            database.DeleteaFaculty();
            break;
        case 9:
            database.ChangeAdvisor();
            break;
        case 10:
            database.RemoveAdvisee();
            break;
        case 11:
            database.WriteFile();
            return false;
        default:
            cout << "Invalid input, please enter a valid number." << endl;
    }
    return true;


}
