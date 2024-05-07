#include "Student.h"
#include <iostream>

using namespace std;

// Default constructor: Initializes a new student with default values
Student::Student() {
    StudentID = 0;
    StudentName = "";
    StudentLevel = "";
    StudentMajor = "";
    StudentGPA = 0;
    StudentAdvisor = 0;
}

// Overloaded constructor: Initializes a new student with a given ID and default values for other attributes
Student::Student(int i) {
    StudentID = i;
    StudentName = "";
    StudentLevel = "";
    StudentMajor = "";
    StudentGPA = 0;
    StudentAdvisor = 0;
}

// Overloaded constructor: Initializes a new student with given values for all attributes
Student::Student(int StudentID, string StudentName, string StudentLevel,
                 string StudentMajor, double StudentGPA, int StudentAdvisor) {
    this->StudentID = StudentID;
    this->StudentName = StudentName;
    this->StudentLevel = StudentLevel;
    this->StudentMajor = StudentMajor;
    this->StudentGPA = StudentGPA;
    this->StudentAdvisor = StudentAdvisor;
}

// Destructor: Currently empty because there are no dynamically allocated attributes
Student::~Student() {}

// Getter for student ID
int Student::getStudentID() const { return StudentID; }

// Getter for student name
string Student::getStudentName() const { return StudentName; }

// Getter for student level
string Student::getStudentLevel() const { return StudentLevel; }

// Getter for student major
string Student::getStudentMajor() const { return StudentMajor; }

// Getter for student GPA
double Student::getStudentGPA() const { return StudentGPA; }

// Getter for student advisor
int Student::getStudentAdvisor() const { return StudentAdvisor; }

// Setter for student advisor
void Student::setAdvisor(int i) {
    StudentAdvisor = i;
}

// Overloaded comparison operators for comparing students based on their IDs
bool Student::operator<(const Student &s) const {
    return (StudentID < s.StudentID);
}

bool Student::operator>(const Student &s) const {
    return (StudentID > s.StudentID);
}

bool Student::operator==(const Student &s) const {
    return (StudentID == s.StudentID);
}

bool Student::operator!=(const Student &s) const {
    return (StudentID != s.StudentID);
}

// Overloaded stream insertion operator for printing a student
ostream &operator<<(ostream &stream, const Student &s) {
    stream << "ID: " << s.getStudentID() << endl;
    stream << "Name: " << s.getStudentName() << endl;
    stream << "Level: " << s.getStudentLevel() << endl;
    stream << "Major: " << s.getStudentMajor() << endl;
    stream << "GPA: " << s.getStudentGPA() << endl;
    stream << "Advisor: " << s.getStudentAdvisor() << endl;
    return stream;
}