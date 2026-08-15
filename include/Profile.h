#ifndef STUDENT_PORTAL_PROFILE_H
#define STUDENT_PORTAL_PROFILE_H

#include <string>

class Profile {
public:
    Profile() = default;
    Profile(int studentId, std::string displayName, std::string email);

    int studentId() const;
    const std::string& displayName() const;
    const std::string& email() const;

    std::string toLine() const;

private:
    int studentId_ = 0;
    std::string displayName_;
    std::string email_;
};

#endif
