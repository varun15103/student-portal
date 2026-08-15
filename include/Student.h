#ifndef STUDENT_PORTAL_STUDENT_H
#define STUDENT_PORTAL_STUDENT_H

#include <string>

class Student {
public:
    Student() = default;
    Student(int id, std::string name, std::string email);

    int id() const;
    const std::string& name() const;
    const std::string& email() const;

    void setName(std::string name);
    void setEmail(std::string email);

    bool hasValidEmail() const;
    std::string toLine() const;

    static bool isValidEmail(const std::string& email);

private:
    int id_ = 0;
    std::string name_;
    std::string email_;
};

#endif
