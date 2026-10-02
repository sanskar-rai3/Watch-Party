#pragma once

#include "party/partyManager.hpp"
#include "httplib.h"

class PartyAPI {
public:
    PartyAPI(PartyManager& partymanager);

    void start();

private:
    httplib::Server svr_;
    PartyManager& partymanager_;
};
