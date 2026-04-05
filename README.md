# Student Record Management System (C++)

Console-based C++ application for managing student records using object-oriented design, file I/O, input validation, and STL containers.

## Features
- Add, update, delete, search, and list student records
- Persistent storage using CSV file I/O
- Input validation and basic error handling
- OOP design with clear separation of concerns
- Uses `std::vector` and `std::map`

## Build
```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/*.cpp -o student_records
```

## Run
```bash
./student_records
```

## File structure
- `src/Student.*` - student entity
- `src/StudentManager.*` - business logic
- `src/FileStorage.*` - persistence layer
- `src/InputValidator.*` - validation helpers
- `src/main.cpp` - CLI entry point
- `uml_class_diagram.puml` - PlantUML class diagram

## Example persisted file
Records are stored in `data/students.csv`.
