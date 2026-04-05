#include "FileStorage.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

std::vector<Student> FileStorage::load(const std::string& path) const {
    std::ifstream input(path);
    std::vector<Student> students;

    if (!input.is_open()) {
        std::cerr << "Warning: could not open " << path << ". Starting with empty records.\n";
        return students;
    }

    std::string line;
    std::getline(input, line); // header
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        students.push_back(Student::fromCsvRow(line));
    }
    return students;
}

void FileStorage::save(const std::string& path, const std::vector<Student>& students) const {
    std::ofstream output(path);
    if (!output.is_open()) {
        throw std::runtime_error("Unable to write to file: " + path);
    }

    output << "id,name,age,course,gpa\n";
    for (const auto& student : students) {
        output << student.toCsvRow() << '\n';
    }
}
