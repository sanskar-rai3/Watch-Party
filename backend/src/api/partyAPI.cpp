#include "api/partyAPI.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"

#include <iostream>

using json = nlohmann::json;

PartyAPI::PartyAPI() {
    svr.set_pre_routing_handler([](const httplib::Request &req, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        if (req.method == "OPTIONS") {
            res.status = 204;
            return httplib::Server::HandlerResponse::Handled;
        }

        return httplib::Server::HandlerResponse::Unhandled;
    });

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello world", "text/plain");
    });
}

void PartyAPI::start() {
    std::cout << "http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
}
