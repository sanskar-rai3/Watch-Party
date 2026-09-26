#pragma once

#include "party.hpp"
#include <unordered_map>

class PartyManager {
public:
    bool createParty(const PartyID& id);

    bool deleteParty(const PartyID& id);

    const std::unordered_map<PartyID, Party>& getParty() const;

    bool hasParty(const PartyID& id);

private:
    std::unordered_map<PartyID, Party> parties_;
};
