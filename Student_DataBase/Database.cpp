#include "Database.h"

#include <fstream>
#include <iostream>

Database::Database(){
    SGT<Student> studentTree;
    SGT<Faculty> facultyTree;
    while (m_option != 11){
        menuOptions();
    }
    //create file named runLog.txt (info from option 1 and option 2 printed to the file instead of terminal)
    ofstream outputFile;
    outputFile.open("runLog.txt");
    studentTree.printToFile(outputFile);
    facultyTree.printToFile(outputFile);
    outputFile.close();

    cout << "database closed" << endl;
}

Database::~Database(){}

void Database::menuOptions(){
    string option;
    cout << "Choose an option from below:" << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Add a new student" << endl;
    cout << "6. Delete a student given the id" << endl;
    cout << "7. Add a new faculty member" << endl;
    cout << "8. Delete a faculty member given the id" << endl;
    cout << "9. Change a student's advisor given the student id and the new faculty id" << endl;
    cout << "10. Remove an advisee from a faculty member given the ids" << endl;
    cout << "11. Exit" << endl;
    cin >> option;
    // if (option != "1" || option != "2" ||option != "3" || option != "4" ||option != "5" || option != "6" ||option != "7" || option != "8" ||option != "9" || option != "10" ||option != "11"){
    //     cout << "that option does not exist" << endl;
    //     menuOptions();
    // }
    m_option = stoi(option);
    optionAction(m_option);
}

void Database::optionAction(int optionNum){
    switch (optionNum) {
        case 1:
            printAllStudents();
            break;
        case 2:
            printAllFaculty();
            break;
        case 3:
            printSpecificStudent();
            break;
        case 4:
            printSpecificFaculty();
            break;
        case 5:
            addNewStudent();
            break;   
        case 6:
            deleteStudent();
            break;
        case 7:
            addNewFaculty();
            break;
        case 8:
            deleteFaculty();
            break;
        case 9:
            changeAdvisor();
            break;
        case 10:
            removeAdviseeFromFaculty();
            break;
        case 11:
            break;
        default:
            cout << "that is not an option" << endl;
            menuOptions();
            break;
    }
}

void Database::printAllStudents(){
    studentTree.printTreeInOrder();
}

void Database::printAllFaculty(){
    facultyTree.printTreeInOrder();
}

void Database::printStudentHelper(Student student){
    cout << "Student ID: " << student.getStudentID() << endl <<
    "Name: " << student.getName() << endl << "Level: " << student.getLevel() << endl <<
    "Major: " << student.getMajor() << endl << "GPA: " << student.getGPA() << endl <<
    "Advisor ID: " << student.getAdvisorID() << endl;
}

void Database::printFacultyHelper(Faculty faculty){
    cout << "Faculty ID: " << faculty.getFacultyID() << endl << 
    "Name: " << faculty.getName() << endl << "Level: " << faculty.getLevel() << endl <<
    "Department: " << faculty.getDepartment() << endl << "Advisees: ";
    faculty.printAdviseeList(); 
    cout << endl;
}

void Database::printSpecificStudent(){
    //asking for the students ID
    string studentIDs;
    cout << "Enter the students ID number" << endl;
    cin >> studentIDs;

    //creating the student and checking for if that student actually exists
    Student *temp = new Student();
    temp->setStudentID(stoi(studentIDs));

    //prompts the user for a student ID until the student exists
    while(!studentTree.exists(temp)){
        cout << "That student didnt exist, please enter the students ID number" << endl;
        cin >> studentIDs;
        temp->setStudentID(stoi(studentIDs));
    }
    Student stu = studentTree.search(temp); 

    //prints out the student
    stu = studentTree.search(temp); 
    printStudentHelper(stu);
}

void Database::printSpecificFaculty(){
    //asking for the faculy's ID
    string facultyIDs;
    cout << "Enter the faculty's ID number" << endl;
    cin >> facultyIDs;

    //creating the faculty and checking for if that faculty actually exists
    Faculty *temp = new Faculty();
    temp->setFacultyID(stoi(facultyIDs));

    //prompts the user for a faculty ID until the faculty exists
    while(!facultyTree.exists(temp)){
        cout << "Enter the faculty's ID number" << endl;
        cin >> facultyIDs;
        temp->setFacultyID(stoi(facultyIDs));
    }
    Faculty fac = facultyTree.search(temp); 

    //prints out the faculty
    fac = facultyTree.search(temp);
    printFacultyHelper(fac);
}

void Database::addNewStudent(){
    //grabbing the student's characteristics
    string studentIDs;
    string name;
    string level;
    string major;
    string GPAs;
    string studentAdvisors;

    cout << "please provide student's ID" << endl;
    cin >> studentIDs;
    cout << "please provide student's name" << endl;
    cin >> name;
    cout << "please provide student's level" << endl;
    cin >> level;
    cout << "please provide student's major" << endl;
    cin >> major;
    cout << "please provide student's GPA" << endl;
    cin >> GPAs;
    cout << "please provide student's Advisor ID" << endl;
    cin >> studentAdvisors;

    //creating and adding the student
    Student newStudent(stoi(studentIDs), name, level, major, stod(GPAs), stoi(studentAdvisors));
    studentTree.insert(newStudent);

    //creating a temp faculty to search for the faculty member with that given ID in the tree
    Faculty* temp = new Faculty();
    temp->setFacultyID(stoi(studentAdvisors));

    //checks that the faculty actually exists and prompt sthe user to enter an ID until a faculty member does exist
    while (!facultyTree.exists(temp)){
        cout << "that faculty member does not exist, please enter a new faculty ID" << endl;
        cin >> studentAdvisors;
        temp->setFacultyID(stoi(studentAdvisors));
    }
    Faculty fac = facultyTree.search(temp); 

    //adds the student to the faculty's ID list
    fac.addAdvisee(stoi(studentIDs));

    cout << "student has been successfully added" << endl;
}

void Database::addNewFaculty(){
    //grabbing the faculty's characteristics
    string facultyIDs;
    string name;
    string level;
    string department;
    string advisees;

    cout << "please provide faculty's ID" << endl;
    cin >> facultyIDs;
    cout << "please provide faculty's name" << endl;
    cin >> name;
    cout << "please provide faculty's level" << endl;
    cin >> level;
    cout << "please provide faculty's department" << endl;
    cin >> department;

    //creating and adding the faculty
    Faculty newFaculty(stoi(facultyIDs), name, level, department);
    facultyTree.insert(newFaculty);
}

void Database::deleteStudent(){
    //grabbing the student's ID
    string studentIDs;

    cout << "please provide the ID of the student to delete" << endl;
    cin >> studentIDs;

    //creating that student
    Student* studentToDelete = new Student();
    studentToDelete->setStudentID(stoi(studentIDs));

    //checking if the student exists and if it doesn't prompting the user for a new student
    while (!studentTree.exists(studentToDelete)){
        cout << "please provide the ID of the student to delete" << endl;
        cin >> studentIDs;
        studentToDelete->setStudentID(stoi(studentIDs));
    }

    Student stu = studentTree.search(studentToDelete);

    //deletes the student from the faculty's advisee list
    Faculty* temp = new Faculty();
    temp->setFacultyID(studentToDelete->getAdvisorID());
    Faculty fac = facultyTree.search(temp); 
    fac.removeAdvisee(stoi(studentIDs));

    //removes the student from the database
    studentTree.remove(stu); 
}

void Database::deleteFaculty(){
    //grabbing the faculty's ID
    string facultyIDs;

    cout << "please provide the ID of the faculty to delete" << endl;
    cin >> facultyIDs;

    Faculty* facultyToDelete = new Faculty();
    facultyToDelete->setFacultyID(stoi(facultyIDs));

    //checks if the faculty exists 
    while(!facultyTree.exists(facultyToDelete)){
        cout << "please provide the ID of the faculty to delete" << endl;
        cin >> facultyIDs;
        facultyToDelete->setFacultyID(stoi(facultyIDs));
    }
    Faculty facu = facultyTree.search(facultyToDelete);

    // DblList<int> tempList = facultyToDelete->getList();
    // for (int i = 0; facu.getListSize(); ++i){

    // }
    facultyTree.remove(facu);

    //redistributes the faculty's advisees
    DblList<int> tempList = facultyToDelete->getList();

    for (int i = 0; facultyToDelete->getListSize(); ++i){
        Student* stu = new Student();
        stu->setStudentID(tempList.removeBack());
        Student student = studentTree.search(stu);
        
    }
    facultyTree.remove(facu); 
}

void Database::changeAdvisor(){
    string studentIDs;
    string facultyIDs;

    cout << "please provide the ID of the student to switch" << endl;
    cin >> studentIDs;
    cout << "please provide the ID of the faculty to switch the student to" << endl;
    cin >> facultyIDs;

    Student* tempStudent = new Student();
    tempStudent->setStudentID(stoi(studentIDs));

    Faculty* newFaculty = new Faculty();
    newFaculty->setFacultyID(stoi(facultyIDs));

    //checking if that student actually exists and prompts until it does
    while (!studentTree.exists(tempStudent)){
        cout << "please provide the ID of the student to delete" << endl;
        cin >> studentIDs;
        tempStudent->setStudentID(stoi(studentIDs));
    }

    //checking if that faculty actuallys exists and prompts until it does
    while (!facultyTree.exists(newFaculty)){
        cout << "that faculty member does not exist, please enter a new faculty ID" << endl;
        cin >> facultyIDs;
        newFaculty->setFacultyID(stoi(facultyIDs));
    }
    
    cout << "created student and faculty" << endl;
    Student stu = studentTree.search(tempStudent);
    Faculty* oldFaculty = new Faculty();
    oldFaculty->setFacultyID(stu.getAdvisorID());
    Faculty oldFac = facultyTree.search(oldFaculty);
    Faculty newFac = facultyTree.search(newFaculty);
    stu = studentTree.search(tempStudent); 
    oldFac = facultyTree.search(oldFaculty); 
    newFac = facultyTree.search(newFaculty); 

    //changes the student's advisor ID to the new faculty
    tempStudent->setAdvisorID(stoi(facultyIDs));

    //removes the student's ID from the past faculty's advisee list
    oldFaculty->removeAdvisee(stoi(studentIDs));

    //adds the student's ID to the new faculty's adviseelist
    newFaculty->addAdvisee(stoi(studentIDs));

}

void Database::removeAdviseeFromFaculty(){
    string studentIDs;
    string facultyIDs;

    cout << "please provide the ID of the student to remove" << endl;
    cin >> studentIDs;

    //make the temp objects
    Student* tempStu = new Student();
    tempStu->setStudentID(stoi(studentIDs));

    //checking if that student actually exists and prompts until it does
    while (!studentTree.exists(tempStu)){
        cout << "please provide the ID of the student to delete" << endl;
        cin >> studentIDs;
        tempStu->setStudentID(stoi(studentIDs));
    }

    Student stu = studentTree.search(tempStu);
    Faculty* tempOldFacu = new Faculty();
    tempOldFacu->setFacultyID(stu.getAdvisorID());
    Faculty oldFac = facultyTree.search(tempOldFacu);

    //remove the advisee
    oldFac.removeAdvisee(stoi(studentIDs));

    //add the student to another random faculty member
    Faculty newFacu = facultyTree.getRootData();
    newFacu.addAdvisee(stoi(studentIDs));
}



