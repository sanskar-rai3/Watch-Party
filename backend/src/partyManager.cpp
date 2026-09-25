#include "partyManager.hpp"
#include "party.hpp"

bool PartyManager::createParty(const std::string& id) {
    if (parties_.contains(id))
        return false;

    parties_.emplace(id, id);
    return true;
}

bool PartyManager::deleteParty(const std::string& id) {
    return parties_.erase(id) > 0;
}

const std::unordered_map<std::string, Party>& PartyManager::getParty() const {
    return parties_;
}

bool PartyManager::hasParty(const std::string& id) {
    return parties_.contains(id);
}
