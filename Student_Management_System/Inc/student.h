#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

#define NUM_OF_SUBJECTS 5
#define FILE_PATH "data/student.txt"
enum Status {
    FAILED = 0,
    SUCCESS,
};

using namespace std;

class Student{
    int ID;
    string Name;
    string Branch;
    vector<int> Marks;
    float CGPA;

public:
    Student();
    Student(int id, const string &name, const string &branch, const vector<int> &v, float cgpa = 0);
    
    void Calculate_CGPA();
    void display();

    int getId() const;
    const string & getName() const;
    const string & getBranch() const;
    const vector<int> & getMarks() const;
    const float getCGPA();

    void setName(const string &name);
    void setBranch(const string& branch);
    void setMarks(const vector<int> &marks);

};


Status addStudent(vector<Student> &S);
Status viewStudent(const vector<Student> &S);
void viewAllStudent(const vector<Student> &S);
Status updateStudent(vector<Student> &S);
Status deleteStudent(vector<Student> &S);
Status searchStudent(const vector<Student> &S);
Status saveDataToFile(const vector<Student> &S);
Status loadDataToProgram(vector<Student> &S);


#endif