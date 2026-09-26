#pragma once

#include "party.hpp"
#include <unordered_map>

class PartyManager {
public:
    Party& createParty();
    bool deleteParty(const PartyID& id);

    bool hasParty(const PartyID& id) const;
    bool empty() const;
    
    const std::unordered_map<PartyID, Party>& getParty() const;


private:
    std::unordered_map<PartyID, Party> parties_;
};
