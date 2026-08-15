#include "LoginManager.h"

#include <functional>

LoginManager::LoginManager() {
    registerUser("admin", "admin123");
    registerUser("staff", "staff123");
}

std::string LoginManager::fingerprint(const std::string& password) {
    const std::size_t hashed = std::hash<std::string>{}(password + "|student-portal");
    return std::to_string(hashed);
}

bool LoginManager::isLoggedIn() const {
    return loggedIn_;
}

const std::string& LoginManager::currentUsername() const {
    return currentUsername_;
}

bool LoginManager::isLocked(const std::string& username) const {
    const auto found = failedAttempts_.find(username);
    return found != failedAttempts_.end() && found->second >= kMaxFailedAttempts;
}

int LoginManager::failedAttempts(const std::string& username) const {
    const auto found = failedAttempts_.find(username);
    return found == failedAttempts_.end() ? 0 : found->second;
}

bool LoginManager::registerUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.size() < 6 || credentials_.count(username) != 0) {
        return false;
    }
    credentials_[username] = fingerprint(password);
    return true;
}

bool LoginManager::authenticate(const std::string& username, const std::string& password) {
    if (isLocked(username)) {
        return false;
    }
    const auto found = credentials_.find(username);
    if (found == credentials_.end() || found->second != fingerprint(password)) {
        failedAttempts_[username] += 1;
        return false;
    }
    failedAttempts_[username] = 0;
    return beginSession(username);
}

bool LoginManager::beginSession(const std::string& username) {
    if (username.empty()) {
        return false;
    }
    currentUsername_ = username;
    loggedIn_ = true;
    return true;
}

void LoginManager::logout() {
    loggedIn_ = false;
    currentUsername_.clear();
}
