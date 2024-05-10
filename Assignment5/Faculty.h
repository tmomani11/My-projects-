#ifndef Faculty_H
#define Faculty_H
#include <iostream>
#include "Student.h"
#include "LazyBST.h"
using namespace std;

// The Faculty class represents a faculty member in a university.
class Faculty{
public:
    // Getter for faculty ID
    int getFacultyID() const;

    // Getter for faculty name
    string getFacultyName() const;

    // Getter for faculty level
    string getFacultyLevel() const;

    // Getter for faculty department
    string getFacultyDepartment() const;
    void PrintFacultyStudents(ostream &stream) const ;

    // Removes a student from this faculty's list of students
    void RemoveStudent(Student S) const;

    // Prints all students of this faculty
    void PrintFacultyStudents() const;

    // Overloaded comparison operators for comparing faculties based on their IDs
    bool operator!=(Faculty &s) const;
    bool operator<(Faculty &s) const;
    bool operator>(Faculty &s) const;
    bool operator==(Faculty &s) const;

    // Adds a student to this faculty's list of students
    void AddStudent(Student S) const;

    // Getter for the list of students of this faculty
    LazyBST<Student>* getFacultyStudents() const;

    // Default constructor: Initializes a new faculty with default values
    Faculty();

    // Overloaded constructor: Initializes a new faculty with a given ID and default values for other attributes
    Faculty(int i);

    // Full constructor: Initializes a new faculty with given values for all attributes
    Faculty(int FacultyID, string FacultyName, string FacultyLevel, string FacultyDepartment);

    // Overloaded stream insertion operator for printing a faculty
    friend std::ostream& operator<<(std::ostream &stream, const Faculty& f);
    // Destructor: Currently empty because the BST<Student> is not dynamically allocated
    ~Faculty();


private:
    // Faculty ID
    int FacultyID;

    // Faculty name
    string FacultyName;

    // Faculty level
    string FacultyLevel;

    // Faculty department
    string FacultyDepartment;

    // Binary search tree of students of this faculty
    LazyBST<Student>* FacultyStudents;
};

#endif