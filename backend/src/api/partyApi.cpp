#include "api/partyApi.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

void PartyServer::registerRoutes(httplib::Server &svr) {
    svr.Post("/api/party/create", [](const httplib::Request &req, httplib::Response &res) {
        try {
            json data = json::parse(req.body);

            std::string host = data.at("host").get<std::string>();
            std::string partyName = data.at("partyName").get<std::string>();
            int maxUsers = data.at("maxUsers").get<int>();

            std::cout << "Host: " << host << "\n";
            std::cout << "Party: " << partyName << "\n";
            std::cout << "Max users: " << maxUsers << "\n";

            json response = {
                                {"success", true},
                                {"message", "Party craeted successfully"}
                            };

            res.set_content(response.dump(), "application/json");
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    });

    svr.Get("/api/parties", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content(R"({"parties":[]})", "application/json");
    });
}
