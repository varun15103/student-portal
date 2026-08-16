#include "Settings.h"

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
