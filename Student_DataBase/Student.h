#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
class Student{
private:
    int m_studentID;
    string m_name;
    string m_level;
    string m_major;
    double m_GPA;
    int m_advisorID;
public: 
    Student();
    Student(int studentID, string name, string level, string major, double GPA, int advisorID);
    ~Student();
    int getStudentID();
    string getName();
    string getLevel();
    string getMajor();
    double getGPA();
    int getAdvisorID();
    void setStudentID(int studentID);
    void setName(string m_name);
    void setLevel(string m_level);
    void setMajor(string m_major);
    void setGPA(double GPA);
    void setAdvisorID(int advisorID);
    void printMethod();
    void printMethodToFile(ofstream &log);

    //Comparison Operators
    bool operator<=(const Student &s);
    bool operator>=(const Student &s);
    bool operator==(const Student &s);
    bool operator<(const Student &s);
    bool operator>(const Student &s);
    bool operator!=(const Student &s);
};

#endif