#ifndef STUDENT_PORTAL_COURSE_H
#define STUDENT_PORTAL_COURSE_H

#include <string>

class Course {
public:
    Course() = default;
    Course(int id, std::string code, std::string title, int credits);

    int id() const;
    const std::string& code() const;
    const std::string& title() const;
    int credits() const;

    void setTitle(std::string title);
    void setCredits(int credits);

    bool hasValidCredits() const;
    std::string toLine() const;

    static bool isValidCode(const std::string& code);

private:
    int id_ = 0;
    std::string code_;
    std::string title_;
    int credits_ = 0;
};

#endif
