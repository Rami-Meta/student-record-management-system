#include "InputValidator.h"
#include "StudentManager.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
T promptNumber(const std::string& message) {
    T value;
    while (true) {
        std::cout << message;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        clearInput();
    }
}

std::string promptString(const std::string& message) {
    std::string value;
    std::cout << message;
    std::getline(std::cin, value);
    return value;
}

Student promptStudent() {
    int id;
    do {
        id = promptNumber<int>("ID: ");
        if (!InputValidator::isPositiveId(id)) {
            std::cout << "ID must be positive.\n";
        }
    } while (!InputValidator::isPositiveId(id));

    std::string name;
    do {
        name = promptString("Name: ");
        if (!InputValidator::isValidName(name)) {
            std::cout << "Name must contain letters.\n";
        }
    } while (!InputValidator::isValidName(name));

    int age;
    do {
        age = promptNumber<int>("Age: ");
        if (!InputValidator::isValidAge(age)) {
            std::cout << "Age must be between 16 and 120.\n";
        }
    } while (!InputValidator::isValidAge(age));

    std::string course = promptString("Course: ");

    double gpa;
    do {
        gpa = promptNumber<double>("GPA (0.0 - 4.0): ");
        if (!InputValidator::isValidGpa(gpa)) {
            std::cout << "GPA must be between 0.0 and 4.0.\n";
        }
    } while (!InputValidator::isValidGpa(gpa));

    return Student(id, name, age, course, gpa);
}

void printStudents(const std::vector<Student>& students) {
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(22) << "Name"
              << std::setw(8) << "Age"
              << std::setw(28) << "Course"
              << std::setw(8) << "GPA" << '\n';
    std::cout << std::string(74, '-') << '\n';
    for (const auto& s : students) {
        std::cout << std::setw(8) << s.getId()
                  << std::setw(22) << s.getName()
                  << std::setw(8) << s.getAge()
                  << std::setw(28) << s.getCourse()
                  << std::setw(8) << std::fixed << std::setprecision(2) << s.getGpa() << '\n';
    }
}
}

int main() {
    StudentManager manager("data/students.csv");
    manager.load();

    while (true) {
        std::cout << "\n=== Student Record Management System ===\n"
                  << "1. Add student\n"
                  << "2. Update student\n"
                  << "3. Delete student\n"
                  << "4. Search by ID\n"
                  << "5. List students\n"
                  << "6. Save and exit\n";

        const int choice = promptNumber<int>("Choose an option: ");

        if (choice == 1) {
            auto student = promptStudent();
            if (manager.addStudent(student)) {
                std::cout << "Student added successfully.\n";
            } else {
                std::cout << "A student with that ID already exists.\n";
            }
        } else if (choice == 2) {
            const int id = promptNumber<int>("Enter ID to update: ");
            if (!manager.findStudentById(id).has_value()) {
                std::cout << "Student not found.\n";
                continue;
            }
            std::cout << "Enter updated details:\n";
            auto updated = promptStudent();
            if (updated.getId() != id) {
                std::cout << "Updated student must keep the same ID.\n";
                continue;
            }
            manager.updateStudent(id, updated);
            std::cout << "Student updated.\n";
        } else if (choice == 3) {
            const int id = promptNumber<int>("Enter ID to delete: ");
            if (manager.deleteStudent(id)) {
                std::cout << "Student deleted.\n";
            } else {
                std::cout << "Student not found.\n";
            }
        } else if (choice == 4) {
            const int id = promptNumber<int>("Enter ID to search: ");
            const auto student = manager.findStudentById(id);
            if (student.has_value()) {
                printStudents({student.value()});
            } else {
                std::cout << "Student not found.\n";
            }
        } else if (choice == 5) {
            const auto students = manager.listStudents();
            if (students.empty()) {
                std::cout << "No records found.\n";
            } else {
                printStudents(students);
            }
        } else if (choice == 6) {
            manager.save();
            std::cout << "Records saved. Goodbye.\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
