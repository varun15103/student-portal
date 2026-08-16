#ifndef STUDENT_PORTAL_SETTINGS_H
#define STUDENT_PORTAL_SETTINGS_H

#include <string>

class Settings {
public:
    const std::string& theme() const;
    const std::string& displayName() const;
    bool emailNotifications() const;
    bool dashboardAlerts() const;
    bool compactMode() const;

    void setTheme(std::string theme);
    void setDisplayName(std::string displayName);
    void setEmailNotifications(bool enabled);
    void setDashboardAlerts(bool enabled);
    void setCompactMode(bool enabled);

    bool isValid() const;
    std::string toLine() const;

    bool saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);

private:
    std::string theme_ = "light";
    std::string displayName_ = "Student";
    bool emailNotifications_ = true;
    bool dashboardAlerts_ = true;
    bool compactMode_ = false;
};

#endif
