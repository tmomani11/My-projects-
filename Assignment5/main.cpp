
#include "DataBase.h"
#include <iostream>
using namespace std;

int main() {
    DataBase database;
    bool Running = true;
    while (Running){
    int Selection;
    cout << " 1  = Print all students and their information\n";
    cout << " 2  = Print all faculty and their information\n";
    cout << " 3  = Find and display student information given the student id\n";
    cout << " 4  = Find and display faculty information given the faculty id\n";
    cout << " 5  = Add a new student\n";
    cout << " 6  = Delete a student given the id\n";
    cout << " 7  = Add a new faculty member\n";
    cout << " 8  = Delete a faculty member given the id.\n";
    cout << " 9  = Change a student’s advisor given the student id and the new faculty id.\n";
    cout << " 10 = Remove an advisee from a faculty member given the ids\n";
    cout << " 11 = Exit" ;
    cout << "Option: ";
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
             Running = false;
            break;u
        }
    }
cout << "Goodbye! program has ended.\n";
  return 0;
}