#ifndef STUDENT_PORTAL_LOGIN_MANAGER_H
#define STUDENT_PORTAL_LOGIN_MANAGER_H

#include <string>
#include <unordered_map>

class LoginManager {
public:
    static constexpr int kMaxFailedAttempts = 3;

    LoginManager();

    bool isLoggedIn() const;
    const std::string& currentUsername() const;
    bool isLocked(const std::string& username) const;
    int failedAttempts(const std::string& username) const;
    std::string lastLoginOf(const std::string& username) const;

    bool registerUser(const std::string& username, const std::string& password);
    bool authenticate(const std::string& username, const std::string& password);
    bool beginSession(const std::string& username);
    void logout();

    bool saveLastLogins(const std::string& path) const;
    bool loadLastLogins(const std::string& path);

private:
    static std::string fingerprint(const std::string& password);
    static std::string nowStamp();
    void recordLastLogin(const std::string& username);

    bool loggedIn_ = false;
    std::string currentUsername_;
    std::unordered_map<std::string, std::string> credentials_;
    std::unordered_map<std::string, int> failedAttempts_;
    std::unordered_map<std::string, std::string> lastLogins_;
};

#endif
