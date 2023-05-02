#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "SGT.H"
#include "Faculty.h"
#include "Student.h"

using namespace std;
class Database{
private:
    SGT<Student> studentTree;
    SGT<Faculty> facultyTree;
    int m_option;
public:
    Database();
    ~Database();
    void simulation();
    void menuOptions();
    void optionAction(int optionNum);
    void printAllStudents();
    void printAllFaculty();
    void printStudentHelper(Student student);
    void printFacultyHelper(Faculty faculty);
    void printSpecificStudent();
    void printSpecificFaculty();
    void addNewStudent();
    void addNewFaculty();
    void deleteStudent();
    void deleteFaculty();
    void changeAdvisor();
    void removeAdviseeFromFaculty();
    
};

#endif