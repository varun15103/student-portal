#include "Settings.h"

#include <sstream>

const std::string& Settings::theme() const {
    return theme_;
}

const std::string& Settings::displayName() const {
    return displayName_;
}

void Settings::setTheme(std::string theme) {
    theme_ = std::move(theme);
}

void Settings::setDisplayName(std::string displayName) {
    displayName_ = std::move(displayName);
}

std::string Settings::toLine() const {
    std::ostringstream out;
    out << "Theme: " << theme_ << " | Display name: " << displayName_;
    return out.str();
}
