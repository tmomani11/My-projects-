
#include "Menu.h"
#include "DataBase.h"
#include <iostream>
using namespace std;

Menu::Menu(){
}

Menu::~Menu(){
}

DataBase database;

bool MainMenu(){
    int Selection;
    bool ChoiceMade = false;
    cout << "\n"
         << "=====================================================\n"
         << "|                     Main Menu                     |\n"
         << "=====================================================\n"
         << "|  1  | Print all students and their information    |\n"
         << "|  2  | Print all faculty and their information     |\n"
         << "|  3  | Find and display student information        |\n"
         << "|       (given the student ID)                      |\n"
         << "|  4  | Find and display faculty information        |\n"
         << "|       (given the faculty ID)                      |\n"
         << "|  5  | Add a new student                           |\n"
         << "|  6  | Delete a student (given the ID)             |\n"
         << "|  7  | Add a new faculty member                    |\n"
         << "|  8  | Delete a faculty member (given the ID)      |\n"
         << "|  9  | Change a student's advisor                  |\n"
         << "|       (given the student ID and new faculty ID)   |\n"
         << "| 10  | Remove an advisee from a faculty member     |\n"
         << "|       (given the IDs)                             |\n"
         << "| 11  | Exit                                        |\n"
         << "=====================================================\n"
         << "Choose an option (1-11): ";
    cin >> Selection;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please enter a number between 1 and 11.\n";
        return true;
    }
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
