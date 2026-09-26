#include "party/user.hpp"

#include <utility>

User::User(UserID id, std::string name)
    : id(id), name(std::move(name)) {}

bool User::operator==(const User& other) const {
    return id == other.id;
}
