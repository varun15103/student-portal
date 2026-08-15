#include "ProfileStore.h"

#include <fstream>
#include <sstream>

bool ProfileStore::upsert(Profile profile) {
    if (!profile.isValid()) {
        return false;
    }
    for (auto& existing : profiles_) {
        if (existing.studentId() == profile.studentId()) {
            existing = std::move(profile);
            return true;
        }
    }
    profiles_.push_back(std::move(profile));
    return true;
}

const Profile* ProfileStore::find(int studentId) const {
    for (const auto& profile : profiles_) {
        if (profile.studentId() == studentId) {
            return &profile;
        }
    }
    return nullptr;
}

const std::vector<Profile>& ProfileStore::all() const {
    return profiles_;
}

bool ProfileStore::saveToFile(const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    for (const auto& profile : profiles_) {
        out << profile.studentId() << '\t' << profile.displayName() << '\t'
            << profile.email() << '\t' << profile.gpa() << '\n';
    }
    return true;
}

bool ProfileStore::loadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    profiles_.clear();
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream row(line);
        int id = 0;
        double gpa = 0.0;
        std::string name;
        std::string email;
        if (row >> id && std::getline(row >> std::ws, name, '\t') &&
            std::getline(row, email, '\t') && row >> gpa) {
            upsert(Profile(id, name, email, gpa));
        }
    }
    return true;
}
