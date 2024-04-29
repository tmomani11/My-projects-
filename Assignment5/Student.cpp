#include "Student.h"
#include "Terminal.h"
#include <iostream>
using namespace std;

Student::Student() {
  m_StudentID = 0;
  m_StudentName = "John Doe";
  m_StudentLevel = "Freshman";
  m_StudentMajor = "Film Production";
  m_StudentGPA = 0;
  m_StudentAdvisor = 0;
}

Student::Student(int i) {
  m_StudentID = i;
  m_StudentName = "John Doe";
  m_StudentLevel = "Freshman";
  m_StudentMajor = "Film Production";
  m_StudentGPA = 0;
  m_StudentAdvisor = 0;
}

Student::Student(int StudentID, string StudentName, string StudentLevel,
                 string StudentMajor, double StudentGPA, int StudentAdvisor) {
  m_StudentID = StudentID;
  m_StudentName = StudentName;
  m_StudentLevel = StudentLevel;
  m_StudentMajor = StudentMajor;
  m_StudentGPA = StudentGPA;
  m_StudentAdvisor = StudentAdvisor;
}

Student::~Student() {}

int Student::getStudentID() const { return m_StudentID; }

string Student::getStudentName() const { return m_StudentName; }

string Student::getStudentLevel() const { return m_StudentLevel; }

string Student::getStudentMajor() const { return m_StudentMajor; }

double Student::getStudentGPA() const { return m_StudentGPA; }

int Student::getStudentAdvisor() const { return m_StudentAdvisor; }

void Student::setAdvisor(int i){
    m_StudentAdvisor = i;
}

bool Student::operator<(const Student& s) const {
    return (m_StudentID < s.m_StudentID);
}

bool Student::operator>(const Student& s) const {
    return (m_StudentID > s.m_StudentID);
}

bool Student::operator==(const Student& s) const {
    return (m_StudentID == s.m_StudentID);
}

bool Student::operator!=(const Student& s) const {
    return (m_StudentID != s.m_StudentID);
}


ostream &operator<<(ostream &stream, const Student& s) {
  stream << "ID: " << s.getStudentID() << endl;
  stream << "Name: " << s.getStudentName() << endl;
  stream << "Level: " << s.getStudentLevel() << endl;
  stream << "Major: " << s.getStudentMajor() << endl;
  stream << "GPA: " << s.getStudentGPA() << endl;
  stream << "Advisor: " << s.getStudentAdvisor() << endl;
  return stream;
}