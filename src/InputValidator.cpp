#include "InputValidator.h"

#include <algorithm>
#include <cctype>

bool InputValidator::isValidName(const std::string& name) {
    return !name.empty() && std::any_of(name.begin(), name.end(), [](unsigned char ch) {
        return std::isalpha(ch);
    });
}

bool InputValidator::isValidAge(int age) {
    return age >= 16 && age <= 120;
}

bool InputValidator::isValidGpa(double gpa) {
    return gpa >= 0.0 && gpa <= 4.0;
}

bool InputValidator::isPositiveId(int id) {
    return id > 0;
}
