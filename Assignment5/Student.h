#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

// The Student class represents a student in a university.
class Student {
public:

    // Default constructor: Initializes a new student with default values
    Student();

    // Overloaded constructor: Initializes a new student with a given ID and default values for other attributes
    Student(int i);

    // Overloaded constructor: Initializes a new student with given values for all attributes
    Student(int StudentID, std::string StudentName, std::string StudentLevel,
            std::string StudentMajor, double StudentGPA, int StudentAdvisor);

    // Destructor: Currently empty because there are no dynamically allocated attributes
    ~Student();

    // Getter for student ID
    int getStudentID() const;

    // Getter for student name
    std::string getStudentName() const;

    // Getter for student level
    std::string getStudentLevel() const;

    // Getter for student major
    std::string getStudentMajor() const;

    // Getter for student GPA
    double getStudentGPA() const;

    // Getter for student advisor
    int getStudentAdvisor() const;

    // Setter for student advisor
    void setAdvisor(int i);

    // Overloaded comparison operators for comparing students based on their IDs
    bool operator!=(const Student& s) const;
    bool operator<(const Student& s) const;
    bool operator>(const Student& s) const;
    bool operator==(const Student& s) const;

    // Overloaded stream insertion operator for printing a student
    friend std::ostream& operator<<(std::ostream &stream, const Student& s);

private:
    // Student ID
    int StudentID;

    // Student GPA
    double StudentGPA;

    // Student advisor ID
    int StudentAdvisor;

    // Student name
    std::string StudentName;

    // Student level
    std::string StudentLevel;

    // Student major
    std::string StudentMajor;
};

#endif  // STUDENT_H