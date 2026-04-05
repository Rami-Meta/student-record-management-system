#include "StudentManager.h"

StudentManager::StudentManager(std::string storagePath)
    : storagePath(std::move(storagePath)) {}

void StudentManager::load() {
    students = storage.load(storagePath);
    rebuildIndex();
}

void StudentManager::save() const {
    storage.save(storagePath, students);
}

bool StudentManager::addStudent(const Student& student) {
    if (idIndex.count(student.getId()) > 0) {
        return false;
    }
    idIndex[student.getId()] = students.size();
    students.push_back(student);
    return true;
}

bool StudentManager::updateStudent(int id, const Student& updated) {
    const auto it = idIndex.find(id);
    if (it == idIndex.end()) {
        return false;
    }
    students[it->second] = updated;
    rebuildIndex();
    return true;
}

bool StudentManager::deleteStudent(int id) {
    const auto it = idIndex.find(id);
    if (it == idIndex.end()) {
        return false;
    }
    students.erase(students.begin() + static_cast<long>(it->second));
    rebuildIndex();
    return true;
}

std::optional<Student> StudentManager::findStudentById(int id) const {
    const auto it = idIndex.find(id);
    if (it == idIndex.end()) {
        return std::nullopt;
    }
    return students[it->second];
}

std::vector<Student> StudentManager::listStudents() const {
    return students;
}

void StudentManager::rebuildIndex() {
    idIndex.clear();
    for (std::size_t i = 0; i < students.size(); ++i) {
        idIndex[students[i].getId()] = i;
    }
}
