#pragma once

#include "FileStorage.h"
#include "Student.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class StudentManager {
public:
    explicit StudentManager(std::string storagePath);

    void load();
    void save() const;

    bool addStudent(const Student& student);
    bool updateStudent(int id, const Student& updated);
    bool deleteStudent(int id);
    std::optional<Student> findStudentById(int id) const;
    std::vector<Student> listStudents() const;

private:
    void rebuildIndex();

    std::string storagePath;
    std::vector<Student> students;
    std::map<int, std::size_t> idIndex;
    FileStorage storage;
};
