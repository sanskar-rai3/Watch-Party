#include "party.hpp"
#include <string>
#include<iostream>
#include <utility>
#include <unordered_set>

Party::Party(std::string id)
    : id_(std::move(id)) {}

bool Party::addClient(int client_id) {
    return clients_.insert(client_id).second;
}

void Party::removeClient(int client_id) {
    clients_.erase(client_id);
}

bool Party::hasClient(int client_id) const {
    return clients_.contains(client_id);
}

bool Party::empty() const {
    return clients_.empty();
}

const std::string &Party::id() const {
    return id_;
}

const std::unordered_set<int> &Party::clients() const {
    return clients_;
}
 

int main () {
    Party party("123");
    party.addClient(0);
    bool empty = party.empty();
    std::cout << empty << std::endl;

    return 0;
}