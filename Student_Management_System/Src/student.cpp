#include "student.h"
#include <fstream>
#include <sstream>

Student::Student(int id, const string &name, const string &branch, const vector<int> &v, float cgpa) {
    ID  = id;
    Name = name;
    Branch = branch;
    Marks = v;
    CGPA = cgpa;  
}

void Student::Calculate_CGPA() {
    if (Marks.empty()) {
        cout<<"Error: No marks to calculate CGPA\n";
        return;
    }

    int totalPoints = 0;
    for (int mark : Marks) {
        if (mark >= 90)
            totalPoints += 10;
        else if (mark >= 80)
            totalPoints += 9;
        else if (mark >= 70)
            totalPoints += 8;
        else if (mark >= 60)
            totalPoints += 7;
        else if (mark >= 50)
            totalPoints += 6;
        else if (mark >= 40)
            totalPoints += 5;
        else
            totalPoints += 0;
    }
    CGPA = (float)totalPoints / NUM_OF_SUBJECTS;
}
void Student::display() {
    cout<<"Name   : "<<Name<<endl;
    cout<<"ID     : "<<ID<<endl;
    cout<<"Branch : "<<Branch<<endl;
    cout<<"Marks  : ";
    for(int i=0; i<NUM_OF_SUBJECTS; i++) {
        cout<<Marks[i];
        if(i!=4) cout<<",";
    }
    cout<<endl;
    cout<<"CGPA   : "<<CGPA<<endl;
}

int Student::getId() const {
    return ID;
}

const string & Student::getName() const {
    return Name;
}

const string & Student::getBranch() const {
    return Branch;
}

const vector<int> & Student::getMarks() const {
    return Marks;
}

const float Student::getCGPA() {
    if(CGPA == 0) {
        Calculate_CGPA();
    }
    return CGPA;
}

void Student::setName(const string &name) {
    Name = name;
}

void Student::setBranch(const string& branch) {
    Branch = branch;
}

void Student::setMarks(const vector<int> &marks) {
    Marks = marks;
}

Status loadDataToProgram(vector<Student> &S) {
    
    ifstream infile(FILE_PATH);
    if(!infile) {
        cout<<"Error in opening Student details File\n";
        return FAILED;
    }
    int id;
    string name, branch;
    vector<int> marks(5);
    float cgpa;

    string line;
    while(!infile.eof()) {
        getline(infile, line);
        if (line.empty()) continue;

        stringstream ss(line);
        string word;
        
        getline(ss, word, '|');
        id = stoi(word);

        getline(ss, name, '|');
        getline(ss, branch, '|');
        
        for(int i=0; i<NUM_OF_SUBJECTS; i++) {
            getline(ss, word, '|');
            marks[i] = stoi(word);
        }

        getline(ss, word, '|');
        cgpa = stof(word);
        
        Student temp(id,name,branch,marks,cgpa);
        S.push_back(temp);
    }
    
    return SUCCESS;
}

Status saveDataToFile(const vector<Student> &S) {
    ofstream outfile(FILE_PATH, ios::out | ios::trunc);
    if (!outfile) {
        cout<<"Error in Opening Student Details file\n";
        return FAILED;
    }

    for(auto i: S) {
        outfile<<i.getId()<<"|";
        outfile<<i.getName()<<"|";
        outfile<<i.getBranch()<<"|";
        
        vector<int> marks = i.getMarks();
        for(int m : marks) {
            outfile<<m<<"|";
        }

        outfile<<i.getCGPA()<<endl;
    }
    return SUCCESS;
}

Status addStudent(vector<Student> &S) {
    int id;
    string name, branch;
    vector<int> marks(5);

    cout<<"Enter Student ID: ";
    cin>>id;
    for(auto i : S) {
        if (id == i.getId()) {
            cout<<"Duplicate ID\n";
            return FAILED;
        }
    }

    getchar();
    cout<<"Enter Student Name: ";
    getline(cin, name);

    cout<<"Enter Branch: ";
    getline(cin, branch);

    cout<<"Enter 5 subject Marks: ";
    for(int i=0; i<NUM_OF_SUBJECTS; i++) {
        cin>>marks[i];
        if(marks[i] <0 || marks[i] > 100) {
            cout<<"Inavlid Marks\n";
            return FAILED;
        }
    }

    Student temp(id, name, branch, marks);
    temp.Calculate_CGPA();

    S.push_back(temp);

    return SUCCESS;

}

Status viewStudent(const vector<Student> &S) {
    int id;
    cout<<"Enter Student ID: ";
    cin>> id;
    
    for(auto i : S) {
        if (id == i.getId()) {
            cout<<"Student Details:\n";
            i.display();
            return SUCCESS;
        }
    }
    return FAILED;
}

void viewAllStudent(const vector<Student> &S) {
    for(auto i : S) {
        i.display();
    }
}

Status updateStudent(vector<Student> &S) {
    int id;
    cout<<"Enter Student ID: ";
    cin >> id;

    for(auto& i : S) {
        if (id == i.getId()) {
            cout<<"Current Details:\n";
            i.display();
            cout<<"----------------------------\n";
            int choice;
            do {
                cout<<"Press to update\n1) Name\n2) Branch\n3) Marks\n4) Exit\n";
                cin>>choice;
                switch(choice) {
                    case 1:
                    {
                        getchar();
                        string name;
                        cout<<"Enter new name: ";
                        getline(cin, name);
                        i.setName(name);
                        break;
                    }
                    case 2: 
                    {
                        getchar();
                        string branch;
                        cout<<"Enter new branch: ";
                        getline(cin, branch);
                        i.setBranch(branch);
                        break;
                    }
                    case 3: 
                    {
                        vector<int> marks(5);
                        cout<<"Enter new marks: ";
                        for (int i = 0; i < NUM_OF_SUBJECTS; i++) {
                            cin >> marks[i];
                        }
                        i.setMarks(marks);
                        i.Calculate_CGPA();
                        break;
                    }
                    case 4:
                        break;
                    default:
                    cout<<"Enter correct option\n";
                }
            }while(choice != 4);
            return SUCCESS;
        }
    }
    return FAILED;
}

Status deleteStudent(vector<Student> &S) {
    int id;
    cout<<"Enter Student ID: ";
    cin>> id;

    vector<Student> :: iterator it;
    for(it = S.begin(); it!=S.end(); it++) {
        if (id == it->getId()) {
            S.erase(it);
            return SUCCESS;
        }
    }
    return FAILED;
}

static string toLower(string str) {
    for(auto& ch: str) {
        ch = tolower(ch);
    }
    return str;
}

Status searchStudent(const vector<Student> &S) {
    string name;
    cout<<"Enter name to search student: ";
    cin>>name;
    string given_name = toLower(name);

    int flag = 0;
    for(auto i: S) {
        string present_name = i.getName();
        present_name = toLower(present_name);
        if( present_name.find(given_name) != string::npos ) {
            flag = 1;
            cout << i.getName() << " ID (" << i.getId() << ")\n";
        }
    }
    if(flag) {
        cout<<"---------------------------\n";
        cout<<"Is Student you are search Found? Press(Y/N)\n";

        char choice;
        cin>>choice;
        if(choice == 'Y' || choice == 'y') {
            return viewStudent(S);
        }
    }
    return FAILED;
}