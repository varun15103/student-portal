#include "ProfileStore.h"

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
