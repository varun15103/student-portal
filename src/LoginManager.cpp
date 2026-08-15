#include "LoginManager.h"

bool LoginManager::isLoggedIn() const {
    return loggedIn_;
}

const std::string& LoginManager::currentUsername() const {
    return currentUsername_;
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
