#include "party/partyManager.hpp"
#include "api/partyAPI.hpp"

class App {
public:
    App();

    void start();

private:
    PartyManager partymanager_;
    PartyAPI partyapi_;
};
