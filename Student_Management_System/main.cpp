#include "student.h"

int main() {
    vector<Student> Slist;
    loadDataToProgram(Slist);    
    
    int choice;
    do{
        cout<<"Press\n1)To ADD Student\n2)View Student\n3)View ALL Students\n4)Update Student Detail\n5)Delete student\n6)Search Student\n7)Exit\n";
        cin >> choice;
        
        switch(choice) {
            case 1:
                if(!addStudent(Slist)) {
                    cout<<"Error: Failed to ADD Student\n";
                }
                break;
            case 2:
                if(!viewStudent(Slist)) {
                    cout<<"Error: Student ID Not Found\n";
                }
                break;
            case 3:
                viewAllStudent(Slist);
                break;
            case 4:
                if(!updateStudent(Slist)) {
                    cout<<"Error: Student Not Found\n";
                }
                break;
            case 5:
                if(!deleteStudent(Slist)) {
                    cout<<"Error: Student Not found\n";
                }
                break;
            case 6:
                if(!searchStudent(Slist)) {
                    cout<<"Error: Student Not found\n";
                }
                break;
            case 7:
                break;

        }
    }while(choice != 7);
    
    saveDataToFile(Slist);

    return 0;
}
