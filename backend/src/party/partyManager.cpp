#include "party/partyManager.hpp"
#include "party/party.hpp"
#include "utils/generateID.hpp"

Party& PartyManager::createParty() {
    PartyID id;
    do {
        id = generatePartyID();
    } while (hasParty(id));

    auto [it, inserted] = parties_.emplace(id, id);

    return it->second;
}

bool PartyManager::deleteParty(const PartyID& id) {
    return parties_.erase(id) > 0;
}

bool PartyManager::hasParty(const PartyID& id) const {
    return parties_.contains(id);
}

bool PartyManager::empty() const {
    return parties_.empty();
}
 
const std::unordered_map<std::string, Party>& PartyManager::getParty() const {
    return parties_;
}
