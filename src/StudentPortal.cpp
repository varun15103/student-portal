#include "StudentPortal.h"

#include <fstream>
#include <sstream>

bool StudentPortal::addStudent(Student student) {
    if (student.name().empty() || !student.hasValidEmail()) {
        return false;
    }
    if (student.id() <= 0) {
        student = Student(nextStudentId_, student.name(), student.email());
    }
    if (findStudent(student.id()) != nullptr) {
        return false;
    }
    if (student.id() >= nextStudentId_) {
        nextStudentId_ = student.id() + 1;
    }
    students_.push_back(std::move(student));
    return true;
}

bool StudentPortal::addCourse(Course course) {
    if (!Course::isValidCode(course.code()) || course.title().empty() ||
        !course.hasValidCredits()) {
        return false;
    }
    if (course.id() <= 0) {
        course = Course(nextCourseId_, course.code(), course.title(), course.credits());
    }
    if (findCourse(course.id()) != nullptr) {
        return false;
    }
    if (course.id() >= nextCourseId_) {
        nextCourseId_ = course.id() + 1;
    }
    courses_.push_back(std::move(course));
    return true;
}

bool StudentPortal::enroll(int studentId, int courseId) {
    if (findStudent(studentId) == nullptr || findCourse(courseId) == nullptr) {
        return false;
    }
    if (isEnrolled(studentId, courseId)) {
        return false;
    }
    enrollments_.push_back({studentId, courseId});
    return true;
}

const Student* StudentPortal::findStudent(int id) const {
    for (const auto& student : students_) {
        if (student.id() == id) {
            return &student;
        }
    }
    return nullptr;
}

const Course* StudentPortal::findCourse(int id) const {
    for (const auto& course : courses_) {
        if (course.id() == id) {
            return &course;
        }
    }
    return nullptr;
}

const std::vector<Student>& StudentPortal::students() const {
    return students_;
}

const std::vector<Course>& StudentPortal::courses() const {
    return courses_;
}

std::vector<int> StudentPortal::courseIdsFor(int studentId) const {
    std::vector<int> ids;
    for (const auto& pair : enrollments_) {
        if (pair.first == studentId) {
            ids.push_back(pair.second);
        }
    }
    return ids;
}

bool StudentPortal::isEnrolled(int studentId, int courseId) const {
    for (const auto& pair : enrollments_) {
        if (pair.first == studentId && pair.second == courseId) {
            return true;
        }
    }
    return false;
}

bool StudentPortal::saveToDirectory(const std::string& directory) const {
    std::ofstream studentsFile(directory + "/students.txt");
    std::ofstream coursesFile(directory + "/courses.txt");
    std::ofstream enrollFile(directory + "/enrollments.txt");
    if (!studentsFile || !coursesFile || !enrollFile) {
        return false;
    }
    for (const auto& student : students_) {
        studentsFile << student.id() << '\t' << student.name() << '\t'
                     << student.email() << '\n';
    }
    for (const auto& course : courses_) {
        coursesFile << course.id() << '\t' << course.code() << '\t' << course.title()
                    << '\t' << course.credits() << '\n';
    }
    for (const auto& pair : enrollments_) {
        enrollFile << pair.first << '\t' << pair.second << '\n';
    }
    return true;
}

bool StudentPortal::loadFromDirectory(const std::string& directory) {
    students_.clear();
    courses_.clear();
    enrollments_.clear();
    nextStudentId_ = 1;
    nextCourseId_ = 1;

    std::ifstream studentsFile(directory + "/students.txt");
    std::ifstream coursesFile(directory + "/courses.txt");
    std::ifstream enrollFile(directory + "/enrollments.txt");
    if (!studentsFile || !coursesFile || !enrollFile) {
        return false;
    }

    std::string line;
    while (std::getline(studentsFile, line)) {
        std::istringstream in(line);
        int id = 0;
        std::string name;
        std::string email;
        if (in >> id && std::getline(in >> std::ws, name, '\t') &&
            std::getline(in, email)) {
            addStudent(Student(id, name, email));
        }
    }
    while (std::getline(coursesFile, line)) {
        std::istringstream in(line);
        int id = 0;
        int credits = 0;
        std::string code;
        std::string title;
        if (in >> id >> code && std::getline(in >> std::ws, title, '\t') &&
            in >> credits) {
            addCourse(Course(id, code, title, credits));
        }
    }
    while (std::getline(enrollFile, line)) {
        std::istringstream in(line);
        int studentId = 0;
        int courseId = 0;
        if (in >> studentId >> courseId) {
            enroll(studentId, courseId);
        }
    }
    return true;
}
