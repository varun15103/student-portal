#include "LoginManager.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <sstream>

LoginManager::LoginManager() {
    registerUser("admin", "admin123");
    registerUser("staff", "staff123");
}

std::string LoginManager::fingerprint(const std::string& password) {
    const std::size_t hashed = std::hash<std::string>{}(password + "|student-portal");
    return std::to_string(hashed);
}

std::string LoginManager::nowStamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    std::ostringstream out;
    out << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
    return out.str();
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

std::string LoginManager::lastLoginOf(const std::string& username) const {
    const auto found = lastLogins_.find(username);
    return found == lastLogins_.end() ? std::string() : found->second;
}

void LoginManager::recordLastLogin(const std::string& username) {
    lastLogins_[username] = nowStamp();
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
    recordLastLogin(username);
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

bool LoginManager::saveLastLogins(const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    for (const auto& entry : lastLogins_) {
        out << entry.first << '\t' << entry.second << '\n';
    }
    return true;
}

bool LoginManager::loadLastLogins(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    lastLogins_.clear();
    std::string username;
    std::string stamp;
    while (in >> username && std::getline(in >> std::ws, stamp)) {
        lastLogins_[username] = stamp;
    }
    return true;
}
