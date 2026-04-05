#pragma once

#include "Student.h"

#include <string>
#include <vector>

class FileStorage {
public:
    std::vector<Student> load(const std::string& path) const;
    void save(const std::string& path, const std::vector<Student>& students) const;
};
