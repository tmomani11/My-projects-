#include <iostream>
#include "Faculty.h"
#include "Student.h"
#include "BST.h"
using namespace std;

Faculty::Faculty(){
    m_FacultyID = 0;
    m_FacultyName = "John Doe";
    m_FacultyLevel = "Freshman";
    m_FacultyDepartment = "Film Production";
    m_FacultyStudents = new BST<Student>();
}

Faculty::Faculty(int i){
    m_FacultyID = i;
    m_FacultyName = "John Doe";
    m_FacultyLevel = "Freshman";
    m_FacultyDepartment = "Film Production";
    m_FacultyStudents = new BST<Student>();
}

Faculty::Faculty(int FacultyID, string FacultyName, string FacultyLevel, string FacultyDepartment){
    m_FacultyID = FacultyID;
    m_FacultyName = FacultyName;
    m_FacultyLevel = FacultyLevel;
    m_FacultyDepartment = FacultyDepartment;
    m_FacultyStudents = new BST<Student>();
}

Faculty::~Faculty(){
}

int Faculty::getFacultyID() const{
  return m_FacultyID;
}

string Faculty::getFacultyName() const{
  return m_FacultyName;
}

string Faculty::getFacultyLevel() const{
  return m_FacultyLevel;
}

string Faculty::getFacultyDepartment() const{
  return m_FacultyDepartment;
}

void Faculty::PrintFacultyStudents() const{
    m_FacultyStudents->printInOrder();
}

void Faculty::AddStudent(Student S) const{
    m_FacultyStudents->insert(S);
}

void Faculty::RemoveStudent(Student S) const{
    m_FacultyStudents->remove(S);
}

bool Faculty::operator!=(Faculty &s) const { return (m_FacultyID != s.m_FacultyID); }

bool Faculty::operator<(Faculty &s) const { return (m_FacultyID < s.m_FacultyID); }

bool Faculty::operator>(Faculty &s) const { return (m_FacultyID > s.m_FacultyID); }

bool Faculty::operator==(Faculty &s) const { return (m_FacultyID == s.m_FacultyID); }

ostream &operator<<(ostream &stream, const Faculty& f) {
  stream << "ID: " << f.getFacultyID() << endl;
  stream << "Name: " << f.getFacultyName() << endl;
  stream << "Level: " << f.getFacultyLevel() << endl;
  stream << "Department: " << f.getFacultyDepartment() << endl;
  stream << "Students:" << endl;
  f.PrintFacultyStudents();
  return stream;
}