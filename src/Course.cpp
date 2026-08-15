#include "Course.h"

#include <cctype>
#include <sstream>

Course::Course(int id, std::string code, std::string title, int credits)
    : id_(id), code_(std::move(code)), title_(std::move(title)), credits_(credits) {}

int Course::id() const {
    return id_;
}

const std::string& Course::code() const {
    return code_;
}

const std::string& Course::title() const {
    return title_;
}

int Course::credits() const {
    return credits_;
}

void Course::setTitle(std::string title) {
    title_ = std::move(title);
}

void Course::setCredits(int credits) {
    credits_ = credits;
}

bool Course::hasValidCredits() const {
    return credits_ >= 1 && credits_ <= 6;
}

bool Course::isValidCode(const std::string& code) {
    if (code.size() < 4) {
        return false;
    }
    for (unsigned char ch : code) {
        if (!std::isalnum(ch)) {
            return false;
        }
    }
    return true;
}

std::string Course::toLine() const {
    std::ostringstream out;
    out << id_ << " | " << code_ << " | " << title_ << " | " << credits_ << " credits";
    return out.str();
}
