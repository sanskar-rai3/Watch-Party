#pragma once

#include "httplib.h"

class PartyServer {
public:
    void registerRoutes(httplib::Server& svr);
};