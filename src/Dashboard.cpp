#include "Dashboard.h"

#include <sstream>

void Dashboard::refresh(const StudentPortal& portal) {
    studentCount_ = static_cast<int>(portal.students().size());
    courseCount_ = static_cast<int>(portal.courses().size());
    enrollmentCount_ = 0;
    for (const auto& student : portal.students()) {
        enrollmentCount_ += static_cast<int>(portal.courseIdsFor(student.id()).size());
    }
}

int Dashboard::studentCount() const {
    return studentCount_;
}

int Dashboard::courseCount() const {
    return courseCount_;
}

int Dashboard::enrollmentCount() const {
    return enrollmentCount_;
}

std::string Dashboard::summary() const {
    std::ostringstream out;
    out << "Students: " << studentCount_ << " | Courses: " << courseCount_
        << " | Enrollments: " << enrollmentCount_;
    return out.str();
}
