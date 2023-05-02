#include "Faculty.h"
using namespace std;

Faculty::Faculty(){
    m_facultyID = 0;
    m_name = "";
    m_level = "";
    m_department = "";
}

Faculty::Faculty(int facultyID, string name, string level, string department){
    m_facultyID = facultyID;
    m_name = name;
    m_level = level;
    m_department = department;
}

Faculty::~Faculty(){}

void Faculty::printMethod(){
    cout << "Faculty ID: " << m_facultyID<< endl << 
    "Name: " << m_name << endl << "Level: " << m_level << endl <<
    "Department: " << m_department << endl << "Advisees: ";
    for (int i = 0; i < adviseeList.getSize(); i++) {
        cout << adviseeList.get(i) << endl;
    }
    cout << endl;
}
void Faculty::printMethodToFile(ofstream &log){
    log << "Faculty ID: " << m_facultyID<< endl << 
    "Name: " << m_name << endl << "Level: " << m_level << endl <<
    "Department: " << m_department << endl << "Advisees: ";
    for (int i = 0; i < adviseeList.getSize(); i++) {
        log << adviseeList.get(i) << endl;
    }
    log << endl;
}

int Faculty::getFacultyID(){
    return m_facultyID;
}

string Faculty::getName(){
    return m_name;
}

string Faculty::getLevel(){
    return m_level;
}

string Faculty::getDepartment(){
    return m_department;
}

int Faculty::getListSize(){
    return adviseeList.getSize();
}

DblList<int> Faculty::getList(){
    return adviseeList;
}

void Faculty::setFacultyID(int facultyID){
    m_facultyID = facultyID;
}

void Faculty::setName(string name){
    m_name = name;
}

void Faculty::setLevel(string level){
    m_level = level;
}

void Faculty::setDepartment(string department){
    m_department = department;
}

//adds a student to the list of advisees
void Faculty::addAdvisee(int studentID){
    cout << "student with id number " << studentID << "has been added" << endl;
    adviseeList.addFront(studentID);
}

//removes the student from the list of advisees
void Faculty::removeAdvisee(int studentID){
    adviseeList.remove(adviseeList.position(studentID)); 
}

void Faculty::printAdviseeList(){
    adviseeList.print();
}

bool Faculty::operator<=(const Faculty &f){
    return (m_facultyID <= f.m_facultyID);
}

bool Faculty::operator>=(const Faculty &f){
    return (m_facultyID >= f.m_facultyID);
}

bool Faculty::operator<(const Faculty &f){
    return (m_facultyID < f.m_facultyID);
}

bool Faculty::operator>(const Faculty &f){
    return (m_facultyID > f.m_facultyID);
}

bool Faculty::operator==(const Faculty &f){
    return (m_facultyID == f.m_facultyID);
}

bool Faculty::operator!=(const Faculty &f){
    return (m_facultyID != f.m_facultyID);
}