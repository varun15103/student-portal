#include "Settings.h"

#include <fstream>
#include <sstream>

const std::string& Settings::theme() const {
    return theme_;
}

const std::string& Settings::displayName() const {
    return displayName_;
}

bool Settings::emailNotifications() const {
    return emailNotifications_;
}

bool Settings::dashboardAlerts() const {
    return dashboardAlerts_;
}

void Settings::setTheme(std::string theme) {
    theme_ = std::move(theme);
}

void Settings::setDisplayName(std::string displayName) {
    displayName_ = std::move(displayName);
}

void Settings::setEmailNotifications(bool enabled) {
    emailNotifications_ = enabled;
}

void Settings::setDashboardAlerts(bool enabled) {
    dashboardAlerts_ = enabled;
}

std::string Settings::toLine() const {
    std::ostringstream out;
    out << "Theme: " << theme_ << " | Display name: " << displayName_
        << " | Email notices: " << (emailNotifications_ ? "on" : "off")
        << " | Dashboard alerts: " << (dashboardAlerts_ ? "on" : "off");
    return out.str();
}

bool Settings::saveToFile(const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    out << "theme=" << theme_ << '\n';
    out << "displayName=" << displayName_ << '\n';
    out << "emailNotifications=" << (emailNotifications_ ? "1" : "0") << '\n';
    out << "dashboardAlerts=" << (dashboardAlerts_ ? "1" : "0") << '\n';
    return true;
}

bool Settings::loadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    std::string line;
    while (std::getline(in, line)) {
        const auto eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }
        const std::string key = line.substr(0, eq);
        const std::string value = line.substr(eq + 1);
        if (key == "theme") {
            theme_ = value;
        } else if (key == "displayName") {
            displayName_ = value;
        } else if (key == "emailNotifications") {
            emailNotifications_ = (value == "1");
        } else if (key == "dashboardAlerts") {
            dashboardAlerts_ = (value == "1");
        }
    }
    return true;
}
