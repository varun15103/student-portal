#include "StudentPortal.h"

#include <filesystem>
#include <iostream>
#include <limits>
#include <string>

namespace {

void discardLine(std::istream& in) {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            discardLine(std::cin);
            return value;
        }
        std::cin.clear();
        discardLine(std::cin);
        std::cout << "Enter a whole number.\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void printMenu() {
    std::cout << "\n=== Student Portal ===\n"
              << "1. Add student\n"
              << "2. Add course\n"
              << "3. List students\n"
              << "4. List courses\n"
              << "5. Enroll student in course\n"
              << "6. Save records\n"
              << "7. Load records\n"
              << "0. Exit\n";
}

}  // namespace

int main() {
    StudentPortal portal;
    const std::string dataDir = "data";
    std::filesystem::create_directories(dataDir);

    bool running = true;
    while (running) {
        printMenu();
        const int choice = readInt("Choice: ");
        switch (choice) {
            case 1: {
                const std::string name = readLine("Name: ");
                const std::string email = readLine("Email: ");
                if (portal.addStudent(Student(0, name, email))) {
                    std::cout << "Student added.\n";
                } else {
                    std::cout << "Could not add student. Check name and email.\n";
                }
                break;
            }
            case 2: {
                const std::string code = readLine("Course code: ");
                const std::string title = readLine("Title: ");
                const int credits = readInt("Credits (1-6): ");
                if (portal.addCourse(Course(0, code, title, credits))) {
                    std::cout << "Course added.\n";
                } else {
                    std::cout << "Could not add course. Check code, title, and credits.\n";
                }
                break;
            }
            case 3:
                if (portal.students().empty()) {
                    std::cout << "No students yet.\n";
                }
                for (const auto& student : portal.students()) {
                    std::cout << student.toLine() << '\n';
                }
                break;
            case 4:
                if (portal.courses().empty()) {
                    std::cout << "No courses yet.\n";
                }
                for (const auto& course : portal.courses()) {
                    std::cout << course.toLine() << '\n';
                }
                break;
            case 5: {
                const int studentId = readInt("Student id: ");
                const int courseId = readInt("Course id: ");
                if (portal.enroll(studentId, courseId)) {
                    std::cout << "Enrolled.\n";
                } else {
                    std::cout << "Enrollment failed. Unknown id or already enrolled.\n";
                }
                break;
            }
            case 6:
                if (portal.saveToDirectory(dataDir)) {
                    std::cout << "Saved to " << dataDir << "/\n";
                } else {
                    std::cout << "Save failed.\n";
                }
                break;
            case 7:
                if (portal.loadFromDirectory(dataDir)) {
                    std::cout << "Loaded from " << dataDir << "/\n";
                } else {
                    std::cout << "Load failed. Save once to create data files.\n";
                }
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Unknown choice.\n";
                break;
        }
    }
    return 0;
}
