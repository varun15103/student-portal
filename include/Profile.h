#ifndef STUDENT_PORTAL_PROFILE_H
#define STUDENT_PORTAL_PROFILE_H

#include <string>

class Profile {
public:
    Profile() = default;
    Profile(int studentId, std::string displayName, std::string email, double gpa = 0.0);

    int studentId() const;
    const std::string& displayName() const;
    const std::string& email() const;
    double gpa() const;
    std::string standing() const;

    void setDisplayName(std::string displayName);
    void setEmail(std::string email);
    void setGpa(double gpa);

    bool isValid() const;
    std::string toLine() const;

private:
    int studentId_ = 0;
    std::string displayName_;
    std::string email_;
    double gpa_ = 0.0;
};

#endif
