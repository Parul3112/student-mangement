#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <algorithm>

using namespace std;

struct Student
{
    int roll;
    string name;
    float marks;

    void input()
    {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const
    {
        cout << "Roll No: " << roll << "\nName: " << name << "\nMarks: " << marks << "\n";
        cout << "-----------------------------\n";
    }
};

const string filename = "students.txt";

vector<Student> loadStudents()
{
    vector<Student> students;
    ifstream inFile(filename);
    Student s;
    while (inFile >> s.roll)
    {
        inFile.ignore();
        getline(inFile, s.name);
        inFile >> s.marks;
        inFile.ignore();
        students.push_back(s);
    }
    inFile.close();
    return students;
}

void saveStudents(const vector<Student> &students)
{
    ofstream outFile(filename);
    for (const auto &s : students)
    {
        outFile << s.roll << "\n"
                << s.name << "\n"
                << s.marks << "\n";
    }
    outFile.close();
}

void addStudent()
{
    Student s;
    s.input();
    ofstream outFile(filename, ios::app);
    outFile << s.roll << "\n"
            << s.name << "\n"
            << s.marks << "\n";
    outFile.close();
    cout << "Student added successfully!\n";
}

void viewStudents()
{
    vector<Student> students = loadStudents();
    if (students.empty())
    {
        cout << "No records found.\n";
    }
    else
    {
        for (const auto &s : students)
            s.display();
    }
}

void searchStudent()
{
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    vector<Student> students = loadStudents();
    bool found = false;
    for (const auto &s : students)
    {
        if (s.roll == roll)
        {
            s.display();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found.\n";
}

void updateStudent()
{
    int roll;
    cout << "Enter Roll No to update: ";
    cin >> roll;
    vector<Student> students = loadStudents();
    bool found = false;
    for (auto &s : students)
    {
        if (s.roll == roll)
        {
            cout << "Current details:\n";
            s.display();
            cout << "Enter new details:\n";
            s.input();
            found = true;
            break;
        }
    }
    if (found)
    {
        saveStudents(students);
        cout << "Student updated successfully.\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

void deleteStudent()
{
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    vector<Student> students = loadStudents();
    auto it = remove_if(students.begin(), students.end(), [roll](const Student &s)
                        { return s.roll == roll; });
    if (it != students.end())
    {
        students.erase(it, students.end());
        saveStudents(students);
        cout << "Student deleted successfully.\n";
    }
    else
    {
        cout << "Student not found.\n";
    }
}

void menu()
{
    int choice;
    do
    {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
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
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

int main()
{
    menu();
    return 0;
}
