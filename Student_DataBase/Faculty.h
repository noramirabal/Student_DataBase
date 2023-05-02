#ifndef FACULTY_H
#define FACULTY_H

#include "DblList.h"

#include <iostream>
#include <fstream>

using namespace std;
class Faculty{
private:
    int m_facultyID;
    string m_name;
    string m_level;
    string m_department;
    DblList<int> adviseeList;
public: 
    Faculty();
    Faculty(int facultyID, string name, string level, string department);
    ~Faculty();
    int getFacultyID();
    string getName();
    string getLevel();
    string getDepartment();
    int getAdvisees();
    int getListSize();
    DblList<int> getList();
    void setFacultyID(int facultyID);
    void setName(string name);
    void printMethod();
    void printMethodToFile(ofstream &log);
    void setLevel(string level);
    void setDepartment(string major);
    void setAdvisees(int advisees);
    void addAdvisee(int studentID);
    void removeAdvisee(int studentID);
    void printAdviseeList();
    int returnRandomFacultyID(int random);
    bool operator<=(const Faculty &f);
    bool operator>=(const Faculty &f);
    bool operator<(const Faculty &f);
    bool operator>(const Faculty &f);
    bool operator==(const Faculty &f);
    bool operator!=(const Faculty &f);

};

#endif