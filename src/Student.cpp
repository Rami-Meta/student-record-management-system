#include "Student.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace {
std::vector<std::string> splitCsv(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        parts.push_back(token);
    }
    return parts;
}
}

Student::Student(int id, std::string name, int age, std::string course, double gpa)
    : id(id), name(std::move(name)), age(age), course(std::move(course)), gpa(gpa) {}

int Student::getId() const { return id; }
const std::string& Student::getName() const { return name; }
int Student::getAge() const { return age; }
const std::string& Student::getCourse() const { return course; }
double Student::getGpa() const { return gpa; }

void Student::setName(const std::string& newName) { name = newName; }
void Student::setAge(int newAge) { age = newAge; }
void Student::setCourse(const std::string& newCourse) { course = newCourse; }
void Student::setGpa(double newGpa) { gpa = newGpa; }

std::string Student::toCsvRow() const {
    std::ostringstream oss;
    oss << id << ',' << name << ',' << age << ',' << course << ','
        << std::fixed << std::setprecision(2) << gpa;
    return oss.str();
}

Student Student::fromCsvRow(const std::string& row) {
    const auto parts = splitCsv(row);
    if (parts.size() != 5) {
        throw std::runtime_error("Invalid CSV row format");
    }

    return Student(
        std::stoi(parts[0]),
        parts[1],
        std::stoi(parts[2]),
        parts[3],
        std::stod(parts[4])
    );
}
