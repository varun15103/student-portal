#ifndef STUDENT_PORTAL_LOGIN_MANAGER_H
#define STUDENT_PORTAL_LOGIN_MANAGER_H

#include <string>

class LoginManager {
public:
    bool isLoggedIn() const;
    const std::string& currentUsername() const;

    // Starts a session for username. Credential checks are added next.
    bool beginSession(const std::string& username);
    void logout();

private:
    bool loggedIn_ = false;
    std::string currentUsername_;
};

#endif
