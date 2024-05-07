#include <iostream>
#include "Faculty.h"
#include "Student.h"
#include "BST.h"
using namespace std;

// Default constructor: Initializes a new faculty with default values
Faculty::Faculty(){
    FacultyID         = 0;
    FacultyName       = "";
    FacultyLevel      = "";
    FacultyDepartment = "";
    FacultyStudents   = new BST<Student>();
}

// Overloaded constructor: Initializes a new faculty with a given ID and default values for other attributes
Faculty::Faculty(int i){
    FacultyID         = i;
    FacultyName       = "";
    FacultyLevel      = "";
    FacultyDepartment = "";
    FacultyStudents   = new BST<Student>();
}

// Overloaded constructor: Initializes a new faculty with given values for all attributes
Faculty::Faculty(int FacultyID, string FacultyName, string FacultyLevel, string FacultyDepartment){
    this->FacultyID    = FacultyID;
    this->FacultyName  = FacultyName;
    this->FacultyLevel = FacultyLevel;
    this->FacultyDepartment = FacultyDepartment;
    FacultyStudents = new BST<Student>();
}

// Destructor: Currently empty because the BST<Student> is not dynamically allocated
Faculty::~Faculty(){
}

// Getter for faculty ID
int Faculty::getFacultyID() const{
    return FacultyID;
}

// Getter for faculty name
string Faculty::getFacultyName() const{
    return FacultyName;
}

// Getter for faculty level
string Faculty::getFacultyLevel() const{
    return FacultyLevel;
}

// Getter for faculty department
string Faculty::getFacultyDepartment() const{
    return FacultyDepartment;
}

// Prints all students of this faculty
void Faculty::PrintFacultyStudents() const{
    FacultyStudents->printInOrder();
}

// Adds a student to this faculty's list of students
void Faculty::AddStudent(Student S) const{
    FacultyStudents->insert(S);
}

// Removes a student from this faculty's list of students
void Faculty::RemoveStudent(Student S) const{
    FacultyStudents->remove(S);
}

// Overloaded comparison operators for comparing faculties based on their IDs
bool Faculty::operator!=(Faculty &s) const { return (FacultyID != s.FacultyID); }
bool Faculty::operator<(Faculty &s) const { return (FacultyID < s.FacultyID); }
bool Faculty::operator>(Faculty &s) const { return (FacultyID > s.FacultyID); }
bool Faculty::operator==(Faculty &s) const { return (FacultyID == s.FacultyID); }

// Getter for the list of students of this faculty
BST<Student>* Faculty::getFacultyStudents() const {
    return FacultyStudents;
}

// Overloaded stream insertion operator for printing a faculty
ostream &operator<<(ostream &stream, const Faculty& f) {
    stream << "ID: " << f.getFacultyID() << endl;
    stream << "Name: " << f.getFacultyName() << endl;
    stream << "Level: " << f.getFacultyLevel() << endl;
    stream << "Department: " << f.getFacultyDepartment() << endl;
    stream << "Students:" << endl;
    f.PrintFacultyStudents();
    return stream;
}