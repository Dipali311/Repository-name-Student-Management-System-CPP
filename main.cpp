#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class Student {
public:
    int roll;
    string name;
    int age;
    string course;

    void input() {
        while (true) {
            cout << "Enter Roll Number: ";
            cin >> roll;
            if (cin.fail() || roll <= 0) {
                cout << "❌ Invalid roll number!\n";
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        while (true) {
            cout << "Enter Age: ";
            cin >> age;
            if (cin.fail() || age <= 0) {
                cout << "❌ Invalid age!\n";
                cin.clear();
                cin.ignore(1000, '\n');
            } else break;
        }
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << "\n-----------------------------\n";
        cout << "📌 Roll   : " << roll << endl;
        cout << "👤 Name   : " << name << endl;
        cout << "🎂 Age    : " << age << endl;
        cout << "📚 Course : " << course << endl;
        cout << "-----------------------------\n";
    }
};

vector<Student> students;

// ---------- Utility ----------
bool isDuplicate(int roll) {
    for (const auto& s : students) {
        if (s.roll == roll) return true;
    }
    return false;
}

// ---------- File Handling ----------
void loadFromFile() {
    ifstream file("students.txt");
    if (!file) return;

    students.clear();

    while (true) {
        Student s;

        if (!(file >> s.roll)) break;
        file.ignore();

        if (!getline(file, s.name)) break;

        if (!(file >> s.age)) break;
        file.ignore();

        if (!getline(file, s.course)) break;

        students.push_back(s);
    }

    file.close();
}

void saveToFile() {
    ofstream file("students.txt", ios::trunc);

    for (const auto& s : students) {
        file << s.roll << "\n"
             << s.name << "\n"
             << s.age << "\n"
             << s.course << "\n";
    }

    file.close();
}

// ---------- Core Functions ----------
void addStudent() {
    Student s;

    cout << "Enter Roll Number: ";
    cin >> s.roll;

    if (cin.fail() || s.roll <= 0) {
        cout << "❌ Invalid roll number!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if (isDuplicate(s.roll)) {
        cout << "❌ Roll number already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);

    while (true) {
        cout << "Enter Age: ";
        cin >> s.age;
        if (cin.fail() || s.age <= 0) {
            cout << "❌ Invalid age!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        } else break;
    }
    cin.ignore();

    cout << "Enter Course: ";
    getline(cin, s.course);

    students.push_back(s);
    saveToFile();

    cout << "\n✅ Student added successfully!\n";
}

void displayAllStudents() {
    if (students.empty()) {
        cout << "\n⚠️ No students found!\n";
        return;
    }

    for (const auto& s : students) {
        s.display();
    }
}

void searchStudent() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    for (const auto& s : students) {
        if (s.roll == roll) {
            cout << "\n🎯 Student Found:\n";
            s.display();
            return;
        }
    }
    cout << "\n❌ Student not found!\n";
}

void updateStudent() {
    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;

    for (auto& s : students) {
        if (s.roll == roll) {
            cout << "\n✏️ Enter new details:\n";
            s.input();
            saveToFile();
            cout << "\n✅ Updated successfully!\n";
            return;
        }
    }
    cout << "\n❌ Student not found!\n";
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll == roll) {
            students.erase(it);
            saveToFile();
            cout << "\n🗑️ Deleted successfully!\n";
            return;
        }
    }
    cout << "\n❌ Student not found!\n";
}

// ---------- Sorting ----------
void sortByRoll() {
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.roll < b.roll;
    });
    cout << "✅ Sorted by Roll\n";
}

void sortByName() {
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.name < b.name;
    });
    cout << "✅ Sorted by Name\n";
}

// ---------- Main ----------
int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n====== Student Management System ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort by Roll\n";
        cout << "7. Sort by Name\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;

            case 6: 
                sortByRoll(); 
                saveToFile(); 
                break;

            case 7: 
                sortByName(); 
                saveToFile(); 
                break;

            case 8: cout << "👋 Exiting...\n"; break;
            default: cout << "❌ Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}