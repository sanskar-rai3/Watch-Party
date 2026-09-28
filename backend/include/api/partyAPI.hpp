#pragma once

#include "httplib.h"

class PartyAPI {
public:
    PartyAPI();

    void start();

private:
    httplib::Server svr;
};
