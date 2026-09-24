#pragma once

#include "httplib.h"

class PartyServer {
public:
    void start();

private:
    httplib::Server svr_;
};