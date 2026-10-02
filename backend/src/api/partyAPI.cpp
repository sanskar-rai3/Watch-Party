#include "api/partyAPI.hpp"
#include "party/partyManager.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"

#include <iostream>

using json = nlohmann::json;

PartyAPI::PartyAPI(PartyManager& partymanager) : partymanager_(partymanager) {
    svr_.set_pre_routing_handler([](const httplib::Request &req, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        if (req.method == "OPTIONS") {
            res.status = 204;
            return httplib::Server::HandlerResponse::Handled;
        }

        return httplib::Server::HandlerResponse::Unhandled;
    });

    svr_.Post("/api/party/create", [this](const httplib::Request& req, httplib::Response& res) {
        Party& party = partymanager_.createParty();

        nlohmann::json response = {
            {"id", party.id()}
        };

        res.set_content(response.dump(), "application/json");
    });
}

void PartyAPI::start() {
    std::cout << "http://localhost:8080" << std::endl;
    svr_.listen("0.0.0.0", 8080);
}
