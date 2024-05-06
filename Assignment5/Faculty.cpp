#include <iostream>
#include "Faculty.h"
#include "Student.h"
#include "BST.h"
using namespace std;

Faculty::Faculty(){
    FacultyID         = 0;
    FacultyName       = "";
    FacultyLevel      = "";
    FacultyDepartment = "";
    FacultyStudents   = new BST<Student>();
}

Faculty::Faculty(int i){
    FacultyID         = i;
    FacultyName       = "";
    FacultyLevel      = "";
    FacultyDepartment = "";
    FacultyStudents   = new BST<Student>();
}

Faculty::Faculty(int FacultyID, string FacultyName, string FacultyLevel, string FacultyDepartment){
    this->FacultyID    = FacultyID;
    this->FacultyName  = FacultyName;
    this->FacultyLevel = FacultyLevel;
    this->FacultyDepartment = FacultyDepartment;
    FacultyStudents = new BST<Student>();
}

Faculty::~Faculty(){
}

int Faculty::getFacultyID() const{
  return FacultyID;
}

string Faculty::getFacultyName() const{
  return FacultyName;
}

string Faculty::getFacultyLevel() const{
  return FacultyLevel;
}

string Faculty::getFacultyDepartment() const{
  return FacultyDepartment;
}

void Faculty::PrintFacultyStudents() const{
    FacultyStudents->printInOrder();
}

void Faculty::AddStudent(Student S) const{
    FacultyStudents->insert(S);
}

void Faculty::RemoveStudent(Student S) const{
    FacultyStudents->remove(S);
}

bool Faculty::operator!=(Faculty &s) const { return (FacultyID != s.FacultyID); }

bool Faculty::operator<(Faculty &s) const { return (FacultyID < s.FacultyID); }

bool Faculty::operator>(Faculty &s) const { return (FacultyID > s.FacultyID); }

bool Faculty::operator==(Faculty &s) const { return (FacultyID == s.FacultyID); }

ostream &operator<<(ostream &stream, const Faculty& f) {
  stream << "ID: " << f.getFacultyID() << endl;
  stream << "Name: " << f.getFacultyName() << endl;
  stream << "Level: " << f.getFacultyLevel() << endl;
  stream << "Department: " << f.getFacultyDepartment() << endl;
  stream << "Students:" << endl;
  f.PrintFacultyStudents();
  return stream;
}