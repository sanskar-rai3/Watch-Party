#pragma once

#include "party/user.hpp"

#include <string>
#include <unordered_map>

using PartyID = std::string;

class Party {
public:
    explicit Party(PartyID id);

    User& addUser(std::string name);
    bool removeUser(const UserID& id);

    bool hasUser(const UserID& id) const;
    bool empty() const;

    const PartyID& id() const;
    const std::unordered_map<UserID, User>& users() const;

private:
    PartyID id_;
    std::unordered_map<UserID, User> users_;
};
