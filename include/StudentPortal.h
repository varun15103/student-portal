#ifndef STUDENT_PORTAL_STUDENT_PORTAL_H
#define STUDENT_PORTAL_STUDENT_PORTAL_H

#include "Course.h"
#include "Student.h"

#include <string>
#include <utility>
#include <vector>

class StudentPortal {
public:
    bool addStudent(Student student);
    bool addCourse(Course course);
    bool enroll(int studentId, int courseId);

    const Student* findStudent(int id) const;
    const Course* findCourse(int id) const;

    const std::vector<Student>& students() const;
    const std::vector<Course>& courses() const;
    std::vector<int> courseIdsFor(int studentId) const;

    bool saveToDirectory(const std::string& directory) const;
    bool loadFromDirectory(const std::string& directory);

private:
    int nextStudentId_ = 1;
    int nextCourseId_ = 1;
    std::vector<Student> students_;
    std::vector<Course> courses_;
    std::vector<std::pair<int, int>> enrollments_;

    bool isEnrolled(int studentId, int courseId) const;
};

#endif
