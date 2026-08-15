#ifndef STUDENT_PORTAL_DASHBOARD_H
#define STUDENT_PORTAL_DASHBOARD_H

#include "StudentPortal.h"

#include <string>

class Dashboard {
public:
    void refresh(const StudentPortal& portal);

    int studentCount() const;
    int courseCount() const;
    int enrollmentCount() const;
    std::string summary() const;

private:
    int studentCount_ = 0;
    int courseCount_ = 0;
    int enrollmentCount_ = 0;
};

#endif
