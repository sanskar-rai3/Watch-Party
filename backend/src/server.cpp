#include <iostream>
#include "httplib.h"
#include "api/partyApi.hpp"
#include "nlohmann/json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

struct User {
    std::string name;
    std::string roomId;
    httplib::ws::WebSocket *socket;
};

std::vector<User> users;

int main() {
    httplib::Server svr;

    PartyServer party;
    party.registerRoutes(svr);

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

    svr.WebSocket("/ws", [](const httplib::Request &req, httplib::ws::WebSocket &ws) {
        std::string msg;

        if (ws.read(msg)) {
            json data = json::parse(msg);
            std::string type = data["type"];

            if (type == "join") {
                std::string name = data["name"];
                std::string roomId = data["roomId"];

                // Store this user's connection
                users.push_back(
                       {name,
                        roomId,
                        &ws}
                );

                std::cout << name
                          << " joined room "
                          << roomId
                          << "\n";

                json roomUsers;
                roomUsers["type"] = "room_users";
                roomUsers["users"] = json::array();

                for (auto &user : users) {
                    if (user.roomId == roomId) {
                        roomUsers["users"].push_back(user.name);
                    }
                }

                std::string response = roomUsers.dump();

                for (auto &user : users) {
                    if (user.roomId == roomId) {
                        if (user.socket != &ws) {
                            json joined;
                            joined["type"] = "user_joined";
                            joined["message"] = name + "joined the chat";

                            user.socket->send(joined.dump());
                        }

                        user.socket->send(response);
                    }
                }
            }
        }

        while (ws.read(msg)) {

        }

        users.erase(std::remove_if(
                users.begin(),
                users.end(),
                [&ws](const User &user) {
                    return user.socket == &ws;
        }),

        users.end());

        std::cout << "User disconnected\n";
    });

    svr.Get("/", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Hello world", "text/plain");
    });

    std::cout << "http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}
