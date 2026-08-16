#ifndef STUDENT_PORTAL_SETTINGS_H
#define STUDENT_PORTAL_SETTINGS_H

#include <string>

class Settings {
public:
    const std::string& theme() const;
    const std::string& displayName() const;

    void setTheme(std::string theme);
    void setDisplayName(std::string displayName);

    std::string toLine() const;

private:
    std::string theme_ = "light";
    std::string displayName_ = "Student";
};

#endif
