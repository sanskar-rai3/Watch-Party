#pragma once

#include <string>
#include <unordered_set>

class Party {
public:
    explicit Party(std::string id);

    bool addClient(int client_id);
    void removeClient(int client_id);

    bool hasClient(int client_id) const;
    bool empty() const;

    const std::string& id() const;
    const std::unordered_set<int>& clients() const;

private:
    std::string id_;
    std::unordered_set<int> clients_;
};
