#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
public:
  Student();
  Student(int i);
  Student(int StudentID, std::string StudentName, std::string StudentLevel,
          std::string StudentMajor, double StudentGPA, int StudentAdvisor);
  ~Student();

  int getStudentID() const;
  std::string getStudentName() const;
  std::string getStudentLevel() const;
  std::string getStudentMajor() const;
  double getStudentGPA() const;
  int getStudentAdvisor() const;
  void setAdvisor(int i);

  bool operator!=(const Student& s) const;
  bool operator<(const Student& s) const;
  bool operator>(const Student& s) const;
  bool operator==(const Student& s) const;


  friend std::ostream& operator<<(std::ostream &stream, const Student& s);

private:
  int m_StudentID;
  std::string m_StudentName;
  std::string m_StudentLevel;
  std::string m_StudentMajor;
  double m_StudentGPA;
  int m_StudentAdvisor;
};

#endif  // STUDENT_H