#include "Student.h"

#include <sstream>

Student::Student(int id, std::string name, std::string email)
    : id_(id), name_(std::move(name)), email_(std::move(email)) {}

int Student::id() const {
    return id_;
}

const std::string& Student::name() const {
    return name_;
}

const std::string& Student::email() const {
    return email_;
}

void Student::setName(std::string name) {
    name_ = std::move(name);
}

void Student::setEmail(std::string email) {
    email_ = std::move(email);
}

bool Student::hasValidEmail() const {
    return isValidEmail(email_);
}

bool Student::isValidEmail(const std::string& email) {
    const auto at = email.find('@');
    if (at == std::string::npos || at == 0) {
        return false;
    }
    const auto dot = email.find('.', at);
    return dot != std::string::npos && dot + 1 < email.size();
}

std::string Student::toLine() const {
    std::ostringstream out;
    out << id_ << " | " << name_ << " | " << email_;
    return out.str();
}
