#include "LoginManager.h"
#include "ProfileStore.h"
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

void printMenu(const LoginManager& login) {
    std::cout << "\n=== Student Portal ===\n";
    if (login.isLoggedIn()) {
        std::cout << "Signed in as: " << login.currentUsername() << '\n';
    } else {
        std::cout << "Signed in as: (guest)\n";
    }
    std::cout << "1. Add student\n"
              << "2. Add course\n"
              << "3. List students\n"
              << "4. List courses\n"
              << "5. Enroll student in course\n"
              << "6. Save records\n"
              << "7. Load records\n"
              << "8. Login\n"
              << "9. Logout\n"
              << "10. View profile\n"
              << "11. Edit profile\n"
              << "0. Exit\n";
}

bool requireLogin(const LoginManager& login) {
    if (login.isLoggedIn()) {
        return true;
    }
    std::cout << "Login required for that action.\n";
    return false;
}

}  // namespace

int main() {
    StudentPortal portal;
    LoginManager login;
    ProfileStore profiles;
    const std::string dataDir = "data";
    const std::string lastLoginPath = dataDir + "/last_logins.txt";
    std::filesystem::create_directories(dataDir);
    login.loadLastLogins(lastLoginPath);

    bool running = true;
    while (running) {
        printMenu(login);
        const int choice = readInt("Choice: ");
        switch (choice) {
            case 1: {
                if (!requireLogin(login)) {
                    break;
                }
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
                if (!requireLogin(login)) {
                    break;
                }
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
                if (!requireLogin(login)) {
                    break;
                }
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
                if (!requireLogin(login)) {
                    break;
                }
                if (portal.saveToDirectory(dataDir) && login.saveLastLogins(lastLoginPath)) {
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
            case 8: {
                const std::string username = readLine("Username: ");
                const std::string password = readLine("Password: ");
                const std::string previous = login.lastLoginOf(username);
                if (login.isLocked(username)) {
                    std::cout << "Account locked after "
                              << LoginManager::kMaxFailedAttempts
                              << " failed attempts.\n";
                } else if (login.authenticate(username, password)) {
                    std::cout << "Logged in as " << login.currentUsername() << ".\n";
                    if (previous.empty()) {
                        std::cout << "First recorded login.\n";
                    } else {
                        std::cout << "Last login: " << previous << ".\n";
                    }
                    login.saveLastLogins(lastLoginPath);
                } else {
                    const int used = login.failedAttempts(username);
                    const int left = LoginManager::kMaxFailedAttempts - used;
                    std::cout << "Login failed. Attempts left: " << left << ".\n";
                }
                break;
            }
            case 9:
                if (!login.isLoggedIn()) {
                    std::cout << "Already logged out.\n";
                } else {
                    login.logout();
                    std::cout << "Logged out.\n";
                }
                break;
            case 10: {
                if (!requireLogin(login)) {
                    break;
                }
                const int studentId = readInt("Student id: ");
                const Profile* profile = profiles.find(studentId);
                if (profile == nullptr) {
                    std::cout << "No profile for that student id.\n";
                } else {
                    std::cout << profile->toLine() << '\n';
                }
                break;
            }
            case 11: {
                if (!requireLogin(login)) {
                    break;
                }
                const int studentId = readInt("Student id: ");
                const std::string name = readLine("Display name: ");
                const std::string email = readLine("Email: ");
                const int gpaTimesTen = readInt("GPA x10 (e.g. 35 for 3.5): ");
                Profile profile(studentId, name, email, gpaTimesTen / 10.0);
                if (profiles.upsert(profile)) {
                    std::cout << "Profile saved. Standing: " << profile.standing() << ".\n";
                } else {
                    std::cout << "Invalid profile. Check id, name, email, and GPA 0-4.\n";
                }
                break;
            }
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
