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

    bool registerUser(const std::string& username, const std::string& password);
    bool authenticate(const std::string& username, const std::string& password);
    bool beginSession(const std::string& username);
    void logout();

private:
    static std::string fingerprint(const std::string& password);

    bool loggedIn_ = false;
    std::string currentUsername_;
    std::unordered_map<std::string, std::string> credentials_;
    std::unordered_map<std::string, int> failedAttempts_;
};

#endif
