#pragma once

#include "user.hpp"

#include <string>
#include <unordered_set>

using PartyID = std::string;

class Party {
public:
    explicit Party(PartyID id);

    bool addUser(User user);
    bool removeUser(UserID id);

    bool hasUser(UserID id) const;
    bool hasUsers() const;
    bool empty() const;

    const PartyID& id() const;
    const std::unordered_set<User>& users() const;

private:
    PartyID id_;
    std::unordered_set<User> users_;
};
