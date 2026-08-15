#include "Profile.h"

#include "Student.h"

#include <sstream>

Profile::Profile(int studentId, std::string displayName, std::string email, double gpa)
    : studentId_(studentId),
      displayName_(std::move(displayName)),
      email_(std::move(email)),
      gpa_(gpa) {}

int Profile::studentId() const {
    return studentId_;
}

const std::string& Profile::displayName() const {
    return displayName_;
}

const std::string& Profile::email() const {
    return email_;
}

double Profile::gpa() const {
    return gpa_;
}

std::string Profile::standing() const {
    if (gpa_ >= 3.5) {
        return "Dean's List";
    }
    if (gpa_ >= 2.0) {
        return "Good Standing";
    }
    if (gpa_ > 0.0) {
        return "Academic Warning";
    }
    return "Unranked";
}

void Profile::setDisplayName(std::string displayName) {
    displayName_ = std::move(displayName);
}

void Profile::setEmail(std::string email) {
    email_ = std::move(email);
}

void Profile::setGpa(double gpa) {
    gpa_ = gpa;
}

bool Profile::isValid() const {
    return studentId_ > 0 && !displayName_.empty() && Student::isValidEmail(email_) &&
           gpa_ >= 0.0 && gpa_ <= 4.0;
}

std::string Profile::toLine() const {
    std::ostringstream out;
    out << studentId_ << " | " << displayName_ << " | " << email_ << " | GPA "
        << gpa_ << " | " << standing();
    return out.str();
}
