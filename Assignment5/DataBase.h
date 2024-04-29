#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include "BST.h"
#include "Faculty.h"
#include <iostream>

using namespace std;

class DataBase {
public:
    void SaveToFile();
    void StudentPrint();
    void FacultyPrint();
    void PrintaStudent();
    void PrintaFaculty();
    void DeleteaStudent();
    void RemoveAdvisee();
    void ChangeAdvisor();
    void DeleteaFaculty();
    void StudentInput();
    void FacultyInput();
    void PrintStudentTree();
    void WriteStudent(ostream& students);
    void WriteFaculty(ostream& faculty);
    void WriteFile();
    DataBase();
    ~DataBase();
private:
    BST<Student>* stree;
    BST<Faculty>* ftree;
    
};

#endif