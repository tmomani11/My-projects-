#ifndef DATABASE_H
#define DATABASE_H
#include "Student.h"
#include "LazyBST.h"
#include "Faculty.h"
#include <iostream>

using namespace std;

// The DataBase class manages a database of students and faculty.//
class DataBase {
public:


    // Prints all students in the database.
    void StudentPrint();

    // Prints all faculty in the database.
    void FacultyPrint();

    // Prints a specific student based on an inputted ID.
    void PrintaStudent();

    // Prints a specific faculty member based on an inputted ID.
    void PrintaFaculty();

    // Deletes a specific student based on an inputted ID.
    void DeleteaStudent();

    // Removes a student from an advisor's Student tree and sets Student advisor to 0.
    void RemoveAdvisee();

    // Changes a student's advisor.
    void ChangeAdvisor();

    // Deletes a specific faculty member based on an inputted ID.
    void DeleteaFaculty();

    // Adds a new student to the database.
    void StudentInput();

    // Adds a new faculty to the database.
    void FacultyInput();



    // Writes all students to an output stream.
    void WriteStudent(ostream& students);

    // Writes all faculty to an output stream.
    void WriteFaculty(ostream& faculty);

    // Writes all students and faculty to a file.
    void WriteFile();

    // Constructor: Initializes the student and faculty binary search trees.
    DataBase();

    // Destructor: Deallocates the memory used by the student and faculty binary search trees.
    ~DataBase();

private:
    // Binary search tree of students.
    LazyBST<Student>* stree;

    // Binary search tree of faculty.
    LazyBST<Faculty>* ftree;
};

#endif