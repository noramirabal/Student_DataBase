#include "Student.h"


Student::Student(){
    m_studentID = 0;
    m_name = "";
    m_level = "";
    m_major = "";
    m_GPA = 0.0;
    m_advisorID = 0;
}

Student::Student(int studentID, string name, string level, string major, double GPA, int advisorID){
    m_studentID = studentID;
    m_name = name;
    m_level = level;
    m_major = major;
    m_GPA = GPA;
    m_advisorID = advisorID;
}

Student::~Student(){}

void Student::printMethod(){
    cout << "Student ID: " << m_studentID << endl <<
    "Name: " << m_name << endl << "Level: " << m_level << endl <<
    "Major: " << m_major << endl << "GPA: " << m_GPA << endl <<
    "Advisor ID: " << m_advisorID << endl;
}

void Student::printMethodToFile(ofstream &log){
    log << "Student ID: " << m_studentID << endl <<
    "Name: " << m_name << endl << "Level: " << m_level << endl <<
    "Major: " << m_major << endl << "GPA: " << m_GPA << endl <<
    "Advisor ID: " << m_advisorID << endl;
    log << endl;
}


int Student::getStudentID(){
    return m_studentID;
}

string Student::getName(){
    return m_name;
}

string Student::getLevel(){
    return m_level;
}

string Student::getMajor(){
    return m_major;
}

double Student::getGPA(){
    return m_GPA;
}

int Student::getAdvisorID(){
    return m_advisorID;
}

void Student::setStudentID(int studentID){
    m_studentID = studentID;
}

void Student::setName(string name){
    m_name = name;
}

void Student::setLevel(string level){
    m_level = level;
}

void Student::setMajor(string major){
    m_major = major;
}

void Student::setGPA(double GPA){
    m_GPA = GPA;
}

void Student::setAdvisorID(int advisorID){
    m_advisorID = advisorID;
}

bool Student::operator<=(const Student &s){
    return (m_studentID <= s.m_studentID);
}

bool Student::operator>=(const Student &s){
    return (m_studentID >= s.m_studentID);
}

bool Student::operator==(const Student &s){
    return (m_studentID == s.m_studentID);
}


bool Student::operator<(const Student &s){
    return (m_studentID < s.m_studentID);
}

bool Student::operator>(const Student &s){
    return (m_studentID > s.m_studentID);
}

bool Student::operator!=(const Student &s){
    return (m_studentID != s.m_studentID);
}


