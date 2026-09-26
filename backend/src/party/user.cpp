#include "party/user.hpp"

User::User(UserID id, std::string name) {
    this->id = id;
    this->name = name;
}

bool User::operator==(const User& other) const {
    return id == other.id;
}
