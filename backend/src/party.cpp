#include "party.hpp"
#include "user.hpp"
#include "generateID.hpp"

#include <utility>
#include <unordered_map>

Party::Party(PartyID id)
    : id_(std::move(id)) {}

User& Party::addUser(std::string name) {
    UserID id;
    do {
        id = generateUserID();
    } while (hasUser(id));

    auto [it, inserted] = users_.emplace(id, User{id, name});

    return it->second;
}

bool Party::removeUser(const UserID& id) {
    return users_.erase(id) > 0;
}

bool Party::hasUser(const UserID& id) const {
    return users_.contains(id);
}

bool Party::empty() const {
    return users_.empty();
}

const PartyID &Party::id() const {
    return id_;
}

const std::unordered_map<UserID, User>& Party::users() const {
    return users_;
}
