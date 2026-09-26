#pragma once

#include <cstdint>
#include <string>

using UserID = std::uint64_t;

struct User {
    UserID      id;
    std::string name;

    User(UserID id, std::string name);

    bool operator==(const User& other) const;
};
