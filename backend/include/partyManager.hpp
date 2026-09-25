#pragma once

#include "party.hpp"
#include <unordered_map>
#include <string>

class PartyManager {
public:
    bool createParty(const std::string& id);

    bool deleteParty(const std::string& id);

    const std::unordered_map<std::string, Party>& getParty() const;

    bool hasParty(const std::string& id);

private:
    std::unordered_map<std::string, Party>& parties_;
};