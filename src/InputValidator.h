#pragma once

#include <string>

class InputValidator {
public:
    static bool isValidName(const std::string& name);
    static bool isValidAge(int age);
    static bool isValidGpa(double gpa);
    static bool isPositiveId(int id);
};
