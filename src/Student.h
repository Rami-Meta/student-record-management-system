#pragma once

#include <string>

class Student {
public:
    Student() = default;
    Student(int id, std::string name, int age, std::string course, double gpa);

    int getId() const;
    const std::string& getName() const;
    int getAge() const;
    const std::string& getCourse() const;
    double getGpa() const;

    void setName(const std::string& name);
    void setAge(int age);
    void setCourse(const std::string& course);
    void setGpa(double gpa);

    std::string toCsvRow() const;
    static Student fromCsvRow(const std::string& row);

private:
    int id{};
    std::string name;
    int age{};
    std::string course;
    double gpa{};
};
