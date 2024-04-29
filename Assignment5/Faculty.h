#ifndef Faculty_H
#define Faculty_H
#include <iostream>
#include "Student.h"
#include "BST.h"
using namespace std;

class Faculty{
    public:
int getFacultyID() const;
string getFacultyName() const;
string getFacultyLevel() const;
string getFacultyDepartment() const;
void RemoveStudent(Student S) const;
void PrintFacultyStudents() const;
bool operator!=(Faculty &s) const;
bool operator<(Faculty &s) const;
bool operator>(Faculty &s) const;
bool operator==(Faculty &s) const;
void AddStudent(Student S) const;
    // Default constructor
    Faculty();
    Faculty(int i);
    
    // Full constructor
    Faculty(int FacultyID, string FacultyName, string FacultyLevel, string FacultyDepartment);

friend std::ostream& operator<<(std::ostream &stream, const Faculty& f);

    // Destructor
    ~Faculty();
    private:
      int m_FacultyID;
      string m_FacultyName;
      string m_FacultyLevel;
      string m_FacultyDepartment;
      BST<Student>* m_FacultyStudents;
};

#endif