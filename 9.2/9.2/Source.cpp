#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

enum Speciality { COMPUTER_SCIENCE, INFORMATICS, MATH_AND_ECONOMICS, PHYSICS_AND_INFORMATICS, VOCATIONAL_TRAINING };
string specialityStr[] = { "Computer Science", "Informatics", "Mathematics and Economics", "Physics and Informatics", "Vocational Training" };

struct Student {
    string surname;
    int course;
    Speciality speciality;
    int physicsGrade;
    int mathGrade;
    union {
        int informaticsGrade;
        int programmingGrade;
        int pedagogyGrade;
    };
};

bool CompareStudents(const Student& a, const Student& b) {
    if (a.speciality != b.speciality)
        return a.speciality > b.speciality;
    if (a.surname != b.surname)
        return a.surname > b.surname;
    return a.course < b.course;
}


void Create(Student* students, const int N) {
    for (int i = 0; i < N; ++i) {
        cout << "Student ¹ " << i + 1 << ":" << endl;
        cout << " Surname: ";
        cin >> students[i].surname;
        cout << " Course: ";
        cin >> students[i].course;
        cout << " Speciality (";
        for (int j = 0; j < 5; ++j) {
            cout << j << " - " << specialityStr[j] << ", ";
        }
        cout << "): ";
        int specialityInput;
        cin >> specialityInput;
        students[i].speciality = static_cast<Speciality>(specialityInput);
        cout << " Physics Grade: ";
        cin >> students[i].physicsGrade;
        cout << " Math Grade: ";
        cin >> students[i].mathGrade;
        switch (students[i].speciality) {
        case COMPUTER_SCIENCE:
            cout << " Programming Grade: ";
            cin >> students[i].programmingGrade;
            break;
        case INFORMATICS:
            cout << " Informatics Grade: ";
            cin >> students[i].informaticsGrade;
            break;
        default:
            cout << " Pedagogy Grade: ";
            cin >> students[i].pedagogyGrade;
            break;
        }
        cout << endl;
    }
}

void PrintTableA(Student* students, const int N) {
    cout << setw(5) << "¹" << setw(15) << "Surname" << setw(7) << "Course" << setw(25) << "Speciality" << setw(7) << "Physics" << setw(7) << "Math" << setw(7) << "Informatics" << endl;
    for (int i = 0; i < N; ++i) {
        cout << setw(5) << i + 1 << setw(15) << students[i].surname << setw(7) << students[i].course << setw(25) << specialityStr[students[i].speciality] << setw(7) << students[i].physicsGrade << setw(7) << students[i].mathGrade;
        if (students[i].speciality == COMPUTER_SCIENCE) {
            cout << setw(7) << students[i].programmingGrade;
        }
        else if (students[i].speciality == INFORMATICS) {
            cout << setw(7) << students[i].informaticsGrade;
        }
        else {
            cout << setw(7) << students[i].pedagogyGrade;
        }
        cout << endl;
    }
}

void PrintTableB(Student* students, const int N) {
    cout << setw(5) << "¹" << setw(15) << "Surname" << setw(7) << "Course" << setw(25) << "Speciality" << setw(7) << "Physics" << setw(7) << "Math" << setw(7) << "Informatics" << setw(7) << "Programming" << setw(7) << "Numerical" << setw(7) << "Pedagogy" << endl;
    for (int i = 0; i < N; ++i) {
        cout << setw(5) << i + 1 << setw(15) << students[i].surname << setw(7) << students[i].course << setw(25) << specialityStr[students[i].speciality] << setw(7) << students[i].physicsGrade << setw(7) << students[i].mathGrade;
        if (students[i].speciality == COMPUTER_SCIENCE) {
            cout << setw(7) << students[i].programmingGrade << setw(7) << "-" << setw(7) << "-";
        }
        else if (students[i].speciality == INFORMATICS) {
            cout << setw(7) << "-" << setw(7) << students[i].informaticsGrade << setw(7) << "-";
        }
        else {
            cout << setw(7) << "-" << setw(7) << "-" << setw(7) << students[i].pedagogyGrade;
        }
        cout << endl;
    }
}

void SortStudents(Student* students, const int N) {
    sort(students, students + N, CompareStudents);
}

vector<int> BuildIndexArray(Student* students, const int N) {
    vector<int> indexArray(N);
    for (int i = 0; i < N; ++i)
        indexArray[i] = i;
    sort(indexArray.begin(), indexArray.end(), [&](int a, int b) {
        return CompareStudents(students[a], students[b]);
        });
    return indexArray;
}

bool BinarySearchStudent(Student* students, const int N, const string& surname, const int course, const Speciality speciality) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].surname == surname && students[mid].course == course && students[mid].speciality ==

            speciality)
            return true;
        else if (students[mid].surname < surname || (students[mid].surname == surname && students[mid].course < course) || (students[mid].surname == surname && students[mid].course == course && students[mid].speciality < speciality))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;
    Student* students = new Student[N];

        int menuItem;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Input Data" << endl;
        cout << "2. Print Table (Level A)" << endl;
        cout << "3. Print Table (Level B)" << endl;
        cout << "4. Sort by Speciality" << endl;
        cout << "5. Binary Search Student" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            break;
        case 2:
            PrintTableA(students, N);
            break;
        case 3:
            PrintTableB(students, N);
            break;
        case 4:
            SortStudents(students, N);
            cout << "Students sorted by Speciality:" << endl;
            PrintTableA(students, N);
            break;
        case 5:
        {
            string surname;
            int course, specialityInput;
            cout << "Enter student's surname: ";
            cin >> surname;
            cout << "Enter student's course: ";
            cin >> course;
            cout << "Enter student's speciality (";
            for (int j = 0; j < 5; ++j) {
                cout << j << " - " << specialityStr[j] << ", ";
            }
            cout << "): ";
            cin >> specialityInput;
            Speciality speciality = static_cast<Speciality>(specialityInput);
            if (BinarySearchStudent(students, N, surname, course, speciality))
                cout << "Student found." << endl;
            else
                cout << "Student not found." << endl;
        }
        break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (menuItem != 0);

    delete[] students;

    return 0;
}