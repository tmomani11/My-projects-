#include "DataBase.h"
#include "LazyBST.h"
#include "Faculty.h"
#include "Student.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor: Initializes the student and faculty binary search trees
DataBase::DataBase() {
    stree = new LazyBST<Student>();
    ftree = new LazyBST<Faculty>();
}

// Destructor: Deallocates the memory used by the student and faculty binary search trees
DataBase::~DataBase() {
    delete stree;
    delete ftree;
}

// Prints all students in the database
void DataBase::StudentPrint() {
    cout << "All Students: " << endl;
    stree->printInOrder();
}

// Prints all faculty in the database
void DataBase::FacultyPrint() {
    cout << "All Faculty: " << endl;
    ftree->printInOrder();
}

// Prints a specific student based on an inputted ID
void DataBase::PrintaStudent() {
    int i;
    cout << "Enter Student ID #: ";
    cin  >> i;
    Student s = Student(i);
    if (stree->contains(s)) {
        Student myStudent = stree->get(s);
        cout << "\nStudent Information" << endl;
        cout << myStudent << endl;
    } else {
        cout << "No student with ID #: " << i << " found in the database." << endl;
    }
}

// Prints a specific faculty member based on an inputted ID
void DataBase::PrintaFaculty() {
    int i;
    cout << "Enter Faculty ID #: ";
    cin  >> i;
    Faculty f = Faculty(i);
    if (ftree->contains(f)) {
        Faculty myFaculty = ftree->get(f);
        cout << "\nFaculty Information" << endl;
        cout << myFaculty << endl;
    } else {
        cout << "No faculty with ID #: " << i << " found in the database." << endl;
    }
}

// Deletes a specific student based on an inputted ID
void DataBase::DeleteaStudent() {
    int i = 0;
    cout << "Enter Student ID #: ";
    cin >> i;
    Student s = Student(i);
    if (stree->contains(s)) {
        Student myStudent = stree->get(s);
        cout << "Student " << myStudent.getStudentName() << " with ID #: " << i
             << " has been removed from the student database!" << endl;
        stree->remove(s);

        // Get the faculty advisor of the student
        Faculty f = Faculty(myStudent.getStudentAdvisor());
        if (ftree->contains(f)) {
            Faculty myFaculty = ftree->get(f);
            ftree->remove(f);
            myFaculty.RemoveStudent(myStudent); // Remove the student from the faculty's list of students
            ftree->insert(myFaculty);
        }
    } else {
        cout << "No student with ID #: " << i << " found in the database." << endl;
    }
}

// Deletes a specific faculty member based on an inputted ID
void DataBase::DeleteaFaculty() {
    int i;
    cout << "Enter Faculty ID #: ";
    cin >> i;
    Faculty f = Faculty(i);
    if (ftree->contains(f)) {
        Faculty myFaculty = ftree->get(f);
        // Check if there are any students who have this faculty member as their advisor
        if (!myFaculty.getFacultyStudents()->isEmpty()) {
            cout << "Warning: There are students who have this faculty member as their advisor. "
                 << "Deleting this faculty member would break referential integrity. "
                 << "Please reassign these students to another faculty member before deleting this one." << endl;
            return; // Abort the command
        }
        cout << "Faculty " << myFaculty.getFacultyName() << " with ID #: " << i
             << " has been removed from the faculty database!" << endl;
        ftree->remove(f);
    } else {
        cout << "No faculty with ID #: " << i << " found in the database." << endl;
    }
}
void DataBase::RemoveAdvisee() {
    int i;
    int j;
    cout << "Enter Student ID #: ";
    cin >> i;
    cout << "Enter Faculty ID #: ";
    cin >> j;
    Faculty f = Faculty(j);
    if (ftree->contains(f)) {
        Faculty newf = ftree->get(f);
        ftree->remove(f);
        Student s = Student(i);
        if (newf.getFacultyStudents()->contains(s)) {
            Student news = newf.getFacultyStudents()->get(s);
            newf.RemoveStudent(news); // Remove the student from the faculty's list of students
            news.setAdvisor(0); // Set the student's advisor to 0
            cout << "Student with ID #: " << i << " has been removed from the advisor with ID #: " << j << endl;
            cout << "Note: This student needs a new advisor." << endl;
            ftree->insert(newf);
        } else {
            cout << "No student with ID #: " << i << " found under the faculty with ID #: " << j << endl;
        }
    } else {
        cout << "No faculty with ID #: " << j << " found in the database." << endl;
    }
}
// Changes a student's advisor
void DataBase::ChangeAdvisor() {
    int i;
    int j;
    cout << "Enter Student ID #: ";
    cin >> i;
    cout << "Enter New Faculty ID #: ";
    cin >> j;

    Student s = Student(i);
    if (!stree->contains(s)) {
        cout << "No student with ID #: " << i << " found in the database." << endl;
        return;
    }

    Faculty f = Faculty(j);
    if (!ftree->contains(f)) {
        cout << "No faculty with ID #: " << j << " found in the database." << endl;
        return;
    }

    // Get the current student and faculty objects
    Student currentStudent = stree->get(s);
    Faculty newFaculty = ftree->get(f);

    // Remove the current student from the old advisor's list
    Faculty oldFaculty = Faculty(currentStudent.getStudentAdvisor());
    if (ftree->contains(oldFaculty)) {
        oldFaculty = ftree->get(oldFaculty);
        ftree->remove(oldFaculty);
        oldFaculty.RemoveStudent(currentStudent);
        ftree->insert(oldFaculty);
    }

    // Add the student to the new advisor's list
    ftree->remove(newFaculty);
    newFaculty.AddStudent(currentStudent);
    ftree->insert(newFaculty);

    // Update the student's advisor
    stree->remove(currentStudent);
    currentStudent.setAdvisor(j);
    stree->insert(currentStudent);
    cout << "Student " << currentStudent.getStudentName()
    << " has been reassigned to faculty ID #: " << j << endl;
}

// Adds a new student to the database
void DataBase::StudentInput() {
    int StudentID;
    string StudentName;
    string StudentLevel;
    string StudentMajor;
    double StudentGPA;
    int StudentAdvisor;

    cout << "Enter Student ID #: ";
    cin >> StudentID;
    cin.ignore(1000, '\n');

    cout << "Enter Student Name: ";
    getline(cin, StudentName);

    cout << "Enter Student Grade Level: ";
    getline(cin, StudentLevel);

    cout << "Enter Student Major: ";
    getline(cin, StudentMajor);

    cout << "Enter Student GPA: ";
    cin >> StudentGPA;

    cout << "Enter Student Advisor ID #: ";
    cin >> StudentAdvisor;

    Faculty f = Faculty(StudentAdvisor);
    if (!ftree->contains(f)) {
        cout << "\nNO FACULTY WITH ID #: " << StudentAdvisor << " FOUND IN DATABASE"
                                                                ". \n ABORTING\n";
        return;
    }

    Student s = Student(StudentID, StudentName, StudentLevel, StudentMajor, StudentGPA, StudentAdvisor);
    cout << endl;

    Faculty newF = ftree->get(f);
    ftree->remove(f);
    newF.AddStudent(s);
    ftree->insert(newF);

    stree->insert(s);
    cout << StudentName << " has been added to the student database!" << endl;
}

// Adds a new faculty to the database
void DataBase::FacultyInput() {
    int FacultyID;
    string FacultyName;
    string FacultyLevel;
    string FacultyDepartment;
    cout << "Enter Faculty ID #: ";
    cin >> FacultyID;
    cin.ignore(1000, '\n');
    cout << "Enter Faculty Name: ";
    getline(cin, FacultyName);
    cout << "Enter Faculty Level: ";
    getline(cin, FacultyLevel);
    cout << "Enter Faculty Department: ";
    getline(cin, FacultyDepartment);
    Faculty f = Faculty(FacultyID, FacultyName, FacultyLevel, FacultyDepartment);
    cout << endl;
    cout << FacultyName << " has been added to the faculty database!" << endl;
    cout << endl;
    ftree->insert(f);
}

// Writes all students to an output stream
void DataBase::WriteStudent(ostream &students) {
    students << "All Students: " << endl;
    stree->writeInOrder(students);
}

// Writes all faculty to an output stream
void DataBase::WriteFaculty(ostream &faculty) {
    faculty << "All Faculty: " << endl;
    ftree->writeInOrder(faculty);
}

// Writes all students and faculty to a file
void DataBase::WriteFile() {
    ofstream treefile("runLog.txt");

    WriteStudent(treefile);
    WriteFaculty(treefile);

    treefile.close();
}
