#include "Profile.h"

#include <sstream>

Profile::Profile(int studentId, std::string displayName, std::string email)
    : studentId_(studentId), displayName_(std::move(displayName)), email_(std::move(email)) {}

int Profile::studentId() const {
    return studentId_;
}

const std::string& Profile::displayName() const {
    return displayName_;
}

const std::string& Profile::email() const {
    return email_;
}

std::string Profile::toLine() const {
    std::ostringstream out;
    out << studentId_ << " | " << displayName_ << " | " << email_;
    return out.str();
}
