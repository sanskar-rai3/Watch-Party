#include "generateID.hpp"
#include "user.hpp"
#include "party.hpp"

#include <random>

UserID generateUserID() {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());

    return gen();
}

PartyID generatePartyID() {
    static constexpr char chars[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<std::size_t> dist(0, sizeof(chars) - 2);

    std::string id(8, '\0');

    for (char& c : id)
        c = chars[dist(gen)];

    return id;
}
