#include <iostream>
#include "httplib.h"
#include "partyApi.hpp"

void PartyServer::start()
{
    svr_.Post("/api/party/create", [](const httplib::Request &req, httplib::Response &res)
              {
        std::cout << "Body: " << req.body << std::endl;

            res.set_content(
                R"({"message":"Party created"})",
                "application/json"
            ); });
}
    