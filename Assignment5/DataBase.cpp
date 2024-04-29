#include "DataBase.h"
#include "BST.h"
#include "Faculty.h"
#include "Student.h"
#include "Terminal.h"
#include "TreeNode.h"
#include <fstream>
#include <iostream>
using namespace std;


DataBase::DataBase() {
  stree = new BST<Student>();
  ftree = new BST<Faculty>();
}

DataBase::~DataBase(){
}

void DataBase::StudentPrint() { //uses pre made PrintIO function to print Students based on ID
  cout << "All Students: " << endl;
  stree->printInOrder();
}

void DataBase::FacultyPrint() { // Same for faculty
  cout << "All Faculty: " << endl;
  ftree->printInOrder();
}

void DataBase::PrintaStudent(){ //Prints one student based on an inputed ID
    int i;
    cout << "Enter Student ID #: "; 
    cin >> i;
    Student s = Student(i);
    Student myStudent = stree->get(s);
    cout << myStudent << endl;
}

void DataBase::PrintaFaculty(){ //Prints one faculty member based on an inputed ID
    int i;
    cout << "Enter Faculty ID #: ";
    cin >> i;
    Faculty f = Faculty(i);
    Faculty myFaculty = ftree->get(f);
    cout << myFaculty << endl;
}

void DataBase::DeleteaStudent(){ //Deletes one student based on an inputed ID
    int i;
    cout << "Enter Student ID #: ";
    cin >> i;
    Student s = Student(i);
    stree->remove(s);
}

void DataBase::DeleteaFaculty(){ //Deletes one faculty member based on an inputed ID
    int i;
    cout << "Enter Faculty ID #: ";
    cin >> i;
    Faculty f = Faculty(i);
    ftree->remove(f);
}

void DataBase::RemoveAdvisee(){ //Removes a student from and adivors Student tree and sets Student advisor to 0
    int i;
    int j;
    cout << "Enter Student ID #: ";
    cin >> i;
    cout << "Enter Faculty ID #: ";
    cin >> j;
    Faculty f = Faculty(j);
    Faculty newf = ftree->get(f);
    ftree->remove(f);
    Student s = Student(i);
    Student news = stree->get(s);
    stree->remove(s);
    news.setAdvisor(0);
    stree->insert(news);
    newf.RemoveStudent(s);
    ftree->insert(newf);
}


void DataBase::ChangeAdvisor(){ //Takes in a student and a new adivsor and then switches the students old advisor with the new
    int i;
    int j;
    int q;
    cout << "Enter Student ID #: ";
    cin >> i;
    cout << "Enter New Faculty ID #: ";
    cin >> j;

    Student s = Student(i);
    Student news = stree->get(s);
    stree->remove(news);
    Faculty f = Faculty(j);
    Faculty newf = ftree->get(f);
    ftree->remove(f);
    newf.AddStudent(news);
    ftree->insert(newf);
    q = news.getStudentAdvisor();
    Faculty z = Faculty(q);
    ftree->remove(z);
    Faculty oldf = ftree->get(z);
    oldf.RemoveStudent(news);
    ftree->insert(newf);
    news.setAdvisor(j);
    stree->insert(news);
}



 

void DataBase::StudentInput() { //creates a new student and places it in the tree. Also assigns student to adivsors tree
  int StudentID;
  string StudentName;
  string StudentLevel;
  string StudentMajor;
  double StudentGPA;
  int StudentAdvisor;
  cout << "Enter Student ID #: ";
  cin >> StudentID;
  cout << "Enter Student Name: ";
  cin >> StudentName;
  cout << "Enter Student Grade Level: ";
  cin >> StudentLevel;
  cout << "Enter Student Major: ";
  cin >> StudentMajor;
  cout << "Enter Student GPA: ";
  cin >> StudentGPA;
  cout << "Enter Student Advisor ID #: ";
  cin >> StudentAdvisor;
  Student s = Student(StudentID, StudentName, StudentLevel, StudentMajor,StudentGPA, StudentAdvisor);
  cout << endl;
  cout << StudentName << " has been added to the student database!" << endl;
  cout << endl;
  stree->insert(s);
  Faculty f = Faculty(StudentAdvisor);
  if (ftree->contains(f)){
    Faculty newF = ftree->get(f);
    ftree->remove(f);
    newF.AddStudent(s);
    ftree->insert(newF);
  }
}

void DataBase::FacultyInput() { //Creates new faculty adn assigns them to a tree
  int FacultyID;
  string FacultyName;
  string FacultyLevel;
  string FacultyDepartment;
  int FacultyStudents;
  cout << "Enter Faculty ID #: ";
  cin >> FacultyID;
  cout << "Enter Faculty Name: ";
  cin >> FacultyName;
  cout << "Enter Faculty Level: ";
  cin >> FacultyLevel;
  cout << "Enter Faculty Department: ";
  cin >> FacultyDepartment;
  Faculty f = Faculty(FacultyID, FacultyName, FacultyLevel, FacultyDepartment);
  cout << endl;
  cout << FacultyName << " has been added to the faculty database!" << endl;
  cout << endl;
  ftree->insert(f);
}

void DataBase::WriteStudent(ostream& students) { //used to write tree.txt (same concepts as StudentPrint())
    students << "All Students: " << endl;
    stree->writeInOrder(students);
}

void DataBase::WriteFaculty(ostream& faculty) {
    faculty << "All Faculty: " << endl;
    ftree->writeInOrder(faculty);
}

void DataBase::WriteFile() {
    ofstream treefile("tree.txt");
    
    WriteStudent(treefile);
    WriteFaculty(treefile);
    
    treefile.close();
}