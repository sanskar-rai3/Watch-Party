#pragma once

#include <cstdint>
#include <string>
#include <functional>

using UserID = std::uint64_t;

struct User {
    UserID      id;
    std::string name;

    bool operator==(const User& other) const {
        return id == other.id;
    }
};

template<>
struct std::hash<User> {
    std::size_t operator()(const User& user) const {
        return std::hash<UserID>{}(user.id);
    }
};
