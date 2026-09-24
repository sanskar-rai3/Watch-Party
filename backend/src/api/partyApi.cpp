#include <iostream>
#include "httplib.h"
#include "api/partyApi.hpp"

void PartyServer::start()
{
    svr_.set_pre_routing_handler(
        [](const httplib::Request &req, httplib::Response &res)
        {
            res.set_header(
                "Access-Control-Allow-Origin",
                "http://localhost:3000");

            res.set_header(
                "Access-Control-Allow-Methods",
                "GET, POST, PUT, DELETE, OPTIONS");

            res.set_header(
                "Access-Control-Allow-Headers",
                "Content-Type");

            if (req.method == "OPTIONS")
            {
                res.status = 204;
                return httplib::Server::HandlerResponse::Handled;
            }

            return httplib::Server::HandlerResponse::Unhandled;
        });
    svr_.Post("/api/party/create", [](const httplib::Request &req, httplib::Response &res)
              {
        std::cout << "Body: " << req.body << std::endl;

            res.set_content(
                R"({"message":"Party created"})",
                "application/json"
            ); });

    svr_.listen("0.0.0.0", 8080);
}
