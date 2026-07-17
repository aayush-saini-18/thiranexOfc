#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

const string FILE_NAME = "students.txt";

struct Student {
    int id;
    string name;
    int age;
    string department;
    float cgpa;
};

// Load students from file
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(FILE_NAME);

    Student s;

    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.department);
        file >> s.cgpa;
        file.ignore();

        students.push_back(s);
    }

    file.close();
    return students;
}

// Save students to file
void saveStudents(const vector<Student>& students) {
    ofstream file(FILE_NAME);

    for (const auto& s : students) {
        file << s.id << endl;
        file << s.name << endl;
        file << s.age << endl;
        file << s.department << endl;
        file << s.cgpa << endl;
    }

    file.close();
}

bool idExists(const vector<Student>& students, int id) {
    for (const auto& s : students) {
        if (s.id == id)
            return true;
    }
    return false;
}

void addStudent() {
    vector<Student> students = loadStudents();

    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    if (idExists(students, s.id)) {
        cout << "Student ID already exists.\n";
        return;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore();

    cout << "Enter Department: ";
    getline(cin, s.department);

    cout << "Enter CGPA: ";
    cin >> s.cgpa;

    students.push_back(s);

    saveStudents(students);

    cout << "\nStudent added successfully.\n";
}

void displayStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n";
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Department"
         << setw(10) << "CGPA" << endl;

    cout << string(75, '-') << endl;

    for (const auto& s : students) {
        cout << left
             << setw(10) << s.id
             << setw(25) << s.name
             << setw(10) << s.age
             << setw(20) << s.department
             << setw(10) << fixed << setprecision(2) << s.cgpa
             << endl;
    }
}

void searchStudent() {
    vector<Student> students = loadStudents();

    int id;

    cout << "\nEnter Student ID: ";
    cin >> id;

    for (const auto& s : students) {
        if (s.id == id) {
            cout << "\nStudent Found\n";
            cout << "ID         : " << s.id << endl;
            cout << "Name       : " << s.name << endl;
            cout << "Age        : " << s.age << endl;
            cout << "Department : " << s.department << endl;
            cout << "CGPA       : " << fixed << setprecision(2) << s.cgpa << endl;
            return;
        }
    }

    cout << "Student not found.\n";
}

void updateStudent() {
    vector<Student> students = loadStudents();

    int id;

    cout << "\nEnter Student ID to Update: ";
    cin >> id;

    bool found = false;

    for (auto& s : students) {
        if (s.id == id) {

            found = true;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;
            cin.ignore();

            cout << "Enter New Department: ";
            getline(cin, s.department);

            cout << "Enter New CGPA: ";
            cin >> s.cgpa;

            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
        return;
    }

    saveStudents(students);

    cout << "Record updated successfully.\n";
}

void deleteStudent() {
    vector<Student> students = loadStudents();

    int id;

    cout << "\nEnter Student ID to Delete: ";
    cin >> id;

    auto it = remove_if(students.begin(), students.end(),
                        [id](Student s) {
                            return s.id == id;
                        });

    if (it == students.end()) {
        cout << "Student not found.\n";
        return;
    }

    students.erase(it, students.end());

    saveStudents(students);

    cout << "Student deleted successfully.\n";
}

void menu() {
    cout << "\n=====================================\n";
    cout << "      STUDENT MANAGEMENT SYSTEM\n";
    cout << "=====================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

int main() {

    int choice;

    do {

        menu();

        cin >> choice;

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank you for using the Student Management System.\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}