#ifndef STUDENT_PORTAL_PROFILE_STORE_H
#define STUDENT_PORTAL_PROFILE_STORE_H

#include "Profile.h"

#include <string>
#include <vector>

class ProfileStore {
public:
    bool upsert(Profile profile);
    const Profile* find(int studentId) const;
    const std::vector<Profile>& all() const;

    bool saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);

private:
    std::vector<Profile> profiles_;
};

#endif
